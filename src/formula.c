#include "formula.h"
#include <stdlib.h>

Formula_ptr formula_new() {
  Formula* f = malloc(sizeof(Formula));
  f->name = malloc(255);
  f->x_formula = malloc(255);
  f->y_formula = malloc(255);
  f->z_formula = malloc(255);
  f->scale = 0;
  f->iter = 0;
  f->a = 0;
  f->b = 0;
  f->c = 0;
  f->d = 0;
  return f;
}
