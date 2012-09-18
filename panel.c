#include "config.h"

#include "secretary-gtk/panel.h"
#include "secretary-gtk/perspective-tree-view.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"


GtkWidget *sct_gtk_panel_new(SctGtkApplication *app) {
    GtkWidget *paned = gtk_hpaned_new();
    
    gtk_paned_add1(GTK_PANED(paned), sct_gtk_perspective_tree_view_new(app));
    gtk_paned_add2(GTK_PANED(paned), sct_gtk_task_tree_view_new(app));

    gtk_widget_show(paned);
    
    return paned;
}

