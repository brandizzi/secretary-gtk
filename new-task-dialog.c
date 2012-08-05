#include "config.h"

#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/_internal/new-task-dialog.h"
#include "secretary-gtk/gettext.h"
#include "secretary-gtk/utils.h"

#include "secretary-gtk/date-entry.h"
#include "secretary-gtk/project-tree-model.h"

#include <time.h>
#include <gtk/gtk.h>

static bool on_new_task_dialog_delete_event(GtkWidget *dialog, gpointer data);


GtkWidget *sct_gtk_new_task_dialog_new(
        Secretary *secretary, GtkWindow *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
            _("New task"), parent, 
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, 
            GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    
    // Creating struct and widgets
    SctGtkNewTaskDialogStruct *ntds = malloc(sizeof(SctGtkNewTaskDialogStruct));
    ntds->secretary = secretary;
    
    ntds->dialog = dialog;
    ntds->description_entry = gtk_entry_new();
    ntds->scheduled_for_entry = sct_gtk_date_entry_new();
    ntds->project_model = GTK_TREE_MODEL(
            sct_gtk_project_tree_model_new(ntds->secretary));
    ntds->project_combo_box = gtk_combo_box_new_with_model(ntds->project_model);

    GtkWidget *table = gtk_table_new(2, 2, FALSE);
    
    GtkWidget *label = gtk_label_new_with_mnemonic(_("_Description"));
    gtk_label_set_mnemonic_widget(GTK_LABEL(label), ntds->description_entry);
    gtk_table_attach(
            GTK_TABLE(table), label, 0, 1, 0, 1, GTK_SHRINK, GTK_FILL, 5, 5);
    
    gtk_table_attach(
            GTK_TABLE(table), ntds->description_entry, 1, 2, 0, 1, 
            GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);
    
    label = gtk_label_new_with_mnemonic(_("_Scheduled to"));
    gtk_label_set_mnemonic_widget(GTK_LABEL(label), ntds->scheduled_for_entry);
    gtk_table_attach(
            GTK_TABLE(table), label, 0, 1, 1, 2, 
            GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

    gtk_table_attach(
            GTK_TABLE(table), ntds->scheduled_for_entry, 1, 2, 1, 2, 
            GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);
    
    GtkWidget *ca = gtk_dialog_get_content_area(GTK_DIALOG(ntds->dialog));
    gtk_container_add(GTK_CONTAINER(ca), table);
    
    gtk_widget_show_all(ca);
    
    gtk_window_set_title(GTK_WINDOW(dialog), _("New task"));
    
    g_signal_connect(
            G_OBJECT(dialog), "delete-event", 
            G_CALLBACK(on_new_task_dialog_delete_event), NULL);
    g_signal_connect(
            G_OBJECT(dialog), "response", 
            G_CALLBACK(on_new_task_dialog_delete_event), NULL);
    
    g_object_set_data(G_OBJECT(dialog), SCT_GTK_NEW_TASK_DIALOG_STRUCT, ntds);
    g_signal_connect(
            G_OBJECT(dialog), "destroy", 
            G_CALLBACK(sct_gtk_free_struct_callback), ntds);

    return dialog;
}

Task *sct_gtk_new_task_dialog_create_task(GtkDialog *dialog) {
    SctGtkNewTaskDialogStruct *ntds = g_object_get_data(
            G_OBJECT(dialog), SCT_GTK_NEW_TASK_DIALOG_STRUCT);
    const char *description = gtk_entry_get_text(
            GTK_ENTRY(ntds->description_entry));
    Task *task = secretary_create_task(ntds->secretary, description);
    
    if (sct_gtk_date_entry_has_selected_date(ntds->scheduled_for_entry)) {
        secretary_schedule_task(
                ntds->secretary, task, 
                sct_gtk_date_entry_get_date(ntds->scheduled_for_entry));
    }
    int index = gtk_combo_box_get_active(
            GTK_COMBO_BOX(ntds->project_combo_box));
    if (index >= 0) {
        Project *project = secretary_get_nth_project(ntds->secretary, index);
        secretary_move_task_to_project(ntds->secretary, project, task);
    }
    return task;
}

static bool on_new_task_dialog_delete_event(GtkWidget *dialog, gpointer data) {
    gtk_widget_hide(dialog);
    return true;
}


