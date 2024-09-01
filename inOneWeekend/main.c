#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
  // World
  hittable_list *world = hittable_list_create();
  if (world == NULL) {
    fprintf(stderr, "Error: Unable to create world\n");
    exit(1);
  }

  // Create and add the first sphere
  point3 center1 = {0, 0, -1};
  hittable *sphere1 = sphere_create(center1, 0.5);
  if (sphere1 == NULL || !hittable_list_add(world, sphere1)) {
    // Handle error: unable to create or add sphere
    fprintf(stderr, "Error: Unable to create or add first sphere\n");
    hittable_list_destroy(world);
    exit(1);
  }

  // Create and add the second sphere
  point3 center2 = {0, -100.5, -1};
  hittable *sphere2 = sphere_create(center2, 100);
  if (sphere2 == NULL || !hittable_list_add(world, sphere2)) {
    // Handle error: unable to create or add sphere
    fprintf(stderr, "Error: Unable to create or add second sphere\n");
    hittable_list_destroy(world);
    exit(1);
  }

  // Camera
  camera cam;
  const hittable_list *tmp_world = world;
  camera_render(&cam, tmp_world);

  return 0;
}
