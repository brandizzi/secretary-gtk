#ifndef _SECRETARY_GTK_SECRETARY_LISTVIEW_H
# define _SECRETARY_GTK_SECRETARY_LISTVIEW_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/application.h"

enum {
    SCT_GTK_TASK_TREE_VIEW_DONE_COLUMN = 0,
    SCT_GTK_TASK_TREE_VIEW_DESCRIPTION_COLUMN,
    SCT_GTK_TASK_TREE_VIEW_PROJECT_COLUMN,
    SCT_GTK_TASK_TREE_VIEW_SCHEDULE_DATE_COLUMN,
    SCT_GTK_TASK_TREE_VIEW_COLUMN_COUNT
};

GtkWidget *sct_gtk_task_tree_view_new(SctGtkApplication *app);

typedef void (SctGtkChangeTaskListViewContentCallback)(
        GtkTreeModel *model, void *data);

void sct_gtk_task_tree_view_change_content(
        GtkTreeView *task_treeview,
        SctGtkChangeTaskListViewContentCallback *callback, void *data);

void sct_gtk_task_tree_view_done_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void sct_gtk_task_tree_view_description_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void sct_gtk_task_tree_view_project_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void sct_gtk_task_tree_view_scheduled_date_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);

#endif /* _SECRETARY_GTK_SECRETARY_LISTVIEW_H */

