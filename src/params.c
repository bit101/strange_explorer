#include "params.h"
#include <gtk/gtk.h>
#include <stdbool.h>

Param param_new(char* name, double value, double min, double max, double step) {
  Param param = {};
  param.name = name;
  param.value = value;
  param.min = min;
  param.max = max;
  param.step = step;
  return param;
}

Params* params_new() {
  Params* p = malloc(sizeof(Params));
  p->scale = param_new("scale", 100, 1, 1000, 0.1);
  p->iter = param_new("iterations", 1000, 0, 1000000, 1);
  p->a = param_new("a", 1.7, -10, 10, 0.001);
  p->b = param_new("b", 1.7, -10, 10, 0.001);
  p->c = param_new("c", 0.6, -10, 10, 0.001);
  p->d = param_new("d", 1.2, -10, 10, 0.001);

  return p;
}

void params_destroy(Params* params) {
  free(params);
}
