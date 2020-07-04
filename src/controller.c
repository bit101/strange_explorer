#include "controller.h"
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "model.h"
#include "params.h"

extern Model* model;
extern Params* params;

static GtkScale* anim_t_scale;
static GtkWidget* drawing_area;
static gboolean is_animating = FALSE;

void controller_set_builder(GtkBuilder* builder) {
  anim_t_scale = GTK_SCALE(gtk_builder_get_object(builder, "anim_t_scale"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
}

gboolean on_export_button_clicked(GtkButton* button, gpointer user_data) {
  canvas_save_image();
  return TRUE;
}
