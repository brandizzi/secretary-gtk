#include "test/test-secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/new-task-dialog.h"
#include "secretary-gtk/gettext.h"

#include "time.h"

static void test_sct_gtk_new_task_dialog_create_task(CuTest *test) {
    Secretary *secretary = secretary_new();
    SctGtkNewTaskDialogStruct *ds = 
        sct_gtk_new_task_dialog_struct_new(secretary, NULL);
    
    gtk_entry_set_text(GTK_ENTRY(ds->description_entry), "My new task");
    
    Task *task = sct_gtk_new_task_dialog_struct_create_task(ds);
    CuAssertStrEquals(test, "My new task", task_get_description(task));
    
    CuAssertIntEquals(test, secretary_count_tasks(secretary, false), 1);
    CuAssertPtrEquals(test, task, secretary_get_nth_task(secretary, 0));
    CuAssertTrue(test, !task_is_scheduled(task));
    CuAssertTrue(test, !task_has_project(task));
}

static void test_sct_gtk_new_task_dialog_create_scheduled_task(CuTest *test) {
    Secretary *secretary = secretary_new();
    SctGtkNewTaskDialogStruct *ds = 
        sct_gtk_new_task_dialog_struct_new(secretary, NULL);
        
    time_t today = time(NULL);
    struct tm *date = localtime(&today);
    date->tm_year += 2; // Always in future, for assuring breakable test
    date->tm_mon = 11;
    date->tm_mday = 31;
    
    gtk_entry_set_text(GTK_ENTRY(ds->description_entry), "My new task");
    gtk_calendar_select_month(
            GTK_CALENDAR(ds->scheduled_for_calendar), 11, date->tm_year);
    gtk_calendar_select_day(GTK_CALENDAR(ds->scheduled_for_calendar), 31);
    
    Task *task = sct_gtk_new_task_dialog_struct_create_task(ds);
    CuAssertStrEquals(test, "My new task", task_get_description(task));
    
    CuAssertIntEquals(test, secretary_count_tasks(secretary, false), 1);
    CuAssertPtrEquals(test, task, secretary_get_nth_task(secretary, 0));
    CuAssertTrue(test, task_is_scheduled(task));
    CuAssertTrue(test, task_is_scheduled_for(task, mktime(date)));
    CuAssertTrue(test, !task_has_project(task));
}

CuSuite *test_sct_gtk_new_task_dialog_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_new_task_dialog_create_task);
    SUITE_ADD_TEST(suite, test_sct_gtk_new_task_dialog_create_scheduled_task);
}


