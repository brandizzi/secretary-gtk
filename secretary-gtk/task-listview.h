#ifndef _SECRETARY_GTK_SECRETARY_LISTVIEW_H
# define _SECRETARY_GTK_SECRETARY_LISTVIEW_H

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#include "secretary-gtk/application.h"

enum {
    SCT_GTK_TASK_DONE_COLUMN = 0,
    SCT_GTK_TASK_DESCRIPTION_COLUMN,
    SCT_GTK_TASK_PROJECT_COLUMN,
    SCT_GTK_TASK_DATE_COLUMN,
    SCT_GTK_TASK_COLUMN_COUNT
};


GtkWidget *sct_gtk_secretary_listview_new(SctGtkApplication *app);

#endif /* _SECRETARY_GTK_SECRETARY_LISTVIEW_H */

