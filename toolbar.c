
#include "config.h"

#include "secretary-gtk/toolbar.h"
#include "secretary-gtk/utils.h"
#include "secretary-gtk/gettext.h"

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/new-project-dialog.h"

static void on_new_task_button_clicked(GtkWidget *tool_button, gpointer data);
static void on_archive_task_button_clicked(GtkWidget *tool_button, gpointer data);
static void on_new_project_button_clicked(GtkWidget *tool_button, gpointer data);
static void on_new_project_button_clicked(GtkWidget *tool_button, gpointer data);

GtkWidget *sct_gtk_toolbar_new(SctGtkApplication *app) {
    GtkToolItem *new_task_button = gtk_tool_button_new_from_stock(GTK_STOCK_NEW),
            *delete_task_button = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE),
            *archive_task_button = gtk_tool_button_new_from_stock(GTK_STOCK_CLEAR),
            *new_project_button = gtk_tool_button_new_from_stock(GTK_STOCK_NEW),
            *delete_project_button = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
    GtkWidget *toolbar = gtk_toolbar_new();

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_task_button, 0);
    g_signal_connect(G_OBJECT(new_task_button), "clicked", 
            G_CALLBACK(on_new_task_button_clicked), app);
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), delete_task_button, 1);
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), archive_task_button, 2);
    g_signal_connect(G_OBJECT(archive_task_button), "clicked", 
            G_CALLBACK(on_archive_task_button_clicked), app);
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_project_button, 3);
    g_signal_connect(G_OBJECT(new_project_button), "clicked", 
            G_CALLBACK(on_new_project_button_clicked), app);
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), delete_project_button, 4);
    
    gtk_widget_show(GTK_WIDGET(new_task_button));
    gtk_widget_show(GTK_WIDGET(delete_task_button));
    gtk_widget_show(GTK_WIDGET(archive_task_button));
    gtk_widget_show(GTK_WIDGET(new_project_button));
    gtk_widget_show(GTK_WIDGET(delete_project_button));
    gtk_widget_show(toolbar);
    
    app->add_task_button = new_task_button;
    app->remove_task_button = delete_task_button;
    return toolbar;
}

// TODO to test
static void on_new_task_button_clicked(GtkWidget *tool_button, gpointer data) {
    SctGtkApplication *app = data;
    gint result = gtk_dialog_run(GTK_DIALOG(app->new_task_dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        sct_gtk_new_task_dialog_create_task(GTK_DIALOG(app->new_task_dialog));
    }
}

// TODO to test
static void on_archive_task_button_clicked(GtkWidget *tool_button, gpointer data) {
    SctGtkApplication *app = data;
    GtkTreeModel *model = app->task_tree_model;
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    
    while (valid) {
        Task *task;
        gtk_tree_model_get(model, &iter, 
                SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, &task, -1);
        if (task_is_done(task)) {
            secretary_archive_task(app->secretary, task);
        }
        valid = gtk_tree_model_iter_next(model, &iter);
    }
    sct_gtk_applicaton_refresh_task_view(app);
    notebook_save(app->notebook);
}

// TODO to test
static void on_new_project_button_clicked(GtkWidget *tool_button, gpointer data) {
    SctGtkApplication *app = data;
    gint result = gtk_dialog_run(GTK_DIALOG(app->new_project_dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        sct_gtk_new_project_dialog_create_project(GTK_DIALOG(app->new_project_dialog));
        notebook_save(app->notebook);
    }
}

