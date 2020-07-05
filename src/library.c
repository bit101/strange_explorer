#include "library.h"

static Formula formula_list[3] = {
    {"Pickover Attractor", "sin(a * y) + c * cos(a * x)", "sin(b * x) + d * cos(b * y)", "n/a", 100, 20000, 1.317,
     -1.512, 2.098, 1.220},
    {"Peter Dejong Attractor", "sin(y*a)-cos(x*b)", "sin(x*c)-cos(y*d)", "n/a", 100, 20000, 0.871, -3.181, -2.195,
     1.220},
    {"Hopalong Attractor", "y-1-sqrt(abs(b*x-1-c))*sign(x-1)", "a-x-1", "n/a", 10, 50000, -0.537, 2.797, 2.973, 0},
};

Formula* get_formulas() {
  return formula_list;
}

int formula_count() {
  return 3;
}
