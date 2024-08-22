#include "ray.h"
#include "vec3.h"

ray ray_create(const point3* origin, const vec3* direction) {
    ray r;
    r.orig = *origin;
    r.dir = *direction;
    return r;
}

// Function to get the point at parameter t along the ray
point3 ray_at(const ray* r, double t) {
    vec3 scaled_dir = vec3_scale(&r->dir, t);
    return (point3)vec3_add(&r->orig, &scaled_dir);
}
