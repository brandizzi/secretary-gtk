#ifndef _SECRETARY_GTK_DATE_ENTRY_INTERNAL_H
# define _SECRETARY_GTK_DATE_ENTRY_INTERNAL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#define SCT_GTK_DATE_ENTRY_STRUCT "sct-gtk-new-task-dialog-struct"

typedef struct {
    Secretary *secretary;
    GtkWidget *entry,
            *calendar,
            *button,
            *calendar_window,
            *box;
    int calendar_day_selected_handler_id,
            entry_changed_handler_id;
} SctGtkDateEntryStruct;    

SctGtkDateEntryStruct *sct_gtk_date_entry_struct_new(GtkDialog *date_entry);

#endif /* _SECRETARY_GTK_DATE_ENTRY_INTERNAL_H */
