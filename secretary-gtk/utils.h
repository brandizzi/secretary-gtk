#ifndef _SECRETARY_GTK_UTILS_H
# define _SECRETARY_GTK_UTILS_H

#include "config.h"

#include <gtk/gtk.h>
#include <time.h>

GtkWidget *sct_gtk_quit(GtkWidget *widget, GdkEvent *event, gpointer data);
#define SCT_GTK_INVALID_DATE (-1)
time_t sct_gtk_get_time_from_string(const char *string);
void sct_gtk_free_struct_callback(GtkWidget *dialog, gpointer data);

#endif /* _SECRETARY_GTK_UTILS_H */

