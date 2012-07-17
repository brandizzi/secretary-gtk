#include "test/test-secretary-gtk/project-tree-model.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_project_tree_model_copy_projects(CuTest *test) {
    Secretary *secretary = secretary_new();
    Project *p1 = secretary_create_project(secretary, "My project"),
            *p2 = secretary_create_project(secretary, "Your project");
    GtkTreeModel *model = 
            GTK_TREE_MODEL(sct_gtk_project_tree_model_new(secretary));
    GtkTreeIter iter, child;
    gchar *name;
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, _("Inbox"), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, _("For today"), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, _("Scheduled"), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, _("Projects"), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_children(model, &child, &iter));
    gtk_tree_model_get(model, &child, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, project_get_name(p1), name);
    g_free(name);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &child));
    gtk_tree_model_get(model, &child, SCT_GTK_PROJECT_PERSPECTIVE_COLUMN, 
            &name, -1);
    CuAssertStrEquals(test, project_get_name(p2), name);
    g_free(name);
}

CuSuite *test_sct_gtk_project_tree_model_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_project_tree_model_copy_projects);
}


