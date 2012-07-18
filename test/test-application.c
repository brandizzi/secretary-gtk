#include "test/test-secretary-gtk/application.h"
#include "test/test-secretary-gtk/test-utils.h"

#include "secretary-gtk/application.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_app_select_inbox(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project;
    Task *task_in_inbox, *task_in_project, *task_scheduled, 
            *task_scheduled_future;
    test_sct_gtk_util_create_project_and_four_tasks(secretary, &project, 
            &task_in_inbox, &task_scheduled, &task_scheduled_future,
            &task_in_project);    
            
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
        // Selecting inbox tasks
    sct_gtk_application_select_path_on_project_treeview(app, 
            SCT_GTK_PROJECT_PATH_INBOX);

    gchar *name = 
        test_sct_gtk_util_get_task_description_from_list_view(app, 0);
    
    CuAssertStrEquals(test, "Inbox task", name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 1);
    CuAssertStrEquals(test, NULL, name);
    
    sct_gtk_application_free(app);
}

static void test_sct_gtk_app_select_scheduled(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project;
     Task *task_in_inbox, *task_in_project, *task_scheduled, 
            *task_scheduled_future;
    test_sct_gtk_util_create_project_and_four_tasks(secretary, &project, 
            &task_in_inbox, &task_scheduled, &task_scheduled_future,
            &task_in_project);
            
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    // Selecting scheduled tasks
    sct_gtk_application_select_path_on_project_treeview(app, 
            SCT_GTK_PROJECT_PATH_SCHEDULED);

    gchar *name = 
        test_sct_gtk_util_get_task_description_from_list_view(app, 0);
    CuAssertStrEquals(test, "Scheduled task", name);
    g_free(name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 1);
    CuAssertStrEquals(test, "Future task", name);
    g_free(name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 2);
    CuAssertStrEquals(test, NULL, name);
    
    sct_gtk_application_free(app);
}

static void test_sct_gtk_app_select_scheduled_for_today(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project;
     Task *task_in_inbox, *task_in_project, *task_scheduled, 
            *task_scheduled_future;
    test_sct_gtk_util_create_project_and_four_tasks(secretary, &project, 
            &task_in_inbox, &task_scheduled, &task_scheduled_future,
            &task_in_project);
            
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    // Selecting scheduled for today tasks
    sct_gtk_application_select_path_on_project_treeview(app, 
            SCT_GTK_PROJECT_PATH_SCHEDULED_FOR_TODAY);

    gchar *name = 
        test_sct_gtk_util_get_task_description_from_list_view(app, 0);
    CuAssertStrEquals(test, "Scheduled task", name);
    g_free(name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 1);
    CuAssertStrEquals(test, NULL, name);
    
    sct_gtk_application_free(app);
}

static void test_sct_gtk_app_select_project_child(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project;
     Task *task_in_inbox, *task_in_project, *task_scheduled, 
            *task_scheduled_future;
    test_sct_gtk_util_create_project_and_four_tasks(secretary, &project, 
            &task_in_inbox, &task_scheduled, &task_scheduled_future,
            &task_in_project);
            
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    // Selecting scheduled for today tasks
    sct_gtk_application_select_path_on_project_treeview(app, 
            SCT_GTK_PROJECT_PATH_NTH_PROJECT(0));

    gchar *name = 
        test_sct_gtk_util_get_task_description_from_list_view(app, 0);
    CuAssertStrEquals(test, "Project task", name);
    g_free(name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 1);
    CuAssertStrEquals(test, NULL, name);
    
    sct_gtk_application_free(app);
}

static void test_sct_gtk_app_select_project_should_not_crash(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project;
     Task *task_in_inbox, *task_in_project, *task_scheduled, 
            *task_scheduled_future;
    test_sct_gtk_util_create_project_and_four_tasks(secretary, &project, 
            &task_in_inbox, &task_scheduled, &task_scheduled_future,
            &task_in_project);
            
            
    SctGtkApplication *app = sct_gtk_application_new(notebook);
   
    // Selecting scheduled for today tasks
    sct_gtk_application_select_path_on_project_treeview(app, 
            SCT_GTK_PROJECT_PATH_PROJECT);

    gchar *name = 
        test_sct_gtk_util_get_task_description_from_list_view(app, 0);
    CuAssertStrEquals(test, "Project task", name);
    g_free(name);
    
    name = test_sct_gtk_util_get_task_description_from_list_view(app, 1);
    CuAssertStrEquals(test, NULL, name);
    
    sct_gtk_application_free(app);
}

CuSuite *test_sct_gtk_app_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_project_should_not_crash);
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_inbox);
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_scheduled);
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_scheduled_for_today);
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_project_child);
}


