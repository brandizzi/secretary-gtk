#include "config.h"

#include "secretary-gtk/project-treeview.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/task-listview.h"
#include "secretary-gtk/gettext.h"

static void _on_cursor_changed(GtkTreeView *project_treeview, gpointer data);

GtkWidget *sct_gtk_project_treeview_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes(
            _("Perspective"), renderer, 
            "text", SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, NULL);
    gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview), column, 0);
    
    Secretary *secretary = notebook_get_secretary(app->notebook);
    
    GtkTreeModel *model = 
            GTK_TREE_MODEL(sct_gtk_project_tree_model_new(secretary));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), FALSE);
    
    GtkScrolledWindow *window =
            GTK_SCROLLED_WINDOW(gtk_scrolled_window_new(NULL,  NULL));
    gtk_container_add(GTK_CONTAINER(window), treeview);
    gtk_widget_show(GTK_WIDGET(treeview));
    gtk_widget_show(GTK_WIDGET(window));
    
    app->project_tree_view = treeview;
    app->project_tree_store = model;
    
    gtk_tree_view_expand_row(GTK_TREE_VIEW(treeview), 
            gtk_tree_path_new_from_string("3"), TRUE);
    
    g_signal_connect(G_OBJECT(treeview), "cursor-changed", 
            G_CALLBACK(_on_cursor_changed), app);
                
    return GTK_WIDGET(window);
}

static void _on_cursor_changed(GtkTreeView *project_treeview, gpointer data) {
    SctGtkApplication *app = data;

    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(project_treeview);
    GtkTreeIter iter;
    GtkTreeModel *model;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;
    
    gchar *path_str = gtk_tree_model_get_string_from_iter(model, &iter);

    if (strncmp(path_str, SCT_GTK_PROJECT_PATH_INBOX, 2) == 0) {
        sct_gtk_task_listview_change_content(
                GTK_TREE_VIEW(app->task_list_view), app->secretary, 
                sct_gtk_task_tree_model_show_inbox, NULL);
    } else if (strncmp(path_str, SCT_GTK_PROJECT_PATH_SCHEDULED, 2) == 0) {
        sct_gtk_task_listview_change_content(
                GTK_TREE_VIEW(app->task_list_view), app->secretary, 
                sct_gtk_task_tree_model_show_scheduled, NULL);
    } else if (strncmp(path_str, SCT_GTK_PROJECT_PATH_SCHEDULED_FOR_TODAY, 2)
             == 0) {
        sct_gtk_task_listview_change_content(
                GTK_TREE_VIEW(app->task_list_view), app->secretary, 
                sct_gtk_task_tree_model_show_scheduled_for_today, NULL);
    } else if (strncmp(path_str, SCT_GTK_PROJECT_PATH_NTH_PROJECT(0), 2) == 0) {
        GtkTreePath *path = gtk_tree_path_new_from_string(path_str);
        gint *indices = gtk_tree_path_get_indices(path);
        Project *project = secretary_get_nth_project(app->secretary, indices[1]);
        sct_gtk_task_listview_change_content(
                GTK_TREE_VIEW(app->task_list_view), app->secretary, 
                sct_gtk_task_tree_model_show_project, project);
    } else if (strncmp(path_str, SCT_GTK_PROJECT_PATH_PROJECT, 2) == 0) {
        GtkTreePath *path = gtk_tree_path_new_from_string(path_str);
        gtk_tree_view_expand_row(GTK_TREE_VIEW(project_treeview), path, TRUE);
        sct_gtk_application_select_path_on_project_treeview(
                app, SCT_GTK_PROJECT_PATH_NTH_PROJECT(0));
    }
    
    g_free(path_str);
}

