#include "test/test-secretary-gtk/task-tree-view.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"

#define DATE_SIZE 20

static void test_sct_gtk_task_list_view_get_done(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task *tu1 = secretary_create_task(secretary, "1st undone task"),
         *td1 = secretary_create_task(secretary, "1st done task"),
         *tu2 = secretary_create_task(secretary, "2nd undone task"),
         *td2 = secretary_create_task(secretary, "2nd done task"),
         *task;
    task_mark_as_done(td1);
    task_mark_as_done(td2);
    
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeIter iter;
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    CuAssertTrue(test, !(gboolean)g_object_get_data(G_OBJECT(renderer), "active"));
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    CuAssertTrue(test, (gboolean)g_object_get_data(G_OBJECT(renderer), "active"));
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    CuAssertTrue(test, !(gboolean)g_object_get_data(G_OBJECT(renderer), "active"));
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    CuAssertTrue(test, (gboolean)g_object_get_data(G_OBJECT(renderer), "active"));
    
}

static void test_sct_gtk_task_list_view_get_description(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task *t1 = secretary_create_task(secretary, "1st task"),
         *t2 = secretary_create_task(secretary, "2nd task"),
         *t3 = secretary_create_task(secretary, "3rd task"),
         *t4 = secretary_create_task(secretary, "4th task"),
         *task;
    
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeIter iter;
    
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "1st task");
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "2nd task");
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "3rd task");
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "4th task");
    
}

static void test_sct_gtk_task_list_view_get_project(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task *t1 = secretary_create_task(secretary, "1st task"),
         *t2 = secretary_create_task(secretary, "2nd task"),
         *t3 = secretary_create_task(secretary, "3rd task"),
         *t4 = secretary_create_task(secretary, "4th task"),
         *task;
     Project *project1 = secretary_create_project(secretary, "Project 1"),
             *project2 = secretary_create_project(secretary, "Project 2");
     
    secretary_move_task_to_project(secretary, project1, t1);
    secretary_move_task_to_project(secretary, project2, t3);
    
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeIter iter;
    
    // Not in inbox
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "");
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "2nd task");
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "");
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "4th task");

    
    // In projects
    sct_gtk_task_tree_model_show_project(model, project1);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "Project 1");
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "1st task");
    
    sct_gtk_task_tree_model_show_project(model, project2);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "Project 2");
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "3rd task");
    
}

static void test_sct_gtk_task_list_view_get_scheduled(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task *t1 = secretary_create_task(secretary, "1st task"),
         *t2 = secretary_create_task(secretary, "2nd task"),
         *t3 = secretary_create_task(secretary, "3rd task"),
         *t4 = secretary_create_task(secretary, "4th task"),
         *task;
    Project *project1 = secretary_create_project(secretary, "Project 1"),
            *project2 = secretary_create_project(secretary, "Project 2");
     
    secretary_move_task_to_project(secretary, project1, t1);
    secretary_move_task_to_project(secretary, project2, t3);
    
    time_t today = time(NULL), future = today + 24*60*60*3;
    
    secretary_schedule_task(secretary, t1, today);
    secretary_schedule_task(secretary, t4, future);
    
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeIter iter;
    
    // Not in inbox
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "");
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "2nd task");
    
    // Scheduled
    sct_gtk_task_tree_model_show_scheduled(model, NULL);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);

    time_t t = task_get_scheduled_date(t1);
    char buffer[SCT_GTK_TASK_TREE_MODEL_DATE_SIZE];
    
    strftime(buffer, SCT_GTK_TASK_TREE_MODEL_DATE_SIZE, "%d-%m-%Y", localtime(&t));
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"),  buffer);
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "1st task");
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_list_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    t = task_get_scheduled_date(t4);
    strftime(buffer, DATE_SIZE, "%d-%m-%Y", localtime(&t));
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), buffer);
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "4th task");
    
    // Scheduled for today
    sct_gtk_task_tree_model_show_scheduled_for_today(model, NULL);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_list_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);

    t = task_get_scheduled_date(t1);
    buffer[SCT_GTK_TASK_TREE_MODEL_DATE_SIZE];
    
    strftime(buffer, SCT_GTK_TASK_TREE_MODEL_DATE_SIZE, "%d-%m-%Y", localtime(&t));
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"),  buffer);
    sct_gtk_task_list_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertStrEquals(test, 
            g_object_get_data(G_OBJECT(renderer), "text"), "1st task");
}


CuSuite *test_sct_gtk_task_list_view_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_done);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_description);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_project);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_scheduled);
    return suite;
}


