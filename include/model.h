#ifndef _MODEL_H_
#define _MODEL_H_

#include <gtk/gtk.h>

typedef struct {
  double width;
  double height;
} Model;

Model* model_new();
void model_destroy(Model* model);

#endif
