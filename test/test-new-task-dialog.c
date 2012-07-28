#include "test/test-secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/_internal/new-task-dialog.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include "time.h"

static void test_sct_gtk_new_task_dialog_create_task(CuTest *test) {
    Secretary *secretary = secretary_new();
    GtkWidget *dialog = sct_gtk_new_task_dialog_new(secretary, NULL);
    SctGtkNewTaskDialogStruct *ds = g_object_get_data(
            G_OBJECT(dialog), SCT_GTK_NEW_TASK_DIALOG_STRUCT);
    
    gtk_entry_set_text(GTK_ENTRY(ds->description_entry), "My new task");
    
    Task *task = sct_gtk_new_task_dialog_create_task(GTK_DIALOG(dialog));
    CuAssertStrEquals(test, "My new task", task_get_description(task));
    
    CuAssertIntEquals(test, secretary_count_tasks(secretary, false), 1);
    CuAssertPtrEquals(test, task, secretary_get_nth_task(secretary, 0));
    CuAssertTrue(test, !task_is_scheduled(task));
    CuAssertTrue(test, !task_has_project(task));
}

CuSuite *test_sct_gtk_new_task_dialog_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_new_task_dialog_create_task);
    return suite;
}


