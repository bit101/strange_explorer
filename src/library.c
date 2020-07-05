#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Formula formula_list[3] = {
    {"Pickover Attractor", "sin(a * y) + c * cos(a * x)", "sin(b * x) + d * cos(b * y)", "n/a", 100, 20000, 1.317,
     -1.512, 2.098, 1.220},
    {"Peter Dejong Attractor", "sin(y*a)-cos(x*b)", "sin(x*c)-cos(y*d)", "n/a", 100, 20000, 0.871, -3.181, -2.195,
     1.220},
    {"Hopalong Attractor", "y-1-sqrt(abs(b*x-1-c))*sign(x-1)", "a-x-1", "n/a", 10, 50000, -0.537, 2.797, 2.973, 0},
};

void set_prop(Formula* formula, char* prop, char* value) {
  char* buffer = malloc(255);
  if (!strcmp(prop, "name")) {
    strcpy(buffer, value);
    formula->name = buffer;
  } else if (!strcmp(prop, "x_formula")) {
    strcpy(buffer, value);
    formula->x_formula = buffer;
  } else if (!strcmp(prop, "y_formula")) {
    strcpy(buffer, value);
    formula->y_formula = buffer;
  } else if (!strcmp(prop, "a")) {
    formula->a = strtod(value, NULL);
  } else if (!strcmp(prop, "b")) {
    formula->b = strtod(value, NULL);
  } else if (!strcmp(prop, "c")) {
    formula->c = strtod(value, NULL);
  } else if (!strcmp(prop, "d")) {
    formula->d = strtod(value, NULL);
  } else if (!strcmp(prop, "scale")) {
    formula->scale = strtod(value, NULL);
  } else if (!strcmp(prop, "iter")) {
    formula->iter = atoi(value);
  }
}

void parse_line(Formula* formula, char* line) {
  line[strcspn(line, "\r\n")] = 0;  // remove newline
  if (strlen(line) == 0) {
    return;
  }
  char* token = strtok(line, " ");
  char* prop = token;
  char* value = malloc(255);
  value[0] = 0;
  while (token != NULL) {
    token = strtok(NULL, " ");
    if (token != NULL) {
      strcat(value, token);
    }
  }
  set_prop(formula, prop, value);
}

Formula load_formula(char* file_name) {
  Formula formula = {};
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Could not open %s\n", file_name);
    exit(1);
  }
  char line[256];

  while (fgets(line, sizeof(line), file)) {
    parse_line(&formula, line);
  }
  fclose(file);
  return formula;
}

Formula* get_formulas() {
  Formula* formula_list = malloc(sizeof(Formula) * 3);
  formula_list[0] = load_formula("formulas/pickover.frm");
  formula_list[1] = load_formula("formulas/dejong.frm");
  formula_list[2] = load_formula("formulas/hopalong.frm");
  return formula_list;
}

int formula_count() {
  return 3;
}
