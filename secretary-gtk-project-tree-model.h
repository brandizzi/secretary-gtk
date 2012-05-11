#ifndef _SECRETARY_GTK_PROJECT_TREE_MODEL_H
# define _SECRETARY_GTK_PROJECT_TREE_MODEL_H

#include <gtk/gtk.h>
#include <secretary/secretary.h>

enum {
    SCT_GTK_PROJECT_PERSPECTIVE_COLUMN = 0,
    SCT_GTK_PROJECT_COLUMN_COUNT
};

GtkWidget *sct_gtk_project_tree_model_new(Secretary *secretary);

#endif /* _SECRETARY_GTK_PROJECT_TREE_MODEL_H */

