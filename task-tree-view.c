#include "config.h"

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"

static void on_done_cell_renderer_toggled(
        GtkCellRendererToggle *renderer, gchar *path, gpointer user_data);
static void on_description_cell_renderer_edited(
        GtkCellRendererText *renderer, gchar *path, gchar *new_text, 
        gpointer user_data);
void on_project_cell_renderer_changed(GtkCellRendererCombo *renderer, 
        gchar *path_string, GtkTreeIter *new_iter, gpointer user_data);

GtkWidget *sct_gtk_task_tree_view_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *done_renderer = gtk_cell_renderer_toggle_new(),
            *description_renderer = gtk_cell_renderer_text_new(),
            *project_renderer = gtk_cell_renderer_combo_new(),
            *date_renderer = gtk_cell_renderer_text_new();
    GtkTreeModel *model = sct_gtk_task_tree_model_new(app->secretary);
            
    gtk_tree_view_insert_column_with_data_func(
            GTK_TREE_VIEW(treeview), SCT_GTK_TASK_TREE_VIEW_DONE_COLUMN,
            _("Done"), done_renderer, 
            sct_gtk_task_tree_view_done_cell_data_func, NULL, NULL);
    g_signal_connect( G_OBJECT(done_renderer), "toggled",
            G_CALLBACK(on_done_cell_renderer_toggled), app);
            
    gtk_tree_view_insert_column_with_data_func(
            GTK_TREE_VIEW(treeview), SCT_GTK_TASK_TREE_VIEW_DESCRIPTION_COLUMN,
            _("Description"), description_renderer, 
            sct_gtk_task_tree_view_description_cell_data_func, NULL, NULL);
    g_object_set(G_OBJECT(description_renderer), "editable", true, NULL);
    g_signal_connect(G_OBJECT(description_renderer), "edited",
            G_CALLBACK(on_description_cell_renderer_edited), app);

    gtk_tree_view_insert_column_with_data_func(
            GTK_TREE_VIEW(treeview), SCT_GTK_TASK_TREE_VIEW_PROJECT_COLUMN,
            _("Project"), project_renderer, 
            sct_gtk_task_tree_view_project_cell_data_func, NULL, NULL);
    g_object_set(
            G_OBJECT(project_renderer), "model", 
            sct_gtk_project_tree_model_new(app->secretary),
            "editable", true,
            "text-column", SCT_GTK_PROJECT_TREE_MODEL_NAME_COLUMN,
            "has-entry", false,
            NULL);
    g_signal_connect(G_OBJECT(project_renderer), "changed",
            G_CALLBACK(on_project_cell_renderer_changed), app);

    gtk_tree_view_insert_column_with_data_func(
            GTK_TREE_VIEW(treeview), SCT_GTK_TASK_TREE_VIEW_SCHEDULE_DATE_COLUMN,
            _("Scheduled to"), date_renderer, 
            sct_gtk_task_tree_view_scheduled_date_cell_data_func, NULL, NULL);
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), model);
    g_object_unref(model);
    
    GtkWidget *window = gtk_scrolled_window_new(NULL,  NULL);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(window), treeview);
    gtk_widget_show(GTK_WIDGET(treeview));
    gtk_widget_show(window);
    

    app->task_tree_model = model;
    app->task_tree_view = treeview;

    return window;
}

void sct_gtk_task_tree_view_change_content(
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


void sct_gtk_task_tree_view_done_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter,SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    if (task) {
        g_object_set(
                G_OBJECT(renderer), "active", (gpointer)task_is_done(task), NULL);
    }
}

void sct_gtk_task_tree_view_description_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN,  
            &task, -1);
    if (task) {
        g_object_set(
            G_OBJECT(renderer), "text", task_get_description(task), NULL);
    }
}

