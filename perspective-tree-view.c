#include "config.h"

#include "secretary-gtk/perspective-tree-view.h"
#include "secretary-gtk/perspective-tree-model.h"
#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"

static void _on_cursor_changed(GtkTreeView *perspective_tree_view, gpointer data);

GtkWidget *sct_gtk_perspective_tree_view_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            _("Perspective"), renderer, 
            "text", SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, NULL);
    gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview), column, 0);
    
    Secretary *secretary = notebook_get_secretary(app->notebook);
    
    GtkTreeModel *model = 
            GTK_TREE_MODEL(sct_gtk_perspective_tree_model_new(secretary));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
    
    GtkScrolledWindow *window =
            GTK_SCROLLED_WINDOW(gtk_scrolled_window_new(NULL,  NULL));
    gtk_container_add(GTK_CONTAINER(window), treeview);
    gtk_widget_show(GTK_WIDGET(treeview));
    gtk_widget_show(GTK_WIDGET(window));
    
    app->perspective_tree_view = treeview;
    app->project_tree_store = model;
    
    gtk_tree_view_expand_row(GTK_TREE_VIEW(treeview), 
            gtk_tree_path_new_from_string("3"), TRUE);
    
    g_signal_connect(G_OBJECT(treeview), "cursor-changed", 
            G_CALLBACK(_on_cursor_changed), app);
                
    return GTK_WIDGET(window);
}

static void _on_cursor_changed(GtkTreeView *perspective_tree_view, gpointer data) {
    SctGtkApplication *app = data;
    sct_gtk_applicaton_refresh_task_view(app);
}

