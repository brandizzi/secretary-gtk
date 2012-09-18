#include "config.h"

#include "secretary-gtk/task-tree-model.h"

static void _sct_gtk_task_tree_model_show_all(GtkTreeModel *model, Secretary *secretary);

GtkTreeModel *sct_gtk_task_tree_model_new(Secretary *secretary) {
    GtkListStore *model = gtk_list_store_new(SCT_GTK_TASK_COLUMN_COUNT,
            G_TYPE_POINTER);
    g_object_set_data(G_OBJECT(model), "secretary", secretary);
    return GTK_TREE_MODEL(model);
}

Secretary *sct_gtk_task_tree_model_get_secretary(GtkTreeModel *model) {
    return g_object_get_data(G_OBJECT(model), "secretary");
}

void sct_gtk_task_tree_model_show_inbox(GtkTreeModel *model, void *data) {
    Secretary *secretary = g_object_get_data(G_OBJECT(model), "secretary");
    int n_tasks = secretary_count_inbox_tasks(secretary, false);
    gtk_list_store_clear(GTK_LIST_STORE(model));
    for (int i = 0; i < n_tasks; i++) {
        Task *task = secretary_get_nth_inbox_task(secretary, i, false);
        sct_gtk_task_tree_model_add_task(model, task);
    }
}

void sct_gtk_task_tree_model_show_scheduled_for_today(
        GtkTreeModel *model, void *data) {
    Secretary *secretary = g_object_get_data(G_OBJECT(model), "secretary");
    int n_tasks = secretary_count_tasks_scheduled_for_today(secretary, false);
    gtk_list_store_clear(GTK_LIST_STORE(model));
    for (int i = 0; i < n_tasks; i++) {
        Task *task = secretary_get_nth_task_scheduled_for_today(
                secretary, i, false);
        sct_gtk_task_tree_model_add_task(model, task);
    }
}

void sct_gtk_task_tree_model_show_scheduled(GtkTreeModel *model, void *data) {
    Secretary *secretary = g_object_get_data(G_OBJECT(model), "secretary");
    int n_tasks = secretary_count_tasks_scheduled(secretary, false);
    gtk_list_store_clear(GTK_LIST_STORE(model));
    for (int i = 0; i < n_tasks; i++) {
        Task *task = secretary_get_nth_task_scheduled(secretary, i, false);
        sct_gtk_task_tree_model_add_task(model, task);
    }
}

void sct_gtk_task_tree_model_show_project(GtkTreeModel *model, void *data) {
    Secretary *secretary = g_object_get_data(G_OBJECT(model), "secretary");
    Project *project = data;
    int n_tasks = project_count_tasks(project, false);
    gtk_list_store_clear(GTK_LIST_STORE(model));
    for (int i = 0; i < n_tasks; i++) {
        Task *task = project_get_nth_task(project, i, false);
        sct_gtk_task_tree_model_add_task(model, task);
    }
}

void sct_gtk_task_tree_model_add_task(GtkTreeModel *model, Task *task) {
    GtkListStore *store = GTK_LIST_STORE(model);
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    
    gtk_list_store_set(store, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN,
            task, -1);
}


static void _sct_gtk_task_tree_model_show_all(GtkTreeModel *model, Secretary *secretary) {
    gtk_list_store_clear(GTK_LIST_STORE(model));

    int n_tasks = secretary_count_tasks(secretary, false)+secretary_count_tasks(secretary, true);
    for (int i = 0; i < n_tasks; i++) {
        Task *task = secretary_get_nth_task(secretary, i);
        sct_gtk_task_tree_model_add_task(model, task);
    }
}
