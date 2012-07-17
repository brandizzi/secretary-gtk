#include "test/test-secretary-gtk/application.h"
#include "secretary-gtk/application.h"
#include "secretary-gtk/project-tree-model.h"
#include "secretary-gtk/gettext.h"

static void test_sct_gtk_app_select_inbox(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    
    Project *project = secretary_create_project(secretary, "My project");
    
    Task *task_in_inbox = secretary_create_task(secretary, "Inbox task"),
         *task_in_project = secretary_create_task(secretary, "Project task"),
         *task_scheduled = secretary_create_task(secretary, "Scheduled task");
    secretary_move_task_to_project(secretary, project, task_in_project);
    secretary_schedule_task(secretary, task_scheduled, time(NULL));
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    // Selecting inbox
    GtkTreeIter iter;
    gtk_tree_model_get_iter_from_string(app->project_tree_store, &iter,
            SCT_GTK_PROJECT_PATH_INBOX);
    
    GtkTreeView *project_tree_view = GTK_TREE_VIEW(app->project_tree_view);
    GtkTreeSelection *selection =
            gtk_tree_view_get_selection(project_tree_view);
    gtk_tree_selection_select_iter(selection, &iter);
    // emiting signal
    gtk_signal_emit_by_name(project_tree_view, "cursor-changed");

    // Evaluating results
    GtkTreeModel *task_store = GTK_TREE_MODEL(app->task_list_store);
    gtk_tree_model_get_iter_first(task_store, &iter);
    char *name;
    gtk_tree_model_get(task_store, &iter, 1, &name, -1);
    
    CuAssertStrEquals(test, "Inbox task", name);
    
    sct_gtk_application_free(app);
}

CuSuite *test_sct_gtk_app_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_app_select_inbox);
}


