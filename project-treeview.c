#include "config.h"

#include "secretary-gtk/project-treeview.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"


GtkWidget *sct_gtk_project_treeview_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            _("Perspective"), renderer, 
            "text", SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, NULL);
    gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview), column, 0);
    
    Secretary *secretary = notebook_get_secretary(app->notebook);
    
    GtkTreeModel *model = sct_gtk_project_tree_model_new(secretary);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);
    
    GtkScrolledWindow *window = gtk_scrolled_window_new(NULL,  NULL);
    gtk_container_add(GTK_CONTAINER(window), treeview);
    gtk_widget_show(GTK_WIDGET(treeview));
    gtk_widget_show(GTK_WIDGET(window));
    
    app->project_tree_view = treeview;
    app->project_tree_store = model;
    
    
    return window;
}

