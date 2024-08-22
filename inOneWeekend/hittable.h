#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <stdbool.h>

typedef struct {
    point3 p;
    vec3 normal;
    double t;
} hit_record;

typedef struct hittable hittable;

struct hittable {
    bool (*hit)(const hittable* self, const ray* r, double ray_tmin, double ray_tmax, hit_record* rec);
    void (*destroy)(hittable* self);
};

#endif
