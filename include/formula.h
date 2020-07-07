#ifndef _FORMULA_H_
#define _FORMULA_H_

typedef struct {
  char* name;
  char* x_formula;
  char* y_formula;
  char* z_formula;
  double scale;
  int iter;
  double a;
  double b;
  double c;
  double d;
} Formula;

typedef Formula* Formula_ptr;

Formula_ptr formula_new();

#endif
