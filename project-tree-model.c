#include "config.h"

#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

GtkTreeModel *sct_gtk_project_tree_model_new(Secretary *secretary) {
    GtkTreeStore *model = gtk_tree_store_new(
            SCT_GTK_PROJECT_TREE_MODEL_COLUMN_COUNT,
            G_TYPE_STRING, G_TYPE_POINTER);
    GtkTreeIter iter, child;
    
    gtk_tree_store_append(model, &child, NULL);
    gtk_tree_store_set(
            model, &child, SCT_GTK_PROJECT_TREE_MODEL_NAME_COLUMN, "", -1);
    gtk_tree_store_set(
            model, &child, SCT_GTK_PROJECT_TREE_MODEL_PROJECT_COLUMN, NULL, -1);

    int n_projects = secretary_count_projects(secretary);
    for (int i = 0; i < n_projects; i++) {
        Project *project = secretary_get_nth_project(secretary, i);
        gtk_tree_store_append(model, &child, NULL);
        gtk_tree_store_set(
                model, &child, SCT_GTK_PROJECT_TREE_MODEL_PROJECT_COLUMN,
                project, -1);
        gtk_tree_store_set(model, &child, SCT_GTK_PROJECT_TREE_MODEL_NAME_COLUMN,
                project_get_name(project), -1);
    }
    return GTK_TREE_MODEL(model);
}
