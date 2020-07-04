#ifndef _PARAMS_PANEL_H_
#define _PARAMS_PANEL_H_

#include <gtk/gtk.h>
#include "params.h"

void params_set_builder(GtkBuilder* builder);
void init_params();
void add_param(Param param, GCallback callback);

#endif
