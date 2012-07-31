#ifndef _SECRETARY_GTK_DATE_ENTRY_H
# define _SECRETARY_GTK_DATE_ENTRY_H


#include "config.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <secretary/secretary.h>
#include <time.h>

GtkWidget *sct_gtk_date_entry_new(void);
bool sct_gtk_date_entry_has_selected_date(GtkWidget *date_entry);
time_t sct_gtk_date_entry_get_date(GtkWidget *date_entry);
void sct_gtk_date_entry_set_date(GtkWidget *date_entry, time_t date_time);

#endif /* _SECRETARY_GTK_DATE_ENTRY_H */
