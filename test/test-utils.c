#include "test-secretary-gtk/test-utils.h"
#include "secretary-gtk/task-tree-view.h"

void test_sct_gtk_util_create_project_and_four_tasks(
    Secretary *secretary, Project **project, 
    Task **inbox_task, Task **scheduled_task, Task **future_task,
    Task **project_task) {
    
    *project = secretary_create_project(secretary, "My project");
    
    *inbox_task = secretary_create_task(secretary, "Inbox task");
    *future_task = secretary_create_task(secretary, "Future task");
    *project_task = secretary_create_task(secretary, "Project task");
    *scheduled_task = secretary_create_task(secretary, "Scheduled task");
    
    secretary_move_task_to_project(secretary, *project, *project_task);
    secretary_schedule_task(secretary, *scheduled_task, time(NULL));
    secretary_schedule_task(secretary, *future_task, time(NULL)+24*60*60*10);
}

gchar *test_sct_gtk_util_get_task_description_from_list_view(
        SctGtkApplication *app, int index) {
    // Evaluating results
    GtkTreeIter iter;
    GtkTreeModel *task_store = app->task_list_store;
    gtk_tree_model_get_iter_first(task_store, &iter);
    char *description;
    
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    
    for (int i = 0; i < index; i++) {
        gtk_tree_model_iter_next(task_store, &iter);
    }
    if (!gtk_list_store_iter_is_valid(GTK_LIST_STORE(task_store), &iter)) {
        return NULL;
    }
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, task_store, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &description, NULL);
    return description;
}

