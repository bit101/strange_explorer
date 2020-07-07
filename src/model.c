#include "model.h"
#include <gtk/gtk.h>
#include <stdbool.h>

Model* model_new() {
  Model* m = malloc(sizeof(Model));
  m->width = 800;
  m->height = 800;
  m->x_formula = malloc(255);
  m->y_formula = malloc(255);
  m->z_formula = malloc(255);
  return m;
}

void model_set_x_formula(Model* model, const char* new_formula) {
  strcpy(model->x_formula, new_formula);
}

void model_set_y_formula(Model* model, const char* new_formula) {
  strcpy(model->y_formula, new_formula);
}

void model_set_z_formula(Model* model, const char* new_formula) {
  strcpy(model->z_formula, new_formula);
}

void model_destroy(Model* model) {
  free(model->x_formula);
  free(model->y_formula);
  free(model->z_formula);
  free(model);
}
