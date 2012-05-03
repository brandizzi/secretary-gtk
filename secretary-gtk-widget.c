#include "config.h"

#include "secretary-gtk-widget.h"
#include "secretary-gtk-toolbar.h"
#include "secretary-gtk-gettext.h"

GtkWidget *sct_gtk_widget_new(Secretary *secretary) {
    GtkWidget *paned = gtk_vpaned_new();
    
    gtk_paned_add1(GTK_PANED(paned), sct_gtk_toolbar_new(secretary, NULL));
    
    GtkWidget *label = gtk_label_new(_("Oh, are you kidding me?"));
    gtk_widget_show(label);

    gtk_paned_add2(GTK_PANED(paned), label);
    gtk_widget_show(paned);
    
    return paned;
}



