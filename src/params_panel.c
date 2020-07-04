#include "params_panel.h"
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "params.h"

static GtkGrid* params_grid;
static GtkWidget* drawing_area;
static int row = 0;
extern Params* params;

void params_set_builder(GtkBuilder* builder) {
  params_grid = GTK_GRID(gtk_builder_get_object(builder, "params_grid"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
}

void add_param(Param param, GCallback callback) {
  GtkWidget* label = gtk_label_new(param.name);
  gtk_grid_attach(params_grid, label, 0, row, 1, 1);

  GtkWidget* scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, param.min, param.max, param.step);
  gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_RIGHT);
  gtk_range_set_value(GTK_RANGE(scale), param.value);
  gtk_widget_set_hexpand(scale, TRUE);
  gtk_grid_attach(params_grid, scale, 1, row, 1, 1);

  g_signal_connect(scale, "value-changed", callback, (gpointer)scale);
  row++;
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

void init_params() {
  add_param(params->scale, (GCallback)on_scale_changed);
  add_param(params->iter, (GCallback)on_iter_changed);
  add_param(params->a, (GCallback)on_a_changed);
  add_param(params->b, (GCallback)on_b_changed);
  add_param(params->c, (GCallback)on_c_changed);
  add_param(params->d, (GCallback)on_d_changed);
}
