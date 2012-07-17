#ifndef _SECRETARY_GTK_SECRETARY_LISTVIEW_H
# define _SECRETARY_GTK_SECRETARY_LISTVIEW_H

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/application.h"

GtkWidget *sct_gtk_task_listview_new(SctGtkApplication *app);

#endif /* _SECRETARY_GTK_SECRETARY_LISTVIEW_H */

