#include "config.h"

#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

GtkTreeStore *sct_gtk_project_tree_model_new(Secretary *secretary) {
    GtkTreeStore *model = gtk_tree_store_new(SCT_GTK_PROJECT_COLUMN_COUNT,
            G_TYPE_STRING);
    GtkTreeIter iter, child;
    gtk_tree_store_append(model, &iter, NULL);
    gtk_tree_store_set(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                _("Inbox"), -1);
    gtk_tree_store_append(model, &iter, NULL);
    gtk_tree_store_set(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                _("For today"), -1);
    gtk_tree_store_append(model, &iter, NULL);
    gtk_tree_store_set(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                _("Scheduled"), -1);
    gtk_tree_store_append(model, &iter, NULL);
    gtk_tree_store_set(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                _("Projects"), -1);

    int n_projects = secretary_count_projects(secretary);
    for (int i = 0; i < n_projects; i++) {
        Project *project = secretary_get_nth_project(secretary, i);
        gtk_tree_store_append(model, &child, &iter);
        gtk_tree_store_set(model, &child, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN,
                project_get_name(project), -1);
    }
    return model;
}
