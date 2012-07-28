#ifndef _SECRETARY_GTK_DATE_ENTRY_H
# define _SECRETARY_GTK_DATE_ENTRY_H


#include "config.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <secretary/secretary.h>
#include <time.h>

GtkWidget *sct_gtk_date_entry_new(void);
time_t sct_gtk_date_entry_get_date(GtkWidget *date_entry);

#endif /* _SECRETARY_GTK_DATE_ENTRY_H */
