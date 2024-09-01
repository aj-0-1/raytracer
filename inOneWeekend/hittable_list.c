#include "hittable_list.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 4

hittable_list *hittable_list_create() {
  hittable_list *list = malloc(sizeof(hittable_list));
  if (!list) {
    return NULL;
  }

  list->objects = malloc(INITIAL_CAPACITY * sizeof(hittable *));
  if (!list->objects) {
    free(list);
    return NULL;
  }

  list->size = 0;
  list->capacity = INITIAL_CAPACITY;
  return list;
}

void hittable_list_destroy(hittable_list *list) {
  if (!list) {
    return;
  }
  for (size_t i = 0; i < list->size; i++) {
    list->objects[i]->destroy(list->objects[i]);
  }
  free(list->objects);
  free(list);
}

void hittable_list_clear(hittable_list *list) {
  for (size_t i = 0; i < list->size; i++) {
    list->objects[i]->destroy(list->objects[i]);
  }
  list->size = 0;
}

bool hittable_list_add(hittable_list *list, hittable *object) {
  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;
    hittable **new_objects = realloc(list->objects, new_capacity * sizeof(hittable *));
    if (!new_objects) {
      return false;
    }
    list->objects = new_objects;
    list->capacity = new_capacity;
  }
  list->objects[list->size++] = object;
  return true;
}

bool hittable_list_hit(const hittable_list *list, const ray *r, interval ray_t, hit_record *rec) {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = ray_t.max;

  for (size_t i = 0; i < list->size; i++) {
    interval temp_t = interval_create(ray_t.min, closest_so_far);
    if (list->objects[i]->hit(list->objects[i], r, temp_t, &temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      *rec = temp_rec;
    }
  }

  return hit_anything;
}
