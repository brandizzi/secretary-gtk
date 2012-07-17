#include "secretary-gtk/application.h"
#include "secretary-gtk/widget.h"
#include <string.h>

SctGtkApplication *sct_gtk_application_new(Notebook *notebook) {
    SctGtkApplication *app = malloc(sizeof(SctGtkApplication));
    app->notebook = notebook;
    app->secretary = notebook_get_secretary(notebook);
    sct_gtk_widget_new(app);
    return app;
}

void sct_gtk_application_free(SctGtkApplication *application) {
 // TODO
}
