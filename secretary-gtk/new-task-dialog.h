#ifndef _SECRETARY_GTK_NEW_TASK_DIALOG_H
# define _SECRETARY_GTK_NEW_TASK_DIALOG_H


#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#include "secretary-gtk/application.h"

typedef struct {
    Secretary *secretary;
    GtkWidget *description_entry,
            *scheduled_for_calendar,
            *scheduled_for_entry,
            *calendar_window;
} SctGtkNewTaskDialogStruct;

SctGtkNewTaskDialogStruct *sct_gtk_new_task_dialog_struct_new(
        Secretary *secretary, GtkWindow *parent);
Task *sct_gtk_new_task_dialog_struct_create_task(
        SctGtkNewTaskDialogStruct *ntds);

GtkWidget *sct_gtk_new_task_dialog_new(
        Secretary *secretary, GtkWindow *parent);

#endif /* _SECRETARY_GTK_NEW_TASK_DIALOG_H */
