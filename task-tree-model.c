#include "secretary-gtk/task-tree-model.h"

#define DATE_SIZE 12

GtkListStore *sct_gtk_task_tree_model_new(SctGtkApplication *app) {
    GtkListStore *model = gtk_list_store_new(SCT_GTK_TASK_COLUMN_COUNT,
            G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    Secretary *secretary = notebook_get_secretary(app->notebook);
    int n_tasks = secretary_count_tasks(secretary, false)+secretary_count_tasks(secretary, true);

    for (int i = 0; i < n_tasks; i++) {
        Task *task = secretary_get_nth_task(secretary, i);
        GtkTreeIter iter;
        gtk_list_store_append(model, &iter);
        gtk_list_store_set(model, &iter, SCT_GTK_TASK_DONE_COLUMN,
                task_is_done(task), -1);

        const char *description = task_get_description(task);
        gtk_list_store_set(model, &iter, SCT_GTK_TASK_DESCRIPTION_COLUMN,
                description, -1);
        free(description);
    
        Project *project = task_get_project(task);
        gtk_list_store_set(model, &iter, SCT_GTK_TASK_PROJECT_COLUMN,
                project? project_get_name(project) : "" , -1);
        char buffer[DATE_SIZE] = "";
        if (task_is_scheduled(task)) {
            time_t secs = task_get_scheduled_date(task);
            strftime(buffer, DATE_SIZE, "%d-%m-%Y", localtime(&secs));
        }
        gtk_list_store_set(model, &iter, SCT_GTK_TASK_DATE_COLUMN,
                buffer, -1);
    }
    return model;
}
