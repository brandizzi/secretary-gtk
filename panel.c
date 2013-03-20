#include "config.h"

#include "secretary-gtk/panel.h"
#include "secretary-gtk/perspective-tree-view.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"


GtkWidget *sct_gtk_panel_new(SctGtkApplication *app) {
    GtkWidget *paned = gtk_hpaned_new(),
              *perspective_tree_view = sct_gtk_perspective_tree_view_new(app),
              *task_tree_view = sct_gtk_task_tree_view_new(app);

    gtk_widget_set_size_request(perspective_tree_view, 300, 600);
    gtk_widget_set_size_request(task_tree_view, 600, 600);

    gtk_paned_add1(GTK_PANED(paned), perspective_tree_view);
    gtk_paned_add2(GTK_PANED(paned), task_tree_view);


    gtk_widget_show(paned);
    
    return paned;
}

