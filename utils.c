#include "config.h"

#include "secretary-gtk/utils.h"
#include "secretary-gtk/gettext.h"

#include <secretary/notebook.h>

GtkWidget *sct_gtk_quit(GtkWidget *widget, GdkEvent *event, gpointer data) {
    Notebook *notebook = data;
    g_print(_("My notebook is %s\n"), notebook->filename);
    gtk_main_quit();
    return FALSE;
}

time_t sct_gtk_get_time_from_string(const char *date_string) {
    struct tm date;
    date_string = strptime(date_string, "%Y-%m-%d", &date);
    if (date_string) {
        return mktime(&date);
    } else {
        return SCT_GTK_INVALID_DATE;
    }
}
