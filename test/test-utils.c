#include "test-secretary-gtk/test-utils.h"

void test_sct_gtk_util_create_project_and_three_tasks(
    Secretary *secretary, Project **project, 
    Task **inbox_task, Task **scheduled_task, Task **project_task) {
    
    *project = secretary_create_project(secretary, "My project");
    
    *inbox_task = secretary_create_task(secretary, "Inbox task");
    *project_task = secretary_create_task(secretary, "Project task");
    *scheduled_task = secretary_create_task(secretary, "Scheduled task");
    
    secretary_move_task_to_project(secretary, *project, *project_task);
    secretary_schedule_task(secretary, *scheduled_task, time(NULL));
}

gchar *test_sct_gtk_util_get_first_task_description_from_list_view(
        SctGtkApplication *app) {
    // Evaluating results
    GtkTreeIter iter;
    GtkTreeModel *task_store = GTK_TREE_MODEL(app->task_list_store);
    gtk_tree_model_get_iter_first(task_store, &iter);
    gchar *name;
    gtk_tree_model_get(task_store, &iter, 1, &name, -1);
    return name;
}

