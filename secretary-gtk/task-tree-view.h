#ifndef _SECRETARY_GTK_SECRETARY_LISTVIEW_H
# define _SECRETARY_GTK_SECRETARY_LISTVIEW_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/application.h"

GtkWidget *sct_gtk_task_listview_new(SctGtkApplication *app);

typedef void (SctGtkChangeTaskListViewContentCallback)(
        GtkTreeModel *model, void *data);

void sct_gtk_task_listview_change_content(
        GtkTreeView *task_treeview,
        SctGtkChangeTaskListViewContentCallback *callback, void *data);

void sct_gtk_task_list_view_done_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);
void sct_gtk_task_list_view_description_cell_data_func(
        GtkTreeViewColumn *column, GtkCellRenderer *renderer, 
        GtkTreeModel *model, GtkTreeIter *iter, gpointer data);

#endif /* _SECRETARY_GTK_SECRETARY_LISTVIEW_H */

