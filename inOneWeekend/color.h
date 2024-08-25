#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

// Function to write the color to the output stream
void write_color(FILE *out, const color *pixel_color);

#endif
