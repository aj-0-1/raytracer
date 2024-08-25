#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct {
  point3 p;
  vec3 normal;
  double t;
  bool front_face;
} hit_record;

void set_face_normal(hit_record *hr, const ray *r, const vec3 *outward_normal);

typedef struct hittable hittable;

struct hittable {
  bool (*hit)(const hittable *self, const ray *r, double t_min, double t_max,
              hit_record *rec);
  void (*destroy)(hittable *self);
  void *data; // Pointer to specific shape data
};

#endif
