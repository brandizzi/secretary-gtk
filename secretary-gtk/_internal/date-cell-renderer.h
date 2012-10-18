#ifndef _SECRETARY_GTK_DATE_CELL_RENDERER_INTERNAL_H
# define _SECRETARY_GTK_DATE_CELL_RENDERER_INTERNAL_H

#include "config.h"

#include <gtk/gtk.h>
#include <secretary/secretary.h>

#define SCT_GTK_DATE_CELL_RENDERER_STRUCT "sct-gtk-date-cell-renderer-struct"

typedef struct {
    Secretary *secretary;
    GtkCellRenderer *cell_renderer;
    GtkWidget *calendar, *calendar_window;
    int calendar_day_selected_handler_id,
            cell_renderer_edited_handler_id,
            cell_renderer_notify_text_handler_id;
} SctGtkDateCellRendererStruct;    

SctGtkDateCellRendererStruct *sct_gtk_date_cell_renderer_struct_new(GtkDialog *date_entry);

#endif /* _SECRETARY_GTK_DATE_CELL_RENDERER_INTERNAL_H */
