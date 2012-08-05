#include "config.h"

#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

GtkTreeStore *sct_gtk_project_tree_model_new(Secretary *secretary) {
    GtkTreeStore *model = gtk_tree_store_new(SCT_GTK_PROJECT_COLUMN_COUNT,
            G_TYPE_STRING);
    GtkTreeIter iter, child;
    
    gtk_tree_store_append(model, &child, NULL);
    gtk_tree_store_set(model, &child, SCT_GTK_PROJECT_COLUMN, "", -1);

    int n_projects = secretary_count_projects(secretary);
    for (int i = 0; i < n_projects; i++) {
        Project *project = secretary_get_nth_project(secretary, i);
        gtk_tree_store_append(model, &child, NULL);
        gtk_tree_store_set(model, &child, SCT_GTK_PROJECT_COLUMN,
                project_get_name(project), -1);
    }
    return model;
}
