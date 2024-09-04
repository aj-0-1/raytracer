#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Constants
#ifndef INFINITY
#define INFINITY (DBL_MAX)
#endif
#define PI 3.1415926535897932385

// Utility Functions
static inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

static inline double random_double() {
    // Returns a random real in [0,1)
    return rand() / (RAND_MAX + 1.0);
}

static inline double random_double_min_max(double min, double max) {
    // Returns a random real in [min,max)
    return min + (max-min)*random_double();
}

// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif
