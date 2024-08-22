#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

// Type definitions
typedef struct {
    double x, y, z;
} vec3;

typedef vec3 point3;

// Constructor
vec3 vec3_create(double x, double y, double z);

// Accessors
#define vec3_x(v) ((v)->x)
#define vec3_y(v) ((v)->y)
#define vec3_z(v) ((v)->z)

// Mutator
void vec3_set(vec3* v, double x, double y, double z);

// Unary operations
vec3 vec3_negate(const vec3* v);
double vec3_length(const vec3* v);
double vec3_length_squared(const vec3* v);
vec3 vec3_unit_vector(const vec3* v);

// Binary operations
vec3 vec3_add(const vec3* u, const vec3* v);
vec3 vec3_subtract(const vec3* u, const vec3* v);
vec3 vec3_multiply(const vec3* u, const vec3* v);
vec3 vec3_scale(const vec3* v, double t);
vec3 vec3_divide(const vec3* v, double t);

// Products
double vec3_dot(const vec3* u, const vec3* v);
vec3 vec3_cross(const vec3* u, const vec3* v);

// Utility
void vec3_print(const vec3* v);

#endif // VEC3_H
