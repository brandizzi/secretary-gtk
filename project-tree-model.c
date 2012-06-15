#include "secretary-gtk/project-tree-model.h"

GtkWidget *sct_gtk_project_tree_model_new(Secretary *secretary) {
    GtkTreeStore *model = gtk_tree_store_new(SCT_GTK_PROJECT_COLUMN_COUNT,
            G_TYPE_STRING);
    int n_projects = secretary_count_projects(secretary);

    for (int i = 0; i < n_projects; i++) {
        Project *project = secretary_get_nth_project(secretary, i);
        GtkTreeIter iter;
        gtk_tree_store_append(model, &iter, NULL);
        gtk_tree_store_set(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                project_get_name(project), -1);
    }
    return model;
}
