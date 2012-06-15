#include "config.h"

#include <gtk/gtk.h>

#include "secretary-gtk/application.h"
#include "secretary-gtk/utils.h"
#include "secretary-gtk/gettext.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    SctGtkApplication *app = sct_gtk_application_new();
    gtk_container_add(GTK_CONTAINER(window), app->widget);
    gtk_widget_show(window);
    
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(sct_gtk_quit),
            app->notebook);
    
    gtk_main();
    return 0;
}

