#include "hittable.h"
#include "ray.h"
#include "vec3.h"

void set_face_normal(hit_record *hr, const ray *r, const vec3 *outward_normal) {
  // Sets the hit record normal vector.
  // NOTE: the parameter `outward_normal` is assumed to have unit length.

  hr->front_face = vec3_dot(&r->dir, outward_normal) < 0;
  if (hr->front_face) {
    hr->normal = *outward_normal;
  } else {
    hr->normal = vec3_negate(outward_normal);
  }
}
