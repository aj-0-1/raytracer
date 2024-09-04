#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"
#include <stdbool.h>

typedef struct {
  double min;
  double max;
} interval;

interval interval_create(double min, double max);

double interval_size(const interval *i);

bool interval_contains(const interval *i, double x);

bool interval_surrounds(const interval *i, double x);

double interval_clamp(const interval *i, double x);

extern const interval interval_empty;
extern const interval interval_universe;

#endif
