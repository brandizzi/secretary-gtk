#include <gtk/gtk.h>
#include <secretary/notebook.h>
#include <secretary-gtk-widget.h>
#include <secretary-gtk-utils.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    Notebook *notebook = notebook_new("/home/adam/.secretary/secretary.notebook");
    Secretary *secretary = notebook_get_secretary(notebook);
    gtk_container_add(GTK_CONTAINER(window), sct_gtk_widget_new(secretary));
    gtk_widget_show(window);
    
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(sct_gtk_quit),
            notebook);
    
    gtk_main();
    return 0;
}

