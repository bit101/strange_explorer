#ifndef _PARAMS_H_
#define _PARAMS_H_

#include <gtk/gtk.h>

typedef struct {
  char* name;
  double value;
  double min;
  double max;
  double step;
} Param;

typedef struct {
  Param scale;
  Param iter;
  Param a;
  Param b;
  Param c;
  Param d;
} Params;

Params* params_new();
void params_destroy(Params* params);

#endif
