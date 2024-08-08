#ifndef GRID__H
#define GRID__H

#include "entity.h"

typedef struct {
  int w, h;
  entity_t *grid;
} grid_t;

grid_t *grid_new(int w, int h);

#endif
