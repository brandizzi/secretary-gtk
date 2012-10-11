#ifndef _SECRETARY_GTK_NEW_PROJECT_DIALOG_H
# define _SECRETARY_GTK_NEW_PROJECT_DIALOG_H


#include "config.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <secretary/secretary.h>

GtkWidget *sct_gtk_new_project_dialog_new(Secretary *secretary, GtkWindow *parent);
Project *sct_gtk_new_project_dialog_create_project(GtkDialog *dialog);

#endif /* _SECRETARY_GTK_NEW_PROJECT_DIALOG_H */
