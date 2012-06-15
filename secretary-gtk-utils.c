#include "secretary-gtk/utils.h"
#include "secretary-gtk/gettext.h"

#include <secretary/notebook.h>

GtkWidget *sct_gtk_quit(GtkWidget *widget, GdkEvent *event, gpointer data) {
    Notebook *notebook = data;
    g_print(_("My notebook is %s\n"), notebook->filename);
    gtk_main_quit();
    return FALSE;
}
