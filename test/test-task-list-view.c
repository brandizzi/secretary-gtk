#include "test/test-secretary-gtk/task-list-view.h"
#include "secretary-gtk/task-listview.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_task_list_view_done_data_func(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task
    
    GtkTreeModel *model = 
            GTK_TREE_MODEL(sct_gtk_project_tree_model_new(secretary));
    GtkTreeIter iter, child;
    gchar *name;
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_COLUMN, &name, -1);
    CuAssertStrEquals(test, "", name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_COLUMN, &name, -1);
    CuAssertStrEquals(test, project_get_name(p1), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_COLUMN,  &name, -1);
    CuAssertStrEquals(test, project_get_name(p2), name);
    g_free(name);
}

CuSuite *test_sct_gtk_project_tree_model_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_project_tree_model_copy_projects);
    return suite;
}


