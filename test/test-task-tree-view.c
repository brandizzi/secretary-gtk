#include "test/test-secretary-gtk/task-tree-view.h"
#include "secretary-gtk/task-tree-view.h"
#include "secretary-gtk/gettext.h"

#define DATE_SIZE 20

static void test_sct_gtk_task_tree_view_get_done(CuTest *test) {
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

    GtkCellRenderer *renderer = gtk_cell_renderer_toggle_new();
    GtkTreeIter iter;
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    gboolean done;
    g_object_get(G_OBJECT(renderer), "active", &done, NULL);
    CuAssertTrue(test, ! done);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    
    g_object_get(G_OBJECT(renderer), "active", &done, NULL);
    CuAssertTrue(test, done);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "active", &done, NULL);
    CuAssertTrue(test, ! done);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_done_cell_data_func(NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "active", &done, NULL);
    CuAssertTrue(test, done);
    
}

static void test_sct_gtk_task_tree_view_get_description(CuTest *test) {
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
    sct_gtk_task_tree_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    char *description;
    g_object_get(G_OBJECT(renderer), "text", &description, NULL);
    CuAssertStrEquals(test, description, "1st task");
    g_free(description);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &description, NULL);
    CuAssertStrEquals(test, description, "2nd task");
    g_free(description);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &description, NULL);
    CuAssertStrEquals(test, description, "3rd task");
    g_free(description);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_description_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &description, NULL);
    CuAssertStrEquals(test, description, "4th task");
    g_free(description);
    
}

static void test_sct_gtk_task_tree_view_get_project(CuTest *test) {
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
    char *project_name;
    
    // Not in inbox
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &project_name, NULL);
    CuAssertStrEquals(test, project_name, "");
    g_free(project_name);
    
    g_object_get(G_OBJECT(renderer), "text", &project_name, NULL);
    sct_gtk_task_tree_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    CuAssertStrEquals(test, project_name, "");
    g_free(project_name);
    
    // In projects
    sct_gtk_task_tree_model_show_project(model, project1);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &project_name, NULL);
    CuAssertStrEquals(test, project_name, "Project 1");
    g_free(project_name);
    
    sct_gtk_task_tree_model_show_project(model, project2);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_project_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &project_name, NULL);
    CuAssertStrEquals(test, project_name, "Project 2");
}

static void test_sct_gtk_task_tree_view_get_scheduled(CuTest *test) {
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
    
    time_t today = time(NULL), future = today + 24*60*60*3, t;
    
    secretary_schedule_task(secretary, t1, today);
    secretary_schedule_task(secretary, t4, future);
    
    GtkTreeModel *model = sct_gtk_task_tree_model_new(secretary);
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeIter iter;
    char *date_string;
    char buffer[SCT_GTK_TASK_TREE_MODEL_DATE_SIZE];
    
    // Not in inbox
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);
    g_object_get(G_OBJECT(renderer), "text", &date_string, NULL);
    CuAssertStrEquals(test, date_string, "");
    g_free(date_string);
    
    // Scheduled
    sct_gtk_task_tree_model_show_scheduled(model, NULL);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);

    t = task_get_scheduled_date(t1);
    strftime(buffer, SCT_GTK_TASK_TREE_MODEL_DATE_SIZE, "%d-%m-%Y", localtime(&t));
    
    g_object_get(G_OBJECT(renderer), "text", &date_string, NULL);
    CuAssertStrEquals(test, date_string,  buffer);
    g_free(date_string);
    
    CuAssertTrue(test, gtk_tree_model_iter_next(model, &iter));
    sct_gtk_task_tree_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);

    t = task_get_scheduled_date(t4);
    strftime(buffer, DATE_SIZE, "%d-%m-%Y", localtime(&t));
    
    g_object_get(G_OBJECT(renderer), "text", &date_string, NULL);
    CuAssertStrEquals(test, date_string, buffer);
    g_free(date_string);
    
    // Scheduled for today
    sct_gtk_task_tree_model_show_scheduled_for_today(model, NULL);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    sct_gtk_task_tree_view_scheduled_date_cell_data_func(
            NULL, renderer, model, &iter, NULL);

    t = task_get_scheduled_date(t1);
    buffer[SCT_GTK_TASK_TREE_MODEL_DATE_SIZE];
    strftime(buffer, SCT_GTK_TASK_TREE_MODEL_DATE_SIZE, "%d-%m-%Y", localtime(&t));
    
    g_object_get(G_OBJECT(renderer), "text", &date_string, NULL);
    CuAssertStrEquals(test,  date_string,  buffer);
    g_free(date_string);
}

