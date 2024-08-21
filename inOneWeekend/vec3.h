#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
    double e[3];
} vec3;

// Define point3 as an alias for vec3
typedef vec3 point3;

vec3 vec3_create(double e0, double e1, double e2);
void vec3_set(vec3* v, double e0, double e1, double e2);
double vec3_x(const vec3* v);
double vec3_y(const vec3* v);
double vec3_z(const vec3* v);

vec3 vec3_negate(const vec3* v);
vec3 vec3_add_vec(const vec3* u, const vec3* v);
vec3 vec3_subtract_vec(const vec3* u, const vec3* v );
vec3 vec3_multiply_vec(const vec3* u, const vec3* v);

vec3 vec3_multiply_scalar(const vec3* v, double t);
vec3 vec3_divide_scalar(const vec3* v, double t);

double vec3_length(const vec3* v);
double vec3_length_squared(const vec3* v);
double vec3_dot(const vec3* u, const vec3* v);
vec3 vec3_cross(const vec3* u, const vec3* v);
vec3 vec3_unit_vector(const vec3* v);
void vec3_print(const vec3* v);

#endif
