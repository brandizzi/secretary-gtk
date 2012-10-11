#ifndef _SECRETARY_GTK_NEW_PROJECT_DIALOG_INTERNAL_H
# define _SECRETARY_GTK_NEW_PROJECT_DIALOG_INTERNAL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#define SCT_GTK_NEW_PROJECT_DIALOG_STRUCT "sct-gtk-new-project-dialog-struct"

typedef struct {
    Secretary *secretary;
    GtkWidget *name_entry,
            *dialog;
} SctGtkNewProjectDialogStruct;    

#endif /* _SECRETARY_GTK_NEW_PROJECT_DIALOG_INTERNAL_H */
