#include "interval.h"

interval interval_create(double min, double max) {
    interval i = {min, max};
    return i;
}

double interval_size(const interval* i) {
    return i->max - i->min;
}

bool interval_contains(const interval* i, double x) {
    return i->min <= x && x <= i->max;
}

bool interval_surrounds(const interval* i, double x) {
    return i->min < x && x < i->max;
}

const interval interval_empty = {INFINITY, -INFINITY};
const interval interval_universe = {-INFINITY, INFINITY};
