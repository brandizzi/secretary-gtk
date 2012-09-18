#include "test/test-secretary-gtk/task-tree-view.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"

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

CuSuite *test_sct_gtk_task_list_view_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_done);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_list_view_get_description);
    return suite;
}

