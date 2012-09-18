#include "test/test-secretary-gtk/task-tree-model.h"
#include "secretary-gtk/task-tree-model.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_task_tree_model_has_tasks(CuTest *test) {
    Secretary *secretary = secretary_new();
    Task *t1 = secretary_create_task(secretary, "My task"),
         *t2 = secretary_create_task(secretary, "Your task"),
         *task;
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    GtkTreeIter iter;
    
    sct_gtk_task_tree_model_show_inbox(model, NULL);
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    CuAssertPtrEquals(test, task, t1);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    gtk_tree_model_get(model, &iter, SCT_GTK_TASK_TREE_MODEL_TASK_COLUMN, 
            &task, -1);
    CuAssertPtrEquals(test, task, t2);
    
    CuAssertTrue(test, ! gtk_tree_model_iter_next(model, &iter));
}



CuSuite *test_sct_gtk_task_tree_model_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_model_has_tasks);
    
    return suite;
}


