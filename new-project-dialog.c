#include "config.h"

#include "secretary-gtk/new-project-dialog.h"
#include "secretary-gtk/_internal/new-project-dialog.h"
#include "secretary-gtk/gettext.h"
#include "secretary-gtk/utils.h"

#include <time.h>
#include <gtk/gtk.h>

static bool on_new_project_dialog_delete_event(GtkWidget *dialog, gpointer data);


GtkWidget *sct_gtk_new_project_dialog_new(
        Secretary *secretary, GtkWindow *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
            _("New project"), parent, 
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, 
            GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    
    // Creating struct and widgets
    SctGtkNewProjectDialogStruct *ntds = malloc(sizeof(SctGtkNewProjectDialogStruct));
    ntds->secretary = secretary;
    
    ntds->dialog = dialog;
    ntds->name_entry = gtk_entry_new();

    GtkWidget *table = gtk_table_new(2, 2, FALSE);
    
    GtkWidget *label = gtk_label_new_with_mnemonic(_("_Name"));
    gtk_label_set_mnemonic_widget(GTK_LABEL(label), ntds->name_entry);
    gtk_table_attach(
            GTK_TABLE(table), label, 0, 1, 0, 1, GTK_SHRINK, GTK_FILL, 5, 5);
    
    gtk_table_attach(
            GTK_TABLE(table), ntds->name_entry, 1, 2, 0, 1, 
            GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

    GtkWidget *ca = gtk_dialog_get_content_area(GTK_DIALOG(ntds->dialog));
    gtk_container_add(GTK_CONTAINER(ca), table);
    
    gtk_widget_show_all(ca);
    
    gtk_window_set_title(GTK_WINDOW(dialog), _("New project"));
    
    g_signal_connect(
            G_OBJECT(dialog), "delete-event", 
            G_CALLBACK(on_new_project_dialog_delete_event), NULL);
    g_signal_connect(
            G_OBJECT(dialog), "response", 
            G_CALLBACK(on_new_project_dialog_delete_event), NULL);
    
    g_object_set_data(G_OBJECT(dialog), SCT_GTK_NEW_PROJECT_DIALOG_STRUCT, ntds);
    g_signal_connect(
            G_OBJECT(dialog), "destroy", 
            G_CALLBACK(sct_gtk_free_struct_callback), ntds);

    return dialog;
}

Project *sct_gtk_new_project_dialog_create_project(GtkDialog *dialog) {
    SctGtkNewProjectDialogStruct *ntds = g_object_get_data(
            G_OBJECT(dialog), SCT_GTK_NEW_PROJECT_DIALOG_STRUCT);
    const char *name = gtk_entry_get_text(
            GTK_ENTRY(ntds->name_entry));
    Project *project = secretary_create_project(ntds->secretary, name);
    
    return project;
}

static bool on_new_project_dialog_delete_event(GtkWidget *dialog, gpointer data) {
    gtk_widget_hide(dialog);
    return true;
}


