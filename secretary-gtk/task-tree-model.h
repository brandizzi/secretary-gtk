#ifndef _SECRETARY_GTK_TASK_TREE_MODEL_H
# define _SECRETARY_GTK_TASK_TREE_MODEL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary-gtk/application.h>

enum {
    SCT_GTK_TASK_DONE_COLUMN = 0,
    SCT_GTK_TASK_DESCRIPTION_COLUMN,
    SCT_GTK_TASK_PROJECT_COLUMN,
    SCT_GTK_TASK_DATE_COLUMN,
    SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN,
    SCT_GTK_TASK_COLUMN_COUNT
};

GtkTreeModel *sct_gtk_task_tree_model_new(Secretary *secretary);
Secretary *sct_gtk_task_tree_model_get_secretary(GtkTreeModel *model);

void sct_gtk_task_tree_model_show_inbox(
        GtkTreeModel *model,void *ignored_data);
void sct_gtk_task_tree_model_show_scheduled(
        GtkTreeModel *model, void *ignored_data);
void sct_gtk_task_tree_model_show_scheduled_for_today(
        GtkTreeModel *model, void *ignored_data);
void sct_gtk_task_tree_model_show_project(
        GtkTreeModel *model, void *data);
        
void sct_gtk_task_tree_model_add_task(GtkTreeModel *model, Task *task);

#endif /* _SECRETARY_GTK_PROJECT_TREE_MODEL_H */

