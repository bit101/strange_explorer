#include "controller.h"
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "model.h"
#include "params.h"

extern Model* model;
extern Params* params;

static GtkScale* anim_t_scale;
static GtkWidget* drawing_area;
static GtkEntry* x_entry;
static GtkEntry* y_entry;
static GtkEntry* z_entry;
static GtkButton* update_formulas_button;
static gboolean is_animating = FALSE;

void controller_set_builder(GtkBuilder* builder) {
  anim_t_scale = GTK_SCALE(gtk_builder_get_object(builder, "anim_t_scale"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
  x_entry = GTK_ENTRY(gtk_builder_get_object(builder, "x_expr_entry"));
  y_entry = GTK_ENTRY(gtk_builder_get_object(builder, "y_expr_entry"));
  z_entry = GTK_ENTRY(gtk_builder_get_object(builder, "z_expr_entry"));
  update_formulas_button = GTK_BUTTON(gtk_builder_get_object(builder, "update_formulas_button"));

  char* x_formula = "sin(a * y) + c * cos(a * x)";
  char* y_formula = "sin(b * x) + d * cos(b * y)";
  model->x_formula = malloc(strlen(x_formula) + 1);
  model->y_formula = malloc(strlen(y_formula) + 1);
  strcpy(model->x_formula, x_formula);
  strcpy(model->y_formula, y_formula);
  gtk_entry_set_text(x_entry, model->x_formula);
  gtk_entry_set_text(y_entry, model->y_formula);
  gtk_entry_set_text(z_entry, "n/a");
}

gboolean on_export_button_clicked(GtkButton* button, gpointer user_data) {
  canvas_save_image();
  return TRUE;
}

gboolean on_update_formulas_button_clicked(GtkButton* button, gpointer user_data) {
  const char* x_formula = gtk_entry_get_text(x_entry);
  const char* y_formula = gtk_entry_get_text(y_entry);

  free(model->x_formula);
  free(model->y_formula);
  model->x_formula = malloc(strlen(x_formula) + 1);
  model->y_formula = malloc(strlen(y_formula) + 1);
  strcpy(model->x_formula, x_formula);
  strcpy(model->y_formula, y_formula);

  return TRUE;
}
