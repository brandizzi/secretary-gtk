#include "config.h"

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/task-listview.h"
#include "secretary-gtk/gettext.h"


GtkWidget *sct_gtk_task_listview_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *done_renderer = gtk_cell_renderer_toggle_new(),
            *description_renderer = gtk_cell_renderer_text_new(),
            *project_renderer = gtk_cell_renderer_combo_new(),
            *date_renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Done"), done_renderer, "active",  
            SCT_GTK_TASK_DONE_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Description"), description_renderer, "text",  
            SCT_GTK_TASK_DESCRIPTION_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Project"), project_renderer, "text",  
            SCT_GTK_TASK_PROJECT_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Scheduled to"), date_renderer, "text",  
            SCT_GTK_TASK_DATE_COLUMN, NULL);
    
    GtkTreeModel *model = GTK_TREE_MODEL(
            sct_gtk_task_tree_model_new(app->secretary));
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);
    
    GtkWidget *window = gtk_scrolled_window_new(NULL,  NULL);
    gtk_container_add(GTK_CONTAINER(window), treeview);
    gtk_widget_show(GTK_WIDGET(treeview));
    gtk_widget_show(window);
    

    app->task_list_store = model;
    app->task_list_view = treeview;

    return window;
}

void sct_gtk_task_listview_change_content(
        GtkTreeView *task_treeview,
        SctGtkChangeTaskListViewContentCallback *callback, void *data) {
    GtkTreeModel *model = 
            gtk_tree_view_get_model(GTK_TREE_VIEW(task_treeview));
    g_object_ref(model);
    gtk_tree_view_set_model(GTK_TREE_VIEW(task_treeview), NULL);
    callback(model, data);
    gtk_tree_view_set_model(GTK_TREE_VIEW(task_treeview), model);
    g_object_unref(model);
}


void sct_gtk_task_list_view_done_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter,SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    if (task) {
        g_object_set_data(
                G_OBJECT(renderer), "active", (gpointer)task_is_done(task));
    }
}

void sct_gtk_task_list_view_description_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter,SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    if (task) {
        g_object_set_data(
                G_OBJECT(renderer), "text",
                (gpointer)task_get_description(task));
    }
}

