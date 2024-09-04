#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

typedef struct {
  hittable **objects;
  size_t size;
  size_t capacity;
} hittable_list;

hittable_list *hittable_list_create();
void hittable_list_destroy(hittable_list *list);
bool hittable_list_add(hittable_list *list, hittable *object);
bool hittable_list_hit(const hittable_list *list, const ray *r, interval ray_t,
                       hit_record *rec);

#endif
