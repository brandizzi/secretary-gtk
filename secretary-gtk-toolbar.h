#ifndef _SECRETARY_GTK_TOOLBAR_H
# define _SECRETARY_GTK_TOOLBAR_H

#include <gtk/gtk.h>
#include <secretary/secretary.h>

typedef struct  {
    GtkWidget *new_task_button, *delete_task_button, *toolbar; 
} SctGtkToolbarComponents;

GtkWidget *sct_gtk_toolbar_new(Secretary *secretary, 
        SctGtkToolbarComponents *widgets);

#endif /* _SECRETARY_GTK_TOOLBAR_H */

