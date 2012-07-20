#include "config.h"

#include <gtk/gtk.h>

#include "secretary-gtk/application.h"
#include "secretary-gtk/gettext.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    
    Notebook *notebook = notebook_new("/home/adam/.secretary/secretary.notebook");
    
    gtk_init(&argc, &argv);
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    gtk_widget_show(app->main_window);
    
    gtk_main();
    return 0;
}

