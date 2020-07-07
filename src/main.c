#include <bitlib/bitlib.h>
#include <gtk/gtk.h>
#include "canvas_controller.h"
#include "controller.h"
#include "model.h"
#include "params.h"

Model* model;
Params* params;

////////////////////////////////////////
// CALLBACKS
////////////////////////////////////////

void on_window_destroy(void) {
  canvas_destroy();
  gtk_main_quit();
}

int main(int argc, char** argv) {
  GtkWidget* window;
  GtkBuilder* builder = NULL;
  GtkGrid* params_grid;

  gtk_init(&argc, &argv);
  model = model_new();
  params = params_new();
  builder = gtk_builder_new();

  if (gtk_builder_add_from_file(builder, "main.ui", NULL) == 0) {
    printf("gtk_builder_add_from_file FAILED\n");
    return (0);
  }

  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  controller_init(builder);

  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(window);
  gtk_main();

  controller_destroy();
  model_destroy(model);
  params_destroy(params);
  return 0;
}
