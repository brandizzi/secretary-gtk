#ifndef _SECRETARY_GTK_TASK_TREE_MODEL_H
# define _SECRETARY_GTK_TASK_TREE_MODEL_H

#include <gtk/gtk.h>
#include <secretary-gtk/application.h>

enum {
    SCT_GTK_TASK_DONE_COLUMN = 0,
    SCT_GTK_TASK_DESCRIPTION_COLUMN,
    SCT_GTK_TASK_PROJECT_COLUMN,
    SCT_GTK_TASK_DATE_COLUMN,
    SCT_GTK_TASK_COLUMN_COUNT
};

GtkListStore *sct_gtk_task_tree_model_new(SctGtkApplication *app);

void sct_gtk_task_tree_model_show_inbox(
        GtkListStore *model, Secretary *secretary, void *ignored_data);
void sct_gtk_task_tree_model_show_scheduled(
        GtkListStore *model, Secretary *secretary, void *ignored_data);
        
void sct_gtk_task_tree_model_add_task(GtkListStore *model, Task *task);

#endif /* _SECRETARY_GTK_PROJECT_TREE_MODEL_H */

