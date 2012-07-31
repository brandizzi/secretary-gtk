#include "test/test-secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/_internal/new-task-dialog.h"
#include "secretary-gtk/date-entry.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include "time.h"

static void test_sct_gtk_new_task_dialog_select_date_schedule_task(
        CuTest *test) {
    Secretary *secretary = secretary_new();
    GtkWidget *dialog = sct_gtk_new_task_dialog_new(secretary, NULL);
    SctGtkNewTaskDialogStruct *ds = g_object_get_data(
            G_OBJECT(dialog), SCT_GTK_NEW_TASK_DIALOG_STRUCT);
        
    time_t today = time(NULL);
    struct tm date = *localtime(&today);
    date.tm_year += 2; // Always in future, for assuring breakable test
    date.tm_mon = 11;
    date.tm_mday = 31;
    
    gtk_entry_set_text(GTK_ENTRY(ds->description_entry), "My new task");
    sct_gtk_date_entry_set_date(ds->scheduled_for_entry, mktime(&date));
    
    Task *task = sct_gtk_new_task_dialog_create_task(GTK_DIALOG(dialog));
    CuAssertStrEquals(test, "My new task", task_get_description(task));
    
    CuAssertIntEquals(test, secretary_count_tasks(secretary, false), 1);
    CuAssertPtrEquals(test, task, secretary_get_nth_task(secretary, 0));
    CuAssertTrue(test, task_is_scheduled(task));
    CuAssertTrue(test, task_is_scheduled_for(task, mktime(&date)));
    CuAssertTrue(test, !task_has_project(task));
}



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
    SUITE_ADD_TEST(suite, 
            test_sct_gtk_new_task_dialog_select_date_schedule_task);
    return suite;
}


