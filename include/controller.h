#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <gtk/gtk.h>

void controller_init(GtkBuilder* builder);
gboolean on_export_button_clicked(GtkButton* button, gpointer user_data);
void controller_destroy();

#endif
