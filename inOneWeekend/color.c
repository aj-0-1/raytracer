#include "color.h"

// Function to write the color to the output stream
void write_color(FILE* out, const color* pixel_color) {
    // Extract the color components
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    // Write out the pixel color components
    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
