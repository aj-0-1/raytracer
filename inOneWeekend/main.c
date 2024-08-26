#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "rtweekend.h"
#include "sphere.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

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

int main() {
  // Image
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = (int)(image_width / aspect_ratio);
  if (image_height < 1) {
    image_height = 1;
  }

  // World
  hittable_list *world = hittable_list_create();
  if (world == NULL) {
    fprintf(stderr, "Error: Unable to create world\n");
    exit(1);
  }

  // Create and add the first sphere
  point3 center1 = {0, 0, -1};
  hittable *sphere1 = sphere_create(center1, 0.5);
  if (sphere1 == NULL || !hittable_list_add(world, sphere1)) {
    // Handle error: unable to create or add sphere
    fprintf(stderr, "Error: Unable to create or add first sphere\n");
    hittable_list_destroy(world);
    exit(1);
  }

  // Create and add the second sphere
  point3 center2 = {0, -100.5, -1};
  hittable *sphere2 = sphere_create(center2, 100);
  if (sphere2 == NULL || !hittable_list_add(world, sphere2)) {
    // Handle error: unable to create or add sphere
    fprintf(stderr, "Error: Unable to create or add second sphere\n");
    hittable_list_destroy(world);
    exit(1);
  }

  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)(image_width) / image_height);
  point3 camera_center = vec3_create(0, 0, 0);

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  vec3 viewport_u = vec3_create(viewport_width, 0, 0);
  vec3 viewport_v = vec3_create(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = vec3_divide(&viewport_u, (double)image_width);
  vec3 pixel_delta_v = vec3_divide(&viewport_v, (double)image_height);

  // Calculate the location of the upper left pixel.
  // viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
  // viewport_u/2 - viewport_v/2;
  vec3 focal_length_vec = vec3_create(0, 0, focal_length);

  vec3 viewport_u_1_2 = vec3_divide(&viewport_u, 2);
  vec3 viewport_v_1_2 = vec3_divide(&viewport_v, 2);

  vec3 viewport_upper_left = vec3_subtract(&camera_center, &focal_length_vec);
  viewport_upper_left = vec3_subtract(&viewport_upper_left, &viewport_u_1_2);
  viewport_upper_left = vec3_subtract(&viewport_upper_left, &viewport_v_1_2);

  vec3 pixel_delta_u_sum_v = vec3_add(&pixel_delta_u, &pixel_delta_v);
  vec3 tmp1 = vec3_scale(&pixel_delta_u_sum_v, 0.5);
  vec3 pixel00_loc = vec3_add(&tmp1, &viewport_upper_left);

  // Allocate buffer for pixel data (3 channels for RGB)
  uint8_t *image_data = (uint8_t *)malloc(image_width * image_height * 3);
  if (!image_data) {
    fprintf(stderr, "Error: Unable to allocate memory for image data\n");
    return 1;
  }

  // Render
  for (int j = 0; j < image_height; j++) {
    fprintf(stderr, "\rScanlines remaining: %d\n", (image_height - j));
    fflush(stderr);
    for (int i = 0; i < image_width; i++) {
      vec3 pixel_center;
      vec3 temp_u, temp_v;

      temp_u = vec3_scale(&pixel_delta_u, i);
      temp_v = vec3_scale(&pixel_delta_v, j);
      pixel_center = vec3_add(&pixel00_loc, &temp_u);
      pixel_center = vec3_add(&pixel_center, &temp_v);

      vec3 ray_direction = vec3_subtract(&pixel_center, &camera_center);
      ray r = ray_create(&camera_center, &ray_direction);

      // Get pixel color using your ray tracing function
      color pixel_color = ray_color(&r, world);

      // Map the color to 0-255 range and store in image_data
      image_data[(j * image_width + i) * 3 + 0] =
          (uint8_t)(vec3_x(&pixel_color) * 255.999); // R
      image_data[(j * image_width + i) * 3 + 1] =
          (uint8_t)(vec3_y(&pixel_color) * 255.999); // G
      image_data[(j * image_width + i) * 3 + 2] =
          (uint8_t)(vec3_z(&pixel_color) * 255.999); // B
    }
  }

  char *filename = getenv("OUTPUT_IMAGE");
  if (filename == NULL) {
    filename = "default_output.png";
  }

  // Write the image to a file using stb_image_write
  if (!stbi_write_png(filename, image_width, image_height, 3, image_data,
                      image_width * 3)) {
    fprintf(stderr, "Error: Failed to write image\n");
    free(image_data);
    return 1;
  }

  // Free the allocated image data
  free(image_data);

  fprintf(stderr, "\rDone.                 \n");
  return 0;
}
