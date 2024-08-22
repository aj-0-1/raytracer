#include "ray.h"
#include "vec3.h"

ray ray_create(const point3* origin, const vec3* direction) {
    ray r;
    r.orig = *origin;
    r.dir = *direction;
    return r;
}

const point3* ray_origin(const ray* r) {
    return &r->orig;
}

const vec3* ray_direction(const ray* r) {
    return &r->dir;
}

// Function to get the point at parameter t along the ray
point3 ray_at(const ray* r, double t) {
    vec3 scaled_dir = vec3_multiply_scalar(&r->dir, t);
    return (point3)vec3_add_vec(&r->orig, &scaled_dir);
}
