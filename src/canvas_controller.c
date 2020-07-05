#include "canvas_controller.h"
#include <bitlib/bitlib.h>
#include <gtk/gtk.h>
#include "controller.h"
#include "model.h"
#include "params.h"
#include "tinyexpr.h"

static cairo_surface_t* surface = NULL;
extern Model* model;
extern Params* params;
static gboolean is_rendering = FALSE;

void custom_draw(cairo_t* cr) {
  double x = 0.1;
  double y = 0.1;
  double scale = params->scale.value;
  double iter = params->iter.value;
  double a = params->a.value;
  double b = params->b.value;
  double c = params->c.value;
  double d = params->d.value;
  double x1, y1;
  const char* x_str = model->x_formula;
  const char* y_str = model->y_formula;
  te_variable vars[] = {
      {"x", &x}, {"y", &y}, {"a", &a}, {"b", &b}, {"c", &c}, {"d", &d},
  };
  te_expr* x_expr = te_compile(x_str, vars, 6, 0);
  te_expr* y_expr = te_compile(y_str, vars, 6, 0);
  cairo_clear_white(cr);
  cairo_translate(cr, model->width / 2, model->height / 2);

  for (int i = 0; i < iter; i++) {
    double xx = x * scale;
    double yy = y * scale;
    if (xx >= -model->width / 2 && xx < model->width / 2 && yy >= -model->width / 2 && yy < model->height / 2) {
      cairo_plot(cr, xx, yy);
    }

    y1 = te_eval(y_expr);
    x1 = te_eval(x_expr);
    x = x1;
    y = y1;
  }
}

//////////////////////////////////////
// CUSTOM DRAWING FUNCTION
//////////////////////////////////////
void canvas_render(GtkWidget* widget) {
  // no need to render if there is already a render in progress.
  if (is_rendering) {
    return;
  }
  // this will be set back to false at the end of on_drawing_area_draw.
  is_rendering = TRUE;
  cairo_t* cr = cairo_create(surface);

  custom_draw(cr);

  cairo_destroy(cr);
  gtk_widget_queue_draw(widget);
}

//////////////////////////////////////
// SIGNAL CALLBACKS
//////////////////////////////////////
gboolean on_drawing_area_configure_event(GtkWidget* widget, GdkEventConfigure* event, gpointer data) {
  if (surface) {
    cairo_surface_destroy(surface);
  }
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, model->width, model->height);
  canvas_render(widget);
  return TRUE;
}

gboolean on_drawing_area_draw(GtkWidget* widget, cairo_t* cr, gpointer data) {
  cairo_set_source_surface(cr, surface, 0, 0);
  cairo_paint(cr);
  // done rendering, allow more renders to happen.
  is_rendering = FALSE;
  return TRUE;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
void canvas_save_image() {
  GtkWidget* file_chooser_dialog =
      gtk_file_chooser_dialog_new("Save as...", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL,
                                  "_Save", GTK_RESPONSE_ACCEPT, NULL);
  gint result = gtk_dialog_run(GTK_DIALOG(file_chooser_dialog));

  if (result == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser* chooser = GTK_FILE_CHOOSER(file_chooser_dialog);
    char* filename = gtk_file_chooser_get_filename(chooser);
    cairo_surface_write_to_png(surface, filename);
    g_free(filename);
  }
  gtk_widget_destroy(file_chooser_dialog);
}

void canvas_destroy() {
  if (surface) {
    cairo_surface_destroy(surface);
  }
}
