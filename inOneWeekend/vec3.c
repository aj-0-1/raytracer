#include "vec3.h"
#include <math.h>

// Constructor
vec3 vec3_create(double x, double y, double z) {
    return (vec3){x, y, z};
}

// Mutator
void vec3_set(vec3* v, double x, double y, double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

// Unary operations
vec3 vec3_negate(const vec3* v) {
    return (vec3){-v->x, -v->y, -v->z};
}

double vec3_length(const vec3* v) {
    return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const vec3* v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

vec3 vec3_unit_vector(const vec3* v) {
    return vec3_divide(v, vec3_length(v));
}

// Binary operations
vec3 vec3_add(const vec3* u, const vec3* v) {
    return (vec3){u->x + v->x, u->y + v->y, u->z + v->z};
}

vec3 vec3_subtract(const vec3* u, const vec3* v) {
    return (vec3){u->x - v->x, u->y - v->y, u->z - v->z};
}

vec3 vec3_multiply(const vec3* u, const vec3* v) {
    return (vec3){u->x * v->x, u->y * v->y, u->z * v->z};
}

vec3 vec3_scale(const vec3* v, double t) {
    return (vec3){v->x * t, v->y * t, v->z * t};
}

vec3 vec3_divide(const vec3* v, double t) {
    return vec3_scale(v, 1.0 / t);
}

// Products
double vec3_dot(const vec3* u, const vec3* v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

vec3 vec3_cross(const vec3* u, const vec3* v) {
    return (vec3){
        u->y * v->z - u->z * v->y,
        u->z * v->x - u->x * v->z,
        u->x * v->y - u->y * v->x
    };
}

// Utility
void vec3_print(const vec3* v) {
    printf("%f %f %f\n", v->x, v->y, v->z);
}
