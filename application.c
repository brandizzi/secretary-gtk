#include "secretary-gtk/application.h"
#include <string.h>

SctGtkApplication *sct_gtk_application_new(void) {
    SctGtkApplication *app = malloc(sizeof(SctGtkApplication));
    app->notebook = notebook_new("/home/adam/.secretary/secretary.notebook");
    sct_gtk_widget_new(app);
    return app;
}
