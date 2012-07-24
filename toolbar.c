#include "config.h"

#include "secretary-gtk/toolbar.h"
#include "secretary-gtk/gettext.h"

static void on_new_task_button_clicked(GtkWidget *tool_button, gpointer data);

GtkWidget *sct_gtk_toolbar_new(SctGtkApplication *app) {
    GtkToolItem *new_task_button = gtk_tool_button_new_from_stock(GTK_STOCK_NEW),
            *delete_task_button = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
    GtkWidget *toolbar = gtk_toolbar_new();

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_task_button, 0);
    g_signal_connect(G_OBJECT(new_task_button), "clicked", 
            G_CALLBACK(on_new_task_button_clicked), app);
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), delete_task_button, 1);
    
    gtk_widget_show(GTK_WIDGET(new_task_button));
    gtk_widget_show(GTK_WIDGET(delete_task_button));
    gtk_widget_show(toolbar);
    
    app->add_task_button = new_task_button;
    app->remove_task_button = delete_task_button;
    return toolbar;
}

static void on_new_task_button_clicked(GtkWidget *tool_button, gpointer data) {
    SctGtkApplication *app = data;
    gtk_dialog_run(GTK_DIALOG(app->new_task_dialog));
}