static void test_sct_gtk_task_tree_view_edit_done(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    Task *task = secretary_create_task(secretary, "My task");
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    GtkWidget *view = app->task_tree_view;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkTreeViewColumn *done_column = gtk_tree_view_get_column(
            GTK_TREE_VIEW(view), SCT_GTK_TASK_TREE_VIEW_DONE_COLUMN);
    GList *renderers =  gtk_cell_layout_get_cells(
            GTK_CELL_LAYOUT(done_column));
    GtkCellRenderer *renderer = GTK_CELL_RENDERER(g_list_nth_data(renderers, 0));
    g_list_free(renderers);

    GtkTreeIter iter;
    char *path = "0";
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, ! task_is_done(task));
    
    g_signal_emit_by_name(G_OBJECT(renderer), "toggled", path, NULL);
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, task_is_done(task));
    
    g_signal_emit_by_name(G_OBJECT(renderer), "toggled", path, NULL);
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, ! task_is_done(task));

}

static void test_sct_gtk_task_tree_view_edit_done_and_save(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    Task *task = secretary_create_task(secretary, "My task");
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    GtkWidget *view = app->task_tree_view;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkTreeViewColumn *done_column = gtk_tree_view_get_column(
            GTK_TREE_VIEW(view), SCT_GTK_TASK_TREE_VIEW_DONE_COLUMN);
    GList *renderers =  gtk_cell_layout_get_cells(
            GTK_CELL_LAYOUT(done_column));
    GtkCellRenderer *renderer = GTK_CELL_RENDERER(g_list_nth_data(renderers, 0));
    g_list_free(renderers);

    GtkTreeIter iter;
    char *path = "0";
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, ! task_is_done(task));

    // Emit
    g_signal_emit_by_name(G_OBJECT(renderer), "toggled", path, NULL);
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, task_is_done(task));
    
    notebook_free(notebook);
    notebook = notebook_new("tempfile");
    secretary = notebook_get_secretary(notebook);
    
    task = secretary_get_nth_task(secretary, 0);
    CuAssertTrue(test, task != NULL);
    CuAssertTrue(test, task_is_done(task));
}

static void test_sct_gtk_task_tree_view_edit_description(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    Task *task = secretary_create_task(secretary, "My task");
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    GtkWidget *view = app->task_tree_view;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkTreeViewColumn *done_column = gtk_tree_view_get_column(
            GTK_TREE_VIEW(view), SCT_GTK_TASK_TREE_VIEW_DESCRIPTION_COLUMN);
    GList *renderers =  gtk_cell_layout_get_cells(
            GTK_CELL_LAYOUT(done_column));
    GtkCellRenderer *renderer = GTK_CELL_RENDERER(g_list_nth_data(renderers, 0));
    g_list_free(renderers);

    GtkTreeIter iter;
    char *path = "0";
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertStrEquals(test, "My task", task_get_description(task));
    
    g_signal_emit_by_name(G_OBJECT(renderer), "edited", path, "My updated task");
    
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertStrEquals(test, "My updated task", task_get_description(task));
}

static void test_sct_gtk_task_tree_view_edit_project(CuTest *test) {
    remove("tempfile");
    Notebook *notebook = notebook_new("tempfile");
    Secretary *secretary = notebook_get_secretary(notebook);
    Task *task = secretary_create_task(secretary, "My task");
    Project *project = secretary_create_project(secretary, "My project");
    
    SctGtkApplication *app = sct_gtk_application_new(notebook);
    
    GtkWidget *view = app->task_tree_view;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    sct_gtk_task_tree_model_show_inbox(model, NULL);

    GtkTreeViewColumn *project_column = gtk_tree_view_get_column(
            GTK_TREE_VIEW(view), SCT_GTK_TASK_TREE_VIEW_PROJECT_COLUMN);
    GList *renderers =  gtk_cell_layout_get_cells(
            GTK_CELL_LAYOUT(project_column));
    GtkCellRenderer *renderer = GTK_CELL_RENDERER(g_list_nth_data(renderers, 0));
    g_list_free(renderers);

    GtkTreeIter iter;
    char *path = "0";
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, !task_has_project(task));
    
    GtkTreeModel *combo_model;
    GtkTreeIter combo_iter;
    g_object_get(G_OBJECT(renderer), "model", &combo_model, NULL);
    
    gtk_tree_model_get_iter_first(combo_model, &combo_iter);
    gtk_tree_model_iter_next(combo_model, &combo_iter);
    
    g_signal_emit_by_name(G_OBJECT(renderer), "changed", path, &combo_iter, NULL);
    
    CuAssertTrue(test, task_has_project(task));
    CuAssertPtrEquals(test, project, task_get_project(task));
    
    sct_gtk_task_tree_model_show_project(model, project);
    CuAssertTrue(test, gtk_tree_model_get_iter_first(model, &iter));
    CuAssertTrue(test, task_has_project(task));
    CuAssertPtrEquals(test, project, task_get_project(task));
    
    gtk_tree_model_get_iter_first(combo_model, &combo_iter);
    
    g_signal_emit_by_name(G_OBJECT(renderer), "changed", path, &combo_iter, NULL);
    
    CuAssertTrue(test, !task_has_project(task));
}

CuSuite *test_sct_gtk_task_tree_view_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_get_done);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_get_description);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_get_project);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_get_scheduled);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_edit_done);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_edit_done_and_save);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_edit_description);
    SUITE_ADD_TEST(suite, test_sct_gtk_task_tree_view_edit_project);
    return suite;
}


