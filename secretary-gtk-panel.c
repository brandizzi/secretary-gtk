#include "config.h"

#include "secretary-gtk-panel.h"
#include "secretary-gtk-project-treeview.h"
#include "secretary-gtk-task-listview.h"
#include "secretary-gtk-gettext.h"


GtkWidget *sct_gtk_panel_new(Secretary *secretary) {
    GtkWidget *paned = gtk_hpaned_new();
    
    gtk_paned_add1(GTK_PANED(paned), sct_gtk_project_treeview_new(secretary));
    gtk_paned_add2(GTK_PANED(paned), sct_gtk_task_listview_new(secretary));

    gtk_widget_show(paned);
    
    return paned;
}

