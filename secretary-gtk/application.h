#ifndef _SECRETARY_GTK_APPLICATION
# define _SECRETARY_GTK_APPLICATION

#include <secretary/notebook.h>
#include <gtk/gtk.h>

typedef struct {
    Notebook *notebook;
    Secretary *secretary;
    GtkTreeModel 
            *project_tree_store, 
            *task_list_store;
    GtkWidget 
            *widget, 
            *project_tree_view, 
            *task_list_view;
    GtkToolItem 
            *add_project_button, 
            *remove_project_button, 
            *add_task_button, 
            *remove_task_button;
} SctGtkApplication;


SctGtkApplication *sct_gtk_application_new(Notebook *notebook);
void sct_gtk_application_free(SctGtkApplication *application);

#endif /* _SECRETARY_GTK_APPLICATION */
