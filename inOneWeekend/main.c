#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>



#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

double hit_sphere(const point3* center, double radius, const ray* r) {
    vec3 oc = vec3_subtract_vec(center, &r->orig);

    double a = vec3_length_squared(&r->dir);
    double h = vec3_dot(&r->dir, &oc);
    double c = vec3_length_squared(&oc) - (radius * radius);
    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray* r) {
    point3 center = vec3_create(0, 0, -1);
    double radius = 0.5;
    double t = hit_sphere(&center, radius, r);

    if (t > 0.0) {
        printf("Hit detected at t = %f\n", t);
        vec3 hit_point = ray_at(r, t);
        vec3 n = vec3_subtract_vec(&hit_point, &center);
        vec3 N = vec3_unit_vector(&n);

        vec3 vec_plus_one = vec3_create(vec3_x(&N) + 1.0, vec3_y(&N) + 1.0, vec3_z(&N) + 1.0);
        color res = vec3_multiply_scalar(&vec_plus_one, 0.5);
        return res;
    }

    vec3 unit_direction = vec3_unit_vector(&r->dir);
    double a = 0.5 * (vec3_y(&unit_direction) + 1.0);

    color white = vec3_create(1.0, 1.0, 1.0);
    color blue = vec3_create(0.5, 0.7, 1.0);

    color result = vec3_multiply_scalar(&white,1.0 - a);
    color temp = vec3_multiply_scalar(&blue, a);

    return vec3_add_vec(&result, &temp);
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

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)(image_width) / image_height);
    point3 camera_center = vec3_create(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3_create(viewport_width, 0, 0);
    vec3 viewport_v = vec3_create(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = vec3_divide_scalar(&viewport_u, (double)image_width);
    vec3 pixel_delta_v = vec3_divide_scalar(&viewport_v,(double)image_height);

    // Calculate the location of the upper left pixel.
    // viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 focal_length_vec = vec3_create(0, 0, focal_length);

    vec3 viewport_u_1_2 = vec3_divide_scalar(&viewport_u, 2);
    vec3 viewport_v_1_2 = vec3_divide_scalar(&viewport_v, 2);

    vec3 viewport_upper_left = vec3_subtract_vec(&camera_center, &focal_length_vec);
    viewport_upper_left = vec3_subtract_vec(&viewport_upper_left, &viewport_u_1_2);
    viewport_upper_left = vec3_subtract_vec(&viewport_upper_left, &viewport_v_1_2);

    vec3 pixel_delta_u_sum_v = vec3_add_vec(&pixel_delta_u, &pixel_delta_v);
    vec3 tmp1 = vec3_multiply_scalar(&pixel_delta_u_sum_v, 0.5);
    vec3 pixel00_loc = vec3_add_vec(&tmp1, &viewport_upper_left);

    // Allocate buffer for pixel data (3 channels for RGB)
    uint8_t *image_data = (uint8_t*)malloc(image_width * image_height * 3);
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

             temp_u = vec3_multiply_scalar(&pixel_delta_u, i);
             temp_v = vec3_multiply_scalar(&pixel_delta_v, j);
             pixel_center = vec3_add_vec(&pixel00_loc, &temp_u);
             pixel_center = vec3_add_vec(&pixel_center, &temp_v);

             vec3 ray_direction = vec3_subtract_vec(&pixel_center, &camera_center);
             ray r = ray_create(&camera_center, &ray_direction);

             // Get pixel color using your ray tracing function
             color pixel_color = ray_color(&r);

             // Map the color to 0-255 range and store in image_data
             image_data[(j * image_width + i) * 3 + 0] = (uint8_t)(vec3_x(&pixel_color) * 255.999); // R
             image_data[(j * image_width + i) * 3 + 1] = (uint8_t)(vec3_y(&pixel_color) * 255.999); // G
             image_data[(j * image_width + i) * 3 + 2] = (uint8_t)(vec3_z(&pixel_color) * 255.999); // B
         }
     }

     char *filename = getenv("OUTPUT_IMAGE");
     if (filename == NULL) {
         filename = "default_output.png";
     }

     // Write the image to a file using stb_image_write
     if (!stbi_write_png(filename, image_width, image_height, 3, image_data, image_width * 3)) {
         fprintf(stderr, "Error: Failed to write image\n");
         free(image_data);
         return 1;
     }

     // Free the allocated image data
     free(image_data);

    fprintf(stderr, "\rDone.                 \n");
    return 0;
}
