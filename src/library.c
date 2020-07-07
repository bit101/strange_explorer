#include "library.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formula.h"

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
  char* value = calloc(255, 1);
  while (token != NULL) {
    token = strtok(NULL, " ");
    if (token != NULL) {
      sprintf(value, "%s %s", value, token);
    }
  }
  set_prop(formula, prop, value);
  free(value);
}

Formula* load_formula(char* file_name) {
  Formula* formula = formula_new();
  FILE* file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Could not open %s\n", file_name);
    exit(1);
  }
  char line[255];

  while (fgets(line, sizeof(line), file)) {
    parse_line(formula, line);
  }
  fclose(file);
  return formula;
}

Formula_ptr* get_formulas() {
  Formula_ptr* formula_list = malloc(sizeof(Formula*) * 100);
  char path[255];
  int index = 0;
  struct dirent* file;
  DIR* dir = opendir("./formulas");

  if (dir) {
    while ((file = readdir(dir)) != NULL) {
      if (strstr(file->d_name, ".frm") != NULL) {
        sprintf(path, "formulas/%s", file->d_name);
        formula_list[index++] = load_formula(path);
      }
    }
    closedir(dir);
  }
  formula_list[index] = NULL;
  return formula_list;
}
