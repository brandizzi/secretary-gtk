#include "config.h"

#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include <time.h>
#include <gtk/gtk.h>

static void on_scheduled_for_entry_focus_in(GtkWidget *entry, gpointer data);
static void on_scheduled_for_entry_focus_out(GtkWidget *entry, gpointer data);
static void on_scheduled_for_calendar_day_selected(
        GtkWidget *calendar, gpointer data);

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
    ntds->scheduled_for_calendar = gtk_calendar_new();
    ntds->scheduled_for_entry = gtk_entry_new();
    
    ntds->calendar_window = gtk_window_new(GTK_WINDOW_POPUP);
    gtk_container_add(
            GTK_CONTAINER(ntds->calendar_window), ntds->scheduled_for_calendar);

    g_signal_connect(
            G_OBJECT(ntds->scheduled_for_entry), "focus-in-event",
            G_CALLBACK(on_scheduled_for_entry_focus_in), ntds);
    g_signal_connect(
            G_OBJECT(ntds->scheduled_for_entry), "focus-out-event",
            G_CALLBACK(on_scheduled_for_entry_focus_out), ntds);
    g_signal_connect(
            G_OBJECT(ntds->scheduled_for_calendar), "day-selected",
            G_CALLBACK(on_scheduled_for_calendar_day_selected), ntds);
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

static void on_scheduled_for_entry_focus_in(GtkWidget *entry, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    gtk_widget_show(ntds->calendar_window);
}

static void on_scheduled_for_entry_focus_out(GtkWidget *entry, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    gtk_widget_hide(ntds->calendar_window);
}

static void on_scheduled_for_calendar_day_selected(
        GtkWidget *calendar, gpointer data) {
    SctGtkNewTaskDialogStruct *ntds = data;
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    GDate *date = g_date_new_dmy(day, month+1, year+1900);
    char buffer[12];
    g_date_strftime(buffer, 12, "%Y-%m-%d", date);
    gtk_entry_set_text(GTK_ENTRY(ntds->scheduled_for_entry), buffer);
}

