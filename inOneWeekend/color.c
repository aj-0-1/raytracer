#include "color.h"
#include "interval.h"

// Function to write the color to the output stream
void write_color(FILE *out, const color *pixel_color) {
  // Extract the color components
  double r = vec3_x(pixel_color);
  double g = vec3_y(pixel_color);
  double b = vec3_z(pixel_color);

  // Translate the [0,1] component values to the byte range [0,255].
  const interval intensity = {0.000, 0.999};
  int rbyte = (int)(256 * interval_clamp(&intensity, r));
  int gbyte = (int)(256 * interval_clamp(&intensity, g));
  int bbyte = (int)(256 * interval_clamp(&intensity, b));

  // Write out the pixel color components
  fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}
