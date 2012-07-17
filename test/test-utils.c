#include "test-secretary-gtk/test-utils.h"

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
    for (int i = 0; i < index; i++) {
        gtk_tree_model_iter_next(task_store, &iter);
    }
    if (!gtk_list_store_iter_is_valid(GTK_LIST_STORE(task_store), &iter)) {
        return NULL;
    }
    gchar *name;
    gtk_tree_model_get(task_store, &iter, 1, &name, -1);
    return name;
}
