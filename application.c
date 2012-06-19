#include "secretary-gtk/application.h"
#include <string.h>

SctGtkApplication *sct_gtk_application_new(Notebook *notebook) {
    SctGtkApplication *app = malloc(sizeof(SctGtkApplication));
    app->notebook = notebook;
    app->secretary = notebook_get_secretary(notebook);
    sct_gtk_widget_new(app);
    return app;
}
