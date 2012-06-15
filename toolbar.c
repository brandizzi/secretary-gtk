#include "secretary-gtk/toolbar.h"
#include "secretary-gtk/gettext.h"

static GtkToolItem *_secretary_aware_button_new(SctGtkApplication *app,
        const gchar *stock_id) {
    GtkToolItem *button = gtk_tool_button_new_from_stock(stock_id);
    gtk_widget_show(GTK_WIDGET(button));
    return button;
}

GtkWidget *sct_gtk_toolbar_new(SctGtkApplication *app) {
    GtkToolItem *new_task_button = _secretary_aware_button_new(app, GTK_STOCK_NEW),
            *delete_task_button = _secretary_aware_button_new(app, GTK_STOCK_DELETE);
    GtkWidget *toolbar = gtk_toolbar_new();

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_task_button, 0);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), delete_task_button, 1);
    gtk_widget_show(toolbar);
    app->add_task_button = new_task_button;
    app->remove_task_button = delete_task_button;
    return toolbar;
}

