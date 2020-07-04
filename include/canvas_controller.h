#ifndef _CANVAS_VIEW_H_
#define _CANVAS_VIEW_H_

#include <gtk/gtk.h>

gboolean on_drawing_area_configure_event(GtkWidget* widget, GdkEventConfigure* event, gpointer data);
gboolean on_drawing_area_draw(GtkWidget* widget, cairo_t* cr, gpointer data);
void canvas_render(GtkWidget* widget);
void canvas_destroy();
void canvas_save_image();

#endif
