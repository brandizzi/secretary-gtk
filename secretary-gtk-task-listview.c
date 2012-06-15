#include "config.h"

#include "secretary-gtk/task-listview.h"
#include "secretary-gtk/gettext.h"


GtkWidget *sct_gtk_task_listview_new(SctGtkApplication *app) {
    GtkWidget *treeview = gtk_tree_view_new();
    GtkCellRenderer *done_renderer = gtk_cell_renderer_toggle_new(),
            *description_renderer = gtk_cell_renderer_text_new(),
            *project_renderer = gtk_cell_renderer_combo_new(),
            *date_renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Done"), done_renderer, "value",  
            SCT_GTK_TASK_DONE_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Description"), description_renderer, "text",  
            SCT_GTK_TASK_DESCRIPTION_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Project"), project_renderer, "text",  
            SCT_GTK_TASK_PROJECT_COLUMN, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1,
            _("Scheduled to"), date_renderer, "text",  
            SCT_GTK_TASK_DATE_COLUMN, NULL);
    gtk_widget_show(treeview);
    
    app->task_list_view = treeview;
    return treeview;
}

