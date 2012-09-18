#ifndef TEST_SCT_GTK_UTILS_H
# define TEST_SCT_GTK_UTILS_H

#include <secretary/secretary.h>
#include <glib.h>
#include <CuTest.h>

#include "secretary-gtk/application.h"

void test_sct_gtk_util_create_project_and_four_tasks(
    Secretary *secretary, Project **project, 
    Task **inbox_task, Task **scheduled_task, Task **future_task, Task **project_task);

gchar *test_sct_gtk_util_get_task_description_from_tree_view(
        SctGtkApplication *app, int index);

#endif /* TEST_SCT_GTK_UTILS_H */



