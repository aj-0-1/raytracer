#include "camera.h"
#include "hittable_list.h"
#include "interval.h"
#include "rtweekend.h"
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

void camera_init(camera *cam) {
  cam->aspect_ratio = 16.0 / 9.0;
  cam->image_width = 400;
  cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
  cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;
  cam->samples_per_pixel = 100;
  cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;
  cam->center = (point3){0, 0, 0};

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)cam->image_width / cam->image_height);

  vec3 viewport_u = {viewport_width, 0, 0};
  vec3 viewport_v = {0, -viewport_height, 0};
  vec3 focal_length_vec = {0, 0, focal_length};

  cam->pixel_delta_u = vec3_divide(&viewport_u, cam->image_width);
  cam->pixel_delta_v = vec3_divide(&viewport_v, cam->image_height);

  vec3 viewport_upper_left = vec3_subtract(&cam->center, &focal_length_vec);
  vec3 viewport_u_1_2 = vec3_divide(&viewport_u, 2);
  vec3 viewport_v_1_2 = vec3_divide(&viewport_v, 2);
  viewport_upper_left = vec3_subtract(&viewport_upper_left, &viewport_u_1_2);
  viewport_upper_left = vec3_subtract(&viewport_upper_left, &viewport_v_1_2);

  vec3 pixel_delta_u_sum_v = vec3_add(&cam->pixel_delta_u, &cam->pixel_delta_v);
  vec3 tmp1 = vec3_scale(&pixel_delta_u_sum_v, 0.5);
  cam->pixel00_loc = vec3_add(&tmp1, &viewport_upper_left);
}

color ray_color(const ray *r, const hittable_list *world) {
  hit_record rec;
  interval i = {0, INFINITY};
  if (hittable_list_hit(world, r, i, &rec)) {
    vec3 tmp1 = vec3_create(1, 1, 1);
    vec3 tmp2 = vec3_add(&rec.normal, &tmp1);
    return vec3_scale(&tmp2, 0.5);
  }

  vec3 unit_direction = vec3_unit_vector(&r->dir);
  double a = 0.5 * (vec3_y(&unit_direction) + 1.0);

  color white = vec3_create(1.0, 1.0, 1.0);
  color blue = vec3_create(0.5, 0.7, 1.0);

  color result = vec3_scale(&white, 1.0 - a);
  color temp = vec3_scale(&blue, a);

  return vec3_add(&result, &temp);
}

vec3 sample_square(camera *cam) {
  // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
  // square.
  return (vec3){random_double() - 0.5, random_double() - 0.5, 0};
}

ray get_ray(camera *cam, int i, int j) {
  // Construct a camera ray originating from the origin and directed at randomly
  // sampled point around the pixel location i, j.
  vec3 offset = sample_square(cam);
  vec3 tmp1 = vec3_scale(&cam->pixel_delta_u, (i + offset.x));
  vec3 tmp2 = vec3_scale(&cam->pixel_delta_v, (j + offset.y));
  vec3 pixel_sample = vec3_add(&cam->pixel00_loc, &tmp1);
  pixel_sample = vec3_add(&pixel_sample, &tmp2);

  point3 ray_origin = cam->center;
  vec3 ray_direction = vec3_subtract(&pixel_sample, &ray_origin);

  return (ray){ray_origin, ray_direction};
}

int camera_render(camera *cam, const hittable_list *world) {
  camera_init(cam);

  // Allocate buffer for pixel data (3 channels for RGB)
  uint8_t *image_data =
      (uint8_t *)malloc(cam->image_width * cam->image_height * 3);
  if (!image_data) {
    fprintf(stderr, "Error: Unable to allocate memory for image data\n");
    return 1;
  }

  // Render
  for (int j = 0; j < cam->image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d\n", (cam->image_height - j));
    fflush(stderr);
    for (int i = 0; i < cam->image_width; i++) {
      color pixel_color = {0, 0, 0};
      for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
        ray r = get_ray(cam, i, j);
        vec3 tmp1 = ray_color(&r, world);
        pixel_color = vec3_add(&pixel_color, &tmp1);
      }

      // Map the color to 0-255 range and store in image_data

      vec3 pixel_colour_scaled =
          vec3_scale(&pixel_color, cam->pixel_samples_scale);

      const interval intensity = {0.000, 0.999};
      double x = interval_clamp(&intensity, vec3_x(&pixel_colour_scaled));
      double y = interval_clamp(&intensity, vec3_y(&pixel_colour_scaled));
      double z = interval_clamp(&intensity, vec3_z(&pixel_colour_scaled));

      image_data[(j * cam->image_width + i) * 3 + 0] =
          (uint8_t)(x * 255.999); // R
      image_data[(j * cam->image_width + i) * 3 + 1] =
          (uint8_t)(y * 255.999); // G
      image_data[(j * cam->image_width + i) * 3 + 2] =
          (uint8_t)(z * 255.999); // B
    }
  }

  char *filename = getenv("OUTPUT_IMAGE");
  if (filename == NULL) {
    filename = "default_output.png";
  }

  // Write the image to a file using stb_image_write
  if (!stbi_write_png(filename, cam->image_width, cam->image_height, 3,
                      image_data, cam->image_width * 3)) {
    fprintf(stderr, "Error: Failed to write image\n");
    free(image_data);
    return 1;
  }

  // Free the allocated image data
  free(image_data);

  fprintf(stderr, "\rDone.                 \n");
  return 0;
}
