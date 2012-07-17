#include "secretary-gtk/application.h"
#include "secretary-gtk/widget.h"
#include <string.h>

SctGtkApplication *sct_gtk_application_new(Notebook *notebook) {
    SctGtkApplication *app = malloc(sizeof(SctGtkApplication));
    app->notebook = notebook;
    app->secretary = notebook_get_secretary(notebook);
    sct_gtk_widget_new(app);
    return app;
}

void sct_gtk_application_free(SctGtkApplication *application) {
 // TODO
}



void sct_gtk_application_select_path_on_project_treeview(
        SctGtkApplication *app, const gchar *path) {
    // Selecting inbox
    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(app->project_tree_store, &iter, path);
    
    GtkTreeView *project_tree_view = GTK_TREE_VIEW(app->project_tree_view);
    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(project_tree_view);
    gtk_tree_selection_select_iter(selection, &iter);
    // emiting signal
    gtk_signal_emit_by_name(GTK_OBJECT(project_tree_view), "cursor-changed");
}
