#include "vec3.h"

// Constructors
vec3 vec3_create(double e0, double e1, double e2) {
    vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

void vec3_set(vec3* v, double e0, double e1, double e2) {
    v->e[0] = e0;
    v->e[1] = e1;
    v->e[2] = e2;
}

// Accessors
double vec3_x(const vec3* v) { return v->e[0]; }
double vec3_y(const vec3* v) { return v->e[1]; }
double vec3_z(const vec3* v) { return v->e[2]; }

// Operations
vec3 vec3_negate(const vec3* v) {
    vec3 res;
    res.e[0] = -vec3_x(v);
    res.e[1] = -vec3_y(v);
    res.e[2] = -vec3_z(v);
    return res;
}

vec3 vec3_add_vec(const vec3* u, const vec3* v) {
    vec3 res;
    res.e[0] = vec3_x(u) + vec3_x(v);
    res.e[1] = vec3_y(u) + vec3_y(v);
    res.e[2] = vec3_z(u) + vec3_z(v);
    return res;
}

vec3 vec3_subtract_vec(const vec3* u, const vec3* v) {
    vec3 res;
    res.e[0] = vec3_x(u) - vec3_x(v);
    res.e[1] = vec3_y(u) - vec3_y(v);
    res.e[2] = vec3_z(u) - vec3_z(v);
    return res;
}

vec3 vec3_multiply_vec(const vec3* u, const vec3* v) {
    vec3 res;
    res.e[0] = vec3_x(u) * vec3_x(v);
    res.e[1] = vec3_y(u) * vec3_y(v);
    res.e[2] = vec3_z(u) * vec3_z(v);
    return res;
}

vec3 vec3_multiply_scalar(const vec3* v, double t) {
    vec3 res;
    res.e[0] = t * vec3_x(v);
    res.e[1] = t * vec3_y(v);
    res.e[2] = t * vec3_z(v);
    return res;
}

vec3 vec3_divide_scalar(const vec3* v, double t) {
    return vec3_multiply_scalar(v, 1.0 / t);
}

double vec3_length(const vec3* v) {
    return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const vec3* v) {
    return (vec3_x(v) * vec3_x(v)) + (vec3_y(v) * vec3_y(v)) + (vec3_z(v) * vec3_z(v));
}

double vec3_dot(const vec3* u, const vec3* v) {
    return (vec3_x(u) * vec3_x(v)) + (vec3_y(u) * vec3_y(v)) + (vec3_z(u) * vec3_z(v));
}

vec3 vec3_cross(const vec3* u, const vec3* v) {
    vec3 res;
    res.e[0] = vec3_y(u) * vec3_z(v) - vec3_z(u) * vec3_y(v);
    res.e[1] = vec3_z(u) * vec3_x(v) - vec3_x(u) * vec3_z(v);
    res.e[2] = vec3_x(u) * vec3_y(v) - vec3_y(u) * vec3_x(v);
    return res;
}

vec3 vec3_unit_vector(const vec3* v) {
    double length = vec3_length(v);
    return vec3_divide_scalar(v, length);
}

void vec3_print(const vec3* v) {
    printf("%f %f %f\n", vec3_x(v), vec3_y(v), vec3_z(v));
}
