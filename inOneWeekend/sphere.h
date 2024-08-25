#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

typedef struct {
  point3 center;
  double radius;
} sphere_data;

// Function to create a new sphere
hittable *sphere_create(point3 center, double radius);

// Function to destroy a sphere (free memory)
void sphere_destroy(hittable *obj);

#endif // SPHERE_H
