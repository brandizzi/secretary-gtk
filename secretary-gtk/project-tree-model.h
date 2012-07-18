#ifndef _SECRETARY_GTK_PROJECT_TREE_MODEL_H
# define _SECRETARY_GTK_PROJECT_TREE_MODEL_H

#include <gtk/gtk.h>
#include <secretary/secretary.h>

enum {
    SCT_GTK_PROJECT_PERSPECTIVE_COLUMN = 0,
    SCT_GTK_PROJECT_COLUMN_COUNT
};

#define SCT_GTK_PROJECT_PATH_INBOX "0"
#define SCT_GTK_PROJECT_PATH_SCHEDULED_FOR_TODAY "1"
#define SCT_GTK_PROJECT_PATH_SCHEDULED "2"
#define SCT_GTK_PROJECT_PATH_PROJECT "3"
#define SCT_GTK_PROJECT_PATH_NTH_PROJECT(n) "3:" #n

GtkTreeStore *sct_gtk_project_tree_model_new(Secretary *secretary);

#endif /* _SECRETARY_GTK_PROJECT_TREE_MODEL_H */

