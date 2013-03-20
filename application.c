#include "config.h"

#include "secretary-gtk/application.h"
#include "secretary-gtk/widget.h"
#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/perspective-tree-model.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/utils.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/new-project-dialog.h"

#include <string.h>

SctGtkApplication *sct_gtk_application_new(Notebook *notebook) {
    SctGtkApplication *app = malloc(sizeof(SctGtkApplication));
    app->notebook = notebook;
    app->secretary = notebook_get_secretary(notebook);

    app->widget = sct_gtk_widget_new(app);
    sct_gtk_application_select_path_on_perspective_tree_view(
            app, SCT_GTK_PROJECT_PATH_INBOX);
    
    app->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_maximize(GTK_WINDOW(app->main_window));

    app->new_task_dialog = sct_gtk_new_task_dialog_new(app->secretary, NULL); 
    app->new_project_dialog = sct_gtk_new_project_dialog_new(app->secretary, NULL);
    
    gtk_container_add(GTK_CONTAINER(app->main_window), app->widget);
    g_signal_connect(G_OBJECT(app->main_window), "delete-event", 
            G_CALLBACK(sct_gtk_quit), app->notebook);

    return app;
}

void sct_gtk_application_free(SctGtkApplication *application) {
 // TODO
}

void sct_gtk_application_select_path_on_perspective_tree_view(
        SctGtkApplication *app, const gchar *path) {
    // Selecting inbox
    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(app->project_tree_store, &iter, path);
    
    GtkTreeView *perspective_tree_view = GTK_TREE_VIEW(app->perspective_tree_view);
    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(perspective_tree_view);
    gtk_tree_selection_select_iter(selection, &iter);
    
    // emiting signal
    gtk_signal_emit_by_name(GTK_OBJECT(perspective_tree_view), "cursor-changed");
}

void sct_gtk_applicaton_refresh_task_view(SctGtkApplication *app) {
    GtkTreeView *perspective_tree_view = GTK_TREE_VIEW(
            app->perspective_tree_view);
    
    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(perspective_tree_view);
    GtkTreeIter iter;
    GtkTreeModel *model;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;
    
    GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
    gint *indices = gtk_tree_path_get_indices(path);
    switch (indices[0]) {
    case SCT_GTK_PROJECT_INDEX_INBOX:
        sct_gtk_task_tree_view_change_content(
                GTK_TREE_VIEW(app->task_tree_view),
                sct_gtk_task_tree_model_show_inbox, NULL);
        break;
    case SCT_GTK_PROJECT_INDEX_SCHEDULED:
        sct_gtk_task_tree_view_change_content(
                GTK_TREE_VIEW(app->task_tree_view),
                sct_gtk_task_tree_model_show_scheduled, NULL);
        break;
    case SCT_GTK_PROJECT_INDEX_SCHEDULED_FOR_TODAY:
        sct_gtk_task_tree_view_change_content(
                GTK_TREE_VIEW(app->task_tree_view),
                sct_gtk_task_tree_model_show_scheduled_for_today, NULL);
        break;
    case SCT_GTK_PROJECT_INDEX_PROJECT:
        if (gtk_tree_path_get_depth(path) == 1) {
            gtk_tree_view_expand_row(
                    GTK_TREE_VIEW(perspective_tree_view), path, TRUE);
            sct_gtk_application_select_path_on_perspective_tree_view(
                    app, SCT_GTK_PROJECT_PATH_NTH_PROJECT(0));
        } else {
            Project *project = secretary_get_nth_project(
                    app->secretary, indices[1]);
            sct_gtk_task_tree_view_change_content(
                    GTK_TREE_VIEW(app->task_tree_view),
                    sct_gtk_task_tree_model_show_project, project);
        }
        break;
    } 
}
