#ifndef _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H
# define _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#define SCT_GTK_NEW_TASK_DIALOG_STRUCT "sct-gtk-new-task-dialog-struct"

typedef struct {
    Secretary *secretary;
    GtkWidget *description_entry,
            *scheduled_for_entry,
            *project_combo_box,
            *dialog;
    GtkTreeModel *project_model;
} SctGtkNewTaskDialogStruct;    

#endif /* _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H */
