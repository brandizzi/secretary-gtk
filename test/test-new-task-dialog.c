#include "test/test-secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_new_task_dialog_create_task(CuTest *test) {
    Secretary *secretary = secretary_new();
    SctGtkNewTaskDialogStruct *ds = 
        sct_gtk_new_task_dialog_struct_new(secretary, NULL);
    
    gtk_entry_set_text(GTK_ENTRY(ds->description_entry), "My new task");
    
    Task *task = sct_gtk_new_task_dialog_struct_create_task(ds);
    CuAssertStrEquals(test, "My new task", task_get_description(task));
    
    CuAssertIntEquals(test, secretary_count_tasks(secretary, false), 1);
    CuAssertPtrEquals(test, task, secretary_get_nth_task(secretary, 0));
}

CuSuite *test_sct_gtk_new_task_dialog_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_new_task_dialog_create_task);
}


