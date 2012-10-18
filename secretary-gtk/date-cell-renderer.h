#ifndef _SECRETARY_GTK_DATE_CELL_RENDERER_H
# define _SECRETARY_GTK_DATE_CELL_RENDERER_H


#include "config.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <secretary/secretary.h>
#include <time.h>

GtkCellRenderer *sct_gtk_date_cell_renderer_new(void);
bool sct_gtk_date_cell_renderer_has_selected_date(GtkCellRenderer *date_cell_renderer);
time_t sct_gtk_date_cell_renderer_get_date(GtkCellRenderer *date_cell_renderer);
void sct_gtk_date_cell_renderer_set_date(GtkCellRenderer *date_cell_renderer, time_t date_time);

#endif /* _SECRETARY_GTK_DATE_CELL_RENDERER_H */
