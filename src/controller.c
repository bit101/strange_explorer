#include "controller.h"
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "library.h"
#include "model.h"
#include "params.h"

extern Model* model;
extern Params* params;

Formula* formula_list;
static GtkComboBoxText* formulas_combo_box;
static GtkWidget* drawing_area;
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
  model_set_x_formula(model, formula_list[index].x_formula);
  model_set_y_formula(model, formula_list[index].y_formula);
  model_set_z_formula(model, formula_list[index].z_formula);
  params->scale.value = formula_list[index].scale;
  params->iter.value = formula_list[index].iter;
  params->a.value = formula_list[index].a;
  params->b.value = formula_list[index].b;
  params->c.value = formula_list[index].c;
  params->d.value = formula_list[index].d;
  gtk_entry_set_text(x_entry, model->x_formula);
  gtk_entry_set_text(y_entry, model->y_formula);
  gtk_entry_set_text(z_entry, model->z_formula);
  gtk_range_set_value(GTK_RANGE(scale_scale), formula_list[index].scale);
  gtk_range_set_value(GTK_RANGE(iter_scale), formula_list[index].iter);
  gtk_range_set_value(GTK_RANGE(a_scale), params->a.value);
  gtk_range_set_value(GTK_RANGE(b_scale), params->b.value);
  gtk_range_set_value(GTK_RANGE(c_scale), params->c.value);
  gtk_range_set_value(GTK_RANGE(d_scale), params->d.value);
}

void init_formulas() {
  for (int i = 0; i < formula_count(); i++) {
    gtk_combo_box_text_append_text(formulas_combo_box, formula_list[i].name);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(formulas_combo_box), 0);
  use_formula(0);
}
void controller_init(GtkBuilder* builder) {
  formula_list = get_formulas();
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
  x_entry = GTK_ENTRY(gtk_builder_get_object(builder, "x_expr_entry"));
  y_entry = GTK_ENTRY(gtk_builder_get_object(builder, "y_expr_entry"));
  z_entry = GTK_ENTRY(gtk_builder_get_object(builder, "z_expr_entry"));
  formulas_combo_box = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "formulas_combo_box"));
  update_formulas_button = GTK_BUTTON(gtk_builder_get_object(builder, "update_formulas_button"));
  scale_scale = GTK_SCALE(gtk_builder_get_object(builder, "scale_scale"));
  iter_scale = GTK_SCALE(gtk_builder_get_object(builder, "iter_scale"));
  a_scale = GTK_SCALE(gtk_builder_get_object(builder, "a_scale"));
  b_scale = GTK_SCALE(gtk_builder_get_object(builder, "b_scale"));
  c_scale = GTK_SCALE(gtk_builder_get_object(builder, "c_scale"));
  d_scale = GTK_SCALE(gtk_builder_get_object(builder, "d_scale"));

  init_formulas();
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
