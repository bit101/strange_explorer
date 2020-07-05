#ifndef _LIBRARY_H_
#define _LIBRARY_H_

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

Formula* get_formulas();
int formula_count();

#endif
