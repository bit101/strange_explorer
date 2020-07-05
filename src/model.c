#include "model.h"
#include <gtk/gtk.h>
#include <stdbool.h>

Model* model_new() {
  Model* m = malloc(sizeof(Model));
  m->width = 800;
  m->height = 800;
  m->x_formula = "";
  m->y_formula = "";
  return m;
}

void model_destroy(Model* model) {
  free(model);
}
