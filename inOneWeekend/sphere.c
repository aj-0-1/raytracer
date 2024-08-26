#include "sphere.h"
#include "interval.h"
#include <math.h>
#include <stdlib.h>

bool sphere_hit(const hittable *obj, const ray *r, interval ray_t,
                hit_record *rec) {
  const sphere_data *s = (const sphere_data *)obj->data;
  vec3 oc = vec3_subtract(&r->orig, &s->center);
  double a = vec3_length_squared(&r->dir);
  double half_b = vec3_dot(&oc, &r->dir);
  double c = vec3_length_squared(&oc) - s->radius * s->radius;

  double discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return false;
  }
  double sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  double root = (-half_b - sqrtd) / a;
  if (!interval_surrounds(&ray_t, root)) {
    root = (-half_b + sqrtd) / a;
    if (!interval_surrounds(&ray_t, root))
      return false;
  }

  rec->t = root;
  rec->p = ray_at(r, rec->t);
  vec3 tmp1 = vec3_subtract(&rec->p, &s->center);
  vec3 outward_normal = vec3_divide(&tmp1, s->radius);
  set_face_normal(rec, r, &outward_normal);

  return true;
}

hittable *sphere_create(point3 center, double radius) {
  hittable *h = malloc(sizeof(hittable));
  if (h == NULL)
    return NULL;

  sphere_data *data = malloc(sizeof(sphere_data));
  if (data == NULL) {
    free(h);
    return NULL;
  }

  data->center = center;
  data->radius = radius;

  h->hit = sphere_hit;
  h->destroy = sphere_destroy;
  h->data = data;

  return h;
}

void sphere_destroy(hittable *obj) {
  free(obj->data);
  free(obj);
}
