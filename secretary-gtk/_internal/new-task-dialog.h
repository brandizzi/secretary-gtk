#ifndef _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H
# define _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#define SCT_GTK_NEW_TASK_DIALOG_STRUCT "sct-gtk-new-task-dialog-struct"

typedef struct {
    Secretary *secretary;
    GtkWidget *description_entry,
            *scheduled_for_calendar,
            *scheduled_for_entry,
            *calendar_window,
            *dialog;
    gulong scheduled_for_calendar_day_selected_handler_id,
            scheduled_for_entry_changed_handler_id;
} SctGtkNewTaskDialogStruct;    

SctGtkNewTaskDialogStruct *sct_gtk_new_task_dialog_struct_new(
        GtkWidget *dialog, Secretary *secretary);
Task *sct_gtk_new_task_dialog_struct_create_task(
        SctGtkNewTaskDialogStruct *ntds);

#endif /* _SECRETARY_GTK_NEW_TASK_DIALOG_INTERNAL_H */
