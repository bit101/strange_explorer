#include "model.h"
#include <gtk/gtk.h>
#include <stdbool.h>

Model* model_new() {
  Model* m = malloc(sizeof(Model));
  m->width = 800;
  m->height = 800;
  m->x_formula = malloc(1);
  m->y_formula = malloc(1);
  m->z_formula = malloc(1);
  return m;
}

void model_set_x_formula(Model* model, const char* new_formula) {
  free(model->x_formula);
  model->x_formula = malloc(strlen(new_formula) + 1);
  strcpy(model->x_formula, new_formula);
}

void model_set_y_formula(Model* model, const char* new_formula) {
  free(model->y_formula);
  model->y_formula = malloc(strlen(new_formula) + 1);
  strcpy(model->y_formula, new_formula);
}

void model_set_z_formula(Model* model, const char* new_formula) {
  free(model->z_formula);
  model->z_formula = malloc(strlen(new_formula) + 1);
  strcpy(model->z_formula, new_formula);
}

void model_destroy(Model* model) {
  free(model);
}
