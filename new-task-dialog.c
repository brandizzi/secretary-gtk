#include "config.h"

#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include <time.h>
#include <gtk/gtk.h>

static bool on_scheduled_for_entry_changed(
        GtkWidget *entry, gpointer data);
static bool on_scheduled_for_button_clicked(
        GtkWidget *button, gpointer data);
static bool on_scheduled_for_calendar_day_selected(
        GtkWidget *calendar, gpointer data);
static bool on_scheduled_for_calendar_day_selected_double_click(
        GtkWidget *calendar, gpointer data);

GtkWidget *sct_gtk_new_task_dialog_new(
        Secretary *secretary, GtkWindow *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
            _("New task"), parent, 
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, 
            GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, NULL);
    
    gtk_window_set_title(GTK_WINDOW(dialog), _("New task"));
    return dialog;
}

SctGtkNewTaskDialogStruct *sct_gtk_new_task_dialog_struct_new(
        Secretary *secretary, GtkWindow *parent) {
    SctGtkNewTaskDialogStruct *ntds = malloc(sizeof(SctGtkNewTaskDialogStruct));
    ntds->secretary = secretary;
    
    ntds->dialog = sct_gtk_new_task_dialog_new(secretary, parent);
    
    ntds->description_entry = gtk_entry_new();
    ntds->scheduled_for_calendar = gtk_calendar_new();
    ntds->scheduled_for_entry = gtk_entry_new();

    GtkWidget *scheduled_for_button = gtk_button_new_with_mnemonic(
            _("S_elect date"));
    g_signal_connect(
            G_OBJECT(scheduled_for_button), "clicked", 
            G_CALLBACK(on_scheduled_for_button_clicked), ntds);
            
    GtkWidget *scheduled_for_box = gtk_hbox_new(false, 2);
    gtk_box_pack_start(
            GTK_BOX(scheduled_for_box), ntds->scheduled_for_entry, 
            TRUE, TRUE, 0);
    gtk_box_pack_end(
            GTK_BOX(scheduled_for_box), scheduled_for_button, TRUE, TRUE, 0);
    

    
    ntds->calendar_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_transient_for(
            GTK_WINDOW(ntds->calendar_window), GTK_WINDOW(ntds->dialog));
    gtk_window_set_decorated(GTK_WINDOW(ntds->calendar_window), FALSE);
    gtk_window_set_modal(GTK_WINDOW(ntds->calendar_window), TRUE);
    gtk_container_add(
            GTK_CONTAINER(ntds->calendar_window), ntds->scheduled_for_calendar);

    ntds->scheduled_for_calendar_day_selected_handler_id = g_signal_connect(
            G_OBJECT(ntds->scheduled_for_calendar), "day-selected",
            G_CALLBACK(on_scheduled_for_calendar_day_selected), ntds);
    g_signal_connect(
            G_OBJECT(ntds->scheduled_for_calendar), "day-selected-double-click",
            G_CALLBACK(on_scheduled_for_calendar_day_selected_double_click),
            ntds);
    ntds->scheduled_for_entry_changed_handler_id = g_signal_connect(
            G_OBJECT(ntds->scheduled_for_entry), "changed",
            G_CALLBACK(on_scheduled_for_entry_changed), ntds);
            
    GtkWidget *table = gtk_table_new(2, 2, TRUE);
    
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
            GTK_TABLE(table), scheduled_for_box, 1, 2, 1, 2, 
            GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);
    
    GtkWidget *ca = gtk_dialog_get_content_area(GTK_DIALOG(ntds->dialog));
    gtk_container_add(GTK_CONTAINER(ca), table);
    
    gtk_widget_show_all(ca);
    
    return ntds;
}

Task *sct_gtk_new_task_dialog_struct_create_task(
        SctGtkNewTaskDialogStruct *ntds) {
    const char *description = gtk_entry_get_text(
            GTK_ENTRY(ntds->description_entry));
    Task *task = secretary_create_task(ntds->secretary, description);
    
    const char *date_string = gtk_entry_get_text(
            GTK_ENTRY(ntds->scheduled_for_entry));
    struct tm date;
    date_string = strptime(date_string, "%Y-%m-%d", &date);
    if (date_string) {
        secretary_schedule_task(ntds->secretary, task, mktime(&date));
    }
    return task;
}

static bool on_scheduled_for_entry_changed(
        GtkWidget *entry, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    const char *date_string = gtk_entry_get_text(
            GTK_ENTRY(ntds->scheduled_for_entry));
    struct tm date;
    date_string = strptime(date_string, "%Y-%m-%d", &date);
    if (date_string) {
        g_signal_handler_block(
                ntds->scheduled_for_calendar, 
                ntds->scheduled_for_calendar_day_selected_handler_id);
        gtk_calendar_select_month(
                GTK_CALENDAR(ntds->scheduled_for_calendar), 
                date.tm_mon, date.tm_year);
        gtk_calendar_select_day(
                GTK_CALENDAR(ntds->scheduled_for_calendar), date.tm_mday);
        g_signal_handler_unblock(
                ntds->scheduled_for_calendar, 
                ntds->scheduled_for_calendar_day_selected_handler_id);
    }
    return false;
}
static bool on_scheduled_for_button_clicked(
        GtkWidget *entry, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    gint dx, dy;
    gtk_window_get_position(GTK_WINDOW(ntds->dialog), &dx, &dy);
    
    GtkAllocation allocation;
    gtk_widget_get_allocation(ntds->scheduled_for_entry, &allocation);
    
    gtk_window_move(
            GTK_WINDOW(ntds->calendar_window), 
            allocation.x+dx, allocation.y+allocation.height*2+dy);
    
    gtk_widget_show_all(ntds->calendar_window);
    return false;
}

static bool on_scheduled_for_calendar_day_selected(
        GtkWidget *calendar, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    GDate *date = g_date_new_dmy(day, month+1, year);
    char buffer[12];
    g_date_strftime(buffer, 12, "%Y-%m-%d", date);
    g_signal_handler_block(
            ntds->scheduled_for_entry, 
            ntds->scheduled_for_entry_changed_handler_id);
    gtk_entry_set_text(GTK_ENTRY(ntds->scheduled_for_entry), buffer);
    g_signal_handler_unblock(
            ntds->scheduled_for_entry, 
            ntds->scheduled_for_entry_changed_handler_id);
    return false;
}

static bool on_scheduled_for_calendar_day_selected_double_click(
        GtkWidget *calendar, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    gtk_widget_hide(ntds->calendar_window);
    gtk_widget_grab_focus(ntds->scheduled_for_entry);
    return false;
}

