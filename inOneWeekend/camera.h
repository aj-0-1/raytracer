#ifndef CAMERA_H
#define CAMERA_H

#include "hittable_list.h"
#include "rtweekend.h"

typedef struct camera {
  double aspect_ratio;
  int image_width;
  int image_height;
  int samples_per_pixel;
  double pixel_samples_scale;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
} camera;

void camera_init(camera *cam);
int camera_render(camera *cam, const hittable_list *world);
color ray_color(const ray *r, const hittable_list *world);
ray get_ray(camera *cam, int i, int j);
vec3 sample_square(camera *cam);

#endif
