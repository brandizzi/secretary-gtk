#ifndef _SECRETARY_GTK_NEW_TASK_DIALOG_H
# define _SECRETARY_GTK_NEW_TASK_DIALOG_H


#include "config.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <secretary/secretary.h>

GtkWidget *sct_gtk_new_task_dialog_new(Secretary *secretary, GtkWindow *parent);
Task *sct_gtk_new_task_dialog_create_task(GtkDialog *dialog);

#endif /* _SECRETARY_GTK_NEW_TASK_DIALOG_H */
