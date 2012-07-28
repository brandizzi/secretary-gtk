#include "config.h"

#include "secretary-gtk/date-entry.h"
#include "secretary-gtk/_internal/date-entry.h"
#include "secretary-gtk/gettext.h"

#include <time.h>
#include <gtk/gtk.h>

static bool on_entry_changed(GtkWidget *entry, gpointer data);
static bool on_button_clicked(GtkWidget *button, gpointer data);
static bool on_calendar_day_selected(GtkWidget *calendar, gpointer data);
static bool on_calendar_day_selected_double_click( 
        GtkWidget *calendar, gpointer data);
static bool on_calendar_focus_out_event(
        GtkWidget *calendar, GdkEvent *event, gpointer data);

GtkWidget *sct_gtk_date_entry_new(void) {
    SctGtkDateEntryStruct *des = malloc(sizeof(SctGtkDateEntryStruct));
    
    des->calendar = gtk_calendar_new();
    des->entry = gtk_entry_new();
    des->button = gtk_button_new_with_mnemonic(_("S_elect date"));
    
    des->box = gtk_hbox_new(false, 2);
    gtk_box_pack_start(GTK_BOX(des->box), des->entry,TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(des->box), des->button, TRUE, TRUE, 0);
    
    des->calendar_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(des->calendar_window), FALSE);
    gtk_window_set_modal(GTK_WINDOW(des->calendar_window), TRUE);
    gtk_container_add(GTK_CONTAINER(des->calendar_window), des->calendar);

    des->calendar_day_selected_handler_id = g_signal_connect(
            G_OBJECT(des->calendar), "day-selected",
            G_CALLBACK(on_calendar_day_selected), des);
    g_signal_connect(
            G_OBJECT(des->calendar), "day-selected-double-click",
            G_CALLBACK(on_calendar_day_selected_double_click), des);
    g_signal_connect(
            G_OBJECT(des->calendar), "focus-out-event",
            G_CALLBACK(on_calendar_focus_out_event), des);
    des->entry_changed_handler_id = g_signal_connect(
            G_OBJECT(des->entry), "changed", 
            G_CALLBACK(on_entry_changed), des);
    g_signal_connect(
            G_OBJECT(des->button), "clicked", 
            G_CALLBACK(on_button_clicked), des);

    g_object_set_data(G_OBJECT(des->box), SCT_GTK_DATE_ENTRY_STRUCT, des);
    return des->box;
}


time_t sct_gtk_date_entry_get_date(GtkWidget *date_entry) {
    SctGtkDateEntryStruct *des = g_object_get_data(
            G_OBJECT(date_entry), SCT_GTK_DATE_ENTRY_STRUCT);
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(des->calendar), &year, &month, &day);
    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_mday = day;
    date.tm_mon  = month;
    date.tm_year = year - 1900;
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    return util_beginning_of_day(mktime(&date));
}

bool sct_gtk_date_entry_has_selected_date(GtkWidget *date_entry) {
    SctGtkDateEntryStruct *des = g_object_get_data(
            G_OBJECT(date_entry), SCT_GTK_DATE_ENTRY_STRUCT);
    const char *date_string = gtk_entry_get_text(GTK_ENTRY(des->entry));
    struct tm date;
    date_string = strptime(date_string, _("%Y-%m-%d"), &date);
    return date_string != NULL;
}

static bool on_entry_changed(GtkWidget *entry, gpointer data) {
    SctGtkDateEntryStruct *des = data;
    const char *date_string = gtk_entry_get_text(
            GTK_ENTRY(des->entry));
    struct tm date;
    date_string = strptime(date_string, _("%Y-%m-%d"), &date);
    if (date_string) {
        g_signal_handler_block(
                des->calendar, des->calendar_day_selected_handler_id);
        gtk_calendar_select_month(
                GTK_CALENDAR(des->calendar),  date.tm_mon, date.tm_year+1900);
        gtk_calendar_select_day(GTK_CALENDAR(des->calendar), date.tm_mday);
        g_signal_handler_unblock(
                des->calendar, des->calendar_day_selected_handler_id);
    }
    return false;
}

static bool on_button_clicked(GtkWidget *entry, gpointer data) {
    SctGtkDateEntryStruct *des = data;
    GtkWidget *window = gtk_widget_get_toplevel(des->box);
    gtk_window_set_transient_for(
            GTK_WINDOW(des->calendar_window), GTK_WINDOW(window));
    
    gint dx, dy;
    gtk_window_get_position(GTK_WINDOW(window), &dx, &dy);
    
    GtkAllocation allocation;
    gtk_widget_get_allocation(des->entry, &allocation);
    
    gtk_window_move(
            GTK_WINDOW(des->calendar_window), 
            allocation.x+dx, allocation.y+allocation.height*2+dy);
    
    gtk_widget_show_all(des->calendar_window);
    return false;
}

static bool on_calendar_day_selected(GtkWidget *calendar, gpointer data) {
    SctGtkDateEntryStruct *des = data;
    
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    GDate *date = g_date_new_dmy(day, month+1, year);
    char buffer[12];
    g_date_strftime(buffer, 12, _("%Y-%m-%d"), date);
    g_signal_handler_block(des->entry, des->entry_changed_handler_id);
    gtk_entry_set_text(GTK_ENTRY(des->entry), buffer);
    g_signal_handler_unblock(des->entry, des->entry_changed_handler_id);
    return false;
}

static bool on_calendar_day_selected_double_click( 
        GtkWidget *calendar, gpointer data) {
    SctGtkDateEntryStruct *des = data;
    gtk_widget_hide(des->calendar_window);
    gtk_widget_grab_focus(des->entry);
    return false;
}

static bool on_calendar_focus_out_event(
        GtkWidget *calendar, GdkEvent *event, gpointer data) {
    SctGtkDateEntryStruct *des = data;
    gtk_widget_hide(des->calendar_window);
    return false;
}