void sct_gtk_task_tree_view_project_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter,SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    if (task) {
        if (task_has_project(task)) {
            Project *project = task_get_project(task);
            g_object_set(
                    G_OBJECT(renderer), "text",
                    (gpointer)project_get_name(project), NULL);
        } else {
            g_object_set(
                    G_OBJECT(renderer), "text", "", NULL);
        }
    }
}

void sct_gtk_task_tree_view_scheduled_date_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data) {
    Task *task = NULL;
    gtk_tree_model_get(model, iter,SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    if (task) {
        if (task_is_scheduled(task)) {
            time_t t = task_get_scheduled_date(task);
            char *buffer = malloc(sizeof(char)*SCT_GTK_TASK_TREE_MODEL_DATE_SIZE);
            strftime(
                buffer, SCT_GTK_TASK_TREE_MODEL_DATE_SIZE,  
                _("%d-%m-%Y"), localtime(&t));
            g_object_set(G_OBJECT(renderer), "text", (gpointer)buffer, NULL);
        } else {
            g_object_set(G_OBJECT(renderer), "text", "", NULL);
        }
    }
}

static void on_done_cell_renderer_toggled(
        GtkCellRendererToggle *renderer, gchar *path_string, gpointer user_data) {
    SctGtkApplication *app = user_data;
    GtkTreeModel *model = app->task_tree_model;
    //gboolean value = gtk_cell_renderer_toggle_get_active(renderer);
    
    GtkTreeIter iter;
    GtkTreePath *path =  gtk_tree_path_new_from_string(path_string);
    gtk_tree_model_get_iter(model, &iter, path);
    
    Secretary *secretary = sct_gtk_task_tree_model_get_secretary(model);
    Task *task;
    gtk_tree_model_get(model, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    task_switch_done_status(task);
    
    notebook_save(app->notebook);
    
    g_object_set(G_OBJECT(renderer), "active", task_is_done(task), NULL);
}

static void on_description_cell_renderer_edited(
        GtkCellRendererText *renderer, gchar *path_string, gchar *new_text, 
        gpointer user_data) {
    SctGtkApplication *app = user_data;
    GtkTreeModel *model = app->task_tree_model;
    Secretary *secretary = app->secretary;
    
    GtkTreeIter iter;
    GtkTreePath *path =  gtk_tree_path_new_from_string(path_string);
    gtk_tree_model_get_iter(model, &iter, path);
    
    Task *task;
    gtk_tree_model_get(model, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    task_set_description(task, new_text);
    
    notebook_save(app->notebook);
    
    g_object_set(G_OBJECT(renderer), "text", task_get_description(task), NULL);
}

void on_project_cell_renderer_changed(GtkCellRendererCombo *renderer, 
        gchar *path_string, GtkTreeIter *new_iter, gpointer user_data) {
    SctGtkApplication *app = user_data;
    GtkTreeModel *model = app->task_tree_model;
    Secretary *secretary = app->secretary;
    
    GtkTreeIter iter;
    GtkTreePath *path =  gtk_tree_path_new_from_string(path_string);
    gtk_tree_model_get_iter(model, &iter, path);
    
    Task *task;
    gtk_tree_model_get(model, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
            
    GtkTreeModel *combo_model;
    Project *old_project = task_get_project(task), *new_project;
    g_object_get(G_OBJECT(renderer), "model", &combo_model, NULL);

    gtk_tree_model_get(combo_model, new_iter, 
            SCT_GTK_PROJECT_TREE_MODEL_PROJECT_COLUMN, &new_project, -1);
    if (new_project) {
        secretary_move_task_to_project(secretary, new_project, task);
        g_object_set(G_OBJECT(renderer), "text", project_get_name(new_project), NULL);
    } else {
        secretary_remove_task_from_project(secretary, task);
        g_object_set(G_OBJECT(renderer), "text", "", NULL);
    }
    g_signal_emit_by_name(G_OBJECT(app->perspective_tree_view), 
            "cursor-changed", app);

    notebook_save(app->notebook);
    
}

