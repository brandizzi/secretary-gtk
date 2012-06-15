#include "test/test-secretary-gtk/project-tree-model.h"
#include "secretary-gtk/project-tree-model.h"

static void test_sct_gtk_project_tree_model_copy_projects(CuTest *test) {
    Secretary *secretary = secretary_new();
    Project *p1 = secretary_create_project(secretary, "My project"),
            *p2 = secretary_create_project(secretary, "Your project");
    GtkTreeModel *model = sct_gtk_project_tree_model_new(secretary);
    return;
    GtkTreeIter iter;
    gchar *name;
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, project_get_name(p1), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, project_get_name(p2), name);
    g_free(name);
}

CuSuite *test_sct_gtk_project_tree_model_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_project_tree_model_copy_projects);
}


