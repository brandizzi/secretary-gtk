#include "config.h"

#include "secretary-gtk/application.h"
#include "secretary-gtk/gettext.h"

#include <gtk/gtk.h>

GtkWidget *sct_gtk_new_task_panel_new(SctGtkApplication *app) {
    GtkWidget *table = gtk_hpaned_new();
    
    gtk_paned_add1(GTK_PANED(paned), sct_gtk_project_treeview_new(app));
    gtk_paned_add2(GTK_PANED(paned), sct_gtk_task_listview_new(app));

    gtk_widget_show(paned);
    
    return paned;
}


