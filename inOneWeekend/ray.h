#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

ray ray_create(const point3* origin, const vec3* direction);

const point3* ray_origin(const ray* r);
const vec3* ray_direction(const ray* r);

// Function to get the point at parameter t along the ray
point3 ray_at(const ray* r, double t);

#endif
