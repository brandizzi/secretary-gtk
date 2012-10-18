#include "config.h"

#include "secretary-gtk/date-cell-renderer.h"
#include "secretary-gtk/_internal/date-cell-renderer.h"
#include "secretary-gtk/gettext.h"
#include "secretary-gtk/utils.h"

#include <time.h>
#include <gtk/gtk.h>


static bool on_cell_renderer_text_edited(
    GtkCellRendererText *renderer, gchar path_string, gchar new_text,
    gpointer data);
static bool on_cell_renderer_text_notify_text(
        GObject *renderer, GParamSpec *spec, gpointer data);
static bool on_button_clicked(GtkWidget *button, gpointer data);
static bool on_calendar_day_selected(GtkWidget *calendar, gpointer data);
static bool on_calendar_day_selected_double_click( 
        GtkWidget *calendar, gpointer data);
static bool on_calendar_focus_out_event(
        GtkWidget *calendar, GdkEvent *event, gpointer data);

GtkCellRenderer *sct_gtk_date_cell_renderer_new(void) {
    SctGtkDateCellRendererStruct *des = malloc(sizeof(SctGtkDateCellRendererStruct));
    des->calendar = gtk_calendar_new();
    des->cell_renderer = gtk_cell_renderer_text_new();
    
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
    des->cell_renderer_edited_handler_id = g_signal_connect(
            G_OBJECT(des->cell_renderer), "edited", 
            G_CALLBACK(on_cell_renderer_text_edited), des);
    des->cell_renderer_notify_text_handler_id = g_signal_connect(
            G_OBJECT(des->cell_renderer), "notify::text", 
            G_CALLBACK(on_cell_renderer_text_notify_text), des);

    g_object_set_data(G_OBJECT(des->cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT, des);
    g_signal_connect(
            G_OBJECT(des->cell_renderer), "destroy", 
            G_CALLBACK(sct_gtk_free_struct_callback), des);
            
    return des->cell_renderer;
}


time_t sct_gtk_date_cell_renderer_get_date(GtkCellRenderer *date_cell_renderer) {
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(des->calendar), &year, &month, &day);
    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_mday = day;
    date.tm_mon  = month;
    date.tm_year = year - 1900;
    char buffer[12]; // TODO delete
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    return util_beginning_of_day(mktime(&date));
}

void sct_gtk_date_cell_renderer_set_date(GtkCellRenderer *date_cell_renderer, time_t date_time) {
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
    guint year, month, day;
    
    struct tm *date = localtime(&date_time);
    gtk_calendar_select_month(
            GTK_CALENDAR(des->calendar),  date->tm_mon, date->tm_year+1900);
    gtk_calendar_select_day(GTK_CALENDAR(des->calendar), date->tm_mday);
}

bool sct_gtk_date_cell_renderer_has_selected_date(GtkCellRenderer *date_cell_renderer) {
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
    const char *date_string;
    g_object_get(G_OBJECT(date_cell_renderer), "text", &date_string, NULL);
    struct tm date;
    if (date_string) {
        date_string = strptime(date_string, _("%Y-%m-%d"), &date);
    }
    return date_string != NULL;
}

static bool on_cell_renderer_text_notify_text(
        GObject *renderer, GParamSpec *spec, gpointer data) {
    SctGtkDateCellRendererStruct *des = data;
    const char *date_string;
    g_object_get(renderer, "text", &date_string, NULL);
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

static bool on_cell_renderer_text_edited(
        GtkCellRendererText *renderer, gchar path_string, gchar new_text,
        gpointer data) {
    SctGtkDateCellRendererStruct *des = data;
    const char *date_string;
    g_object_get(G_OBJECT(renderer), "text", &date_string, NULL);
    struct tm date;
    date_string = strptime(date_string, _("%Y-%m-%d"), &date);
    if (date_string) {
        g_signal_handler_block(
                G_OBJECT(des->calendar), des->calendar_day_selected_handler_id);

        gtk_calendar_select_month(
                GTK_CALENDAR(des->calendar),  date.tm_mon, date.tm_year+1900);
        gtk_calendar_select_day(GTK_CALENDAR(des->calendar), date.tm_mday);

        g_signal_handler_unblock(
                des->calendar, des->calendar_day_selected_handler_id);
    }
    return false;
}

static bool on_calendar_day_selected(GtkWidget *calendar, gpointer data) {
    SctGtkDateCellRendererStruct *des = data;
    
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    GDate *date = g_date_new_dmy(day, month+1, year);
    char buffer[12];
    g_date_strftime(buffer, 12, _("%Y-%m-%d"), date);
    
    g_signal_handler_block(
            des->cell_renderer, des->cell_renderer_edited_handler_id);
    g_signal_handler_block(
            des->cell_renderer, des->cell_renderer_notify_text_handler_id);
            
    g_object_set(G_OBJECT(des->cell_renderer), "text", buffer, NULL);
    
    g_signal_handler_unblock(
            des->cell_renderer,  des->cell_renderer_notify_text_handler_id);
    g_signal_handler_unblock(
            des->cell_renderer,  des->cell_renderer_edited_handler_id);
    return false;
}

static bool on_calendar_day_selected_double_click( 
        GtkWidget *calendar, gpointer data) {
    SctGtkDateCellRendererStruct *des = data;
    gtk_widget_hide(des->calendar_window);
    gtk_widget_grab_focus(des->cell_renderer);
    return false;
}

static bool on_calendar_focus_out_event(
        GtkWidget *calendar, GdkEvent *event, gpointer data) {
    SctGtkDateCellRendererStruct *des = data;
    gtk_widget_hide(des->calendar_window);
    return false;
}

