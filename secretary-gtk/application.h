#ifndef _SECRETARY_GTK_APPLICATION
# define _SECRETARY_GTK_APPLICATION

#include "config.h"

#include <secretary/notebook.h>
#include <gtk/gtk.h>


typedef struct {
    Notebook *notebook;
    Secretary *secretary;
    GtkTreeModel 
            *project_tree_store, 
            *task_tree_model;
    GtkWidget 
            *widget, 
            *perspective_tree_view, 
            *task_tree_view,
            *main_window,
            *new_task_dialog,
            *new_project_dialog;
    GtkToolItem 
            *add_project_button, 
            *remove_project_button, 
            *add_task_button, 
            *remove_task_button;
} SctGtkApplication;


SctGtkApplication *sct_gtk_application_new(Notebook *notebook);
void sct_gtk_application_free(SctGtkApplication *application);
void sct_gtk_application_select_path_on_perspective_tree_view(
        SctGtkApplication *app, const gchar *path);

#endif /* _SECRETARY_GTK_APPLICATION */
