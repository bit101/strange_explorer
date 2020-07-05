#ifndef _MODEL_H_
#define _MODEL_H_

#include <gtk/gtk.h>

typedef struct {
  double width;
  double height;
  char* x_formula;
  char* y_formula;
  char* z_formula;
} Model;

Model* model_new();
void model_set_x_formula(Model* model, const char* new_formula);
void model_set_y_formula(Model* model, const char* new_formula);
void model_set_z_formula(Model* model, const char* new_formula);
void model_destroy(Model* model);

#endif
