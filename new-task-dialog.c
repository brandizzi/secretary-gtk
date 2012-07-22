#include "config.h"

#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include <gtk/gtk.h>

GtkWidget *sct_gtk_new_task_dialog_new(
        Secretary *secretary, GtkWindow *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
            _("New task"), parent, 
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, 
            GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    
    gtk_window_set_title(GTK_WINDOW(dialog), _("New task"));
}

SctGtkNewTaskDialogStruct *sct_gtk_new_task_dialog_struct_new(
        Secretary *secretary, GtkWindow *parent) {
    SctGtkNewTaskDialogStruct *ntds = malloc(sizeof(SctGtkNewTaskDialogStruct));
    ntds->secretary = secretary;
    ntds->description_entry = gtk_entry_new();
    return ntds;
}

Task *sct_gtk_new_task_dialog_struct_create_task(
        SctGtkNewTaskDialogStruct *ntds) {
    const char *description = gtk_entry_get_text(
            GTK_ENTRY(ntds->description_entry));
    Task *task = secretary_create_task(ntds->secretary, description);
}


