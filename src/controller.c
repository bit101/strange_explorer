#include "controller.h"
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "library.h"
#include "model.h"
#include "params.h"

extern Model* model;
extern Params* params;

static Formula** formula_list;
static GtkWidget* drawing_area;
static GtkComboBoxText* formulas_combo_box;
static GtkEntry* x_entry;
static GtkEntry* y_entry;
static GtkEntry* z_entry;
static GtkButton* update_formulas_button;
static GtkScale* scale_scale;
static GtkScale* iter_scale;
static GtkScale* a_scale;
static GtkScale* b_scale;
static GtkScale* c_scale;
static GtkScale* d_scale;

void use_formula(int index) {
  Formula* formula = formula_list[index];

  // update model / params from formula
  model_set_x_formula(model, formula->x_formula);
  model_set_y_formula(model, formula->y_formula);
  /* model_set_z_formula(model, formula.z_formula); */
  params->scale.value = formula->scale;
  params->iter.value = formula->iter;
  params->a.value = formula->a;
  params->b.value = formula->b;
  params->c.value = formula->c;
  params->d.value = formula->d;

  // update ui from model / params
  gtk_entry_set_text(x_entry, model->x_formula);
  gtk_entry_set_text(y_entry, model->y_formula);
  /* gtk_entry_set_text(z_entry, model->z_formula); */
  gtk_range_set_value(GTK_RANGE(scale_scale), params->scale.value);
  gtk_range_set_value(GTK_RANGE(iter_scale), params->iter.value);
  gtk_range_set_value(GTK_RANGE(a_scale), params->a.value);
  gtk_range_set_value(GTK_RANGE(b_scale), params->b.value);
  gtk_range_set_value(GTK_RANGE(c_scale), params->c.value);
  gtk_range_set_value(GTK_RANGE(d_scale), params->d.value);
}

void init_formulas() {
  int index = 0;
  Formula_ptr fp = formula_list[index];
  while (fp != NULL) {
    gtk_combo_box_text_append_text(formulas_combo_box, fp->name);
    index++;
    fp = formula_list[index];
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(formulas_combo_box), 0);
  use_formula(0);
}

void get_widgets(GtkBuilder* builder) {
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
  formulas_combo_box = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "formulas_combo_box"));
  x_entry = GTK_ENTRY(gtk_builder_get_object(builder, "x_expr_entry"));
  y_entry = GTK_ENTRY(gtk_builder_get_object(builder, "y_expr_entry"));
  z_entry = GTK_ENTRY(gtk_builder_get_object(builder, "z_expr_entry"));
  update_formulas_button = GTK_BUTTON(gtk_builder_get_object(builder, "update_formulas_button"));
  scale_scale = GTK_SCALE(gtk_builder_get_object(builder, "scale_scale"));
  iter_scale = GTK_SCALE(gtk_builder_get_object(builder, "iter_scale"));
  a_scale = GTK_SCALE(gtk_builder_get_object(builder, "a_scale"));
  b_scale = GTK_SCALE(gtk_builder_get_object(builder, "b_scale"));
  c_scale = GTK_SCALE(gtk_builder_get_object(builder, "c_scale"));
  d_scale = GTK_SCALE(gtk_builder_get_object(builder, "d_scale"));
}

void controller_init(GtkBuilder* builder) {
  formula_list = get_formulas();
  get_widgets(builder);
  init_formulas();
}

void controller_destroy() {
  int index = 0;
  while (formula_list[index] != NULL) {
    free(formula_list[index++]);
  }
  free(formula_list);
}

gboolean on_export_button_clicked(GtkButton* button, gpointer user_data) {
  canvas_save_image();
  return TRUE;
}

gboolean on_update_formulas_button_clicked(GtkButton* button, gpointer user_data) {
  model_set_x_formula(model, gtk_entry_get_text(x_entry));
  model_set_y_formula(model, gtk_entry_get_text(y_entry));
  model_set_z_formula(model, gtk_entry_get_text(z_entry));

  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_formula_changed(GtkComboBoxText* combo_box, gpointer user_data) {
  int index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
  use_formula(index);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_scale_changed(GtkRange* range, gpointer* user_data) {
  params->scale.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_iter_changed(GtkRange* range, gpointer* user_data) {
  params->iter.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_a_changed(GtkRange* range, gpointer* user_data) {
  params->a.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_b_changed(GtkRange* range, gpointer* user_data) {
  params->b.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_c_changed(GtkRange* range, gpointer* user_data) {
  params->c.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}

gboolean on_d_changed(GtkRange* range, gpointer* user_data) {
  params->d.value = gtk_range_get_value(range);
  canvas_render(drawing_area);
  return TRUE;
}
