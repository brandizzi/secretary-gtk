#include "test/test-secretary-gtk/new-project-dialog.h"
#include "secretary-gtk/_internal/new-project-dialog.h"
#include "secretary-gtk/new-project-dialog.h"
#include "secretary-gtk/gettext.h"

#include <gtk/gtk.h>

#include "time.h"

static void test_sct_gtk_new_project_dialog_create_project(CuTest *test) {
    Secretary *secretary = secretary_new();
    GtkWidget *dialog = sct_gtk_new_project_dialog_new(secretary, NULL);
    SctGtkNewProjectDialogStruct *ds = g_object_get_data(
            G_OBJECT(dialog), SCT_GTK_NEW_PROJECT_DIALOG_STRUCT);
    
    gtk_entry_set_text(GTK_ENTRY(ds->name_entry), "My new project");
    
    Project *project = sct_gtk_new_project_dialog_create_project(GTK_DIALOG(dialog));
    CuAssertStrEquals(test, "My new project", project_get_name(project));
    
    CuAssertIntEquals(test, secretary_count_projects(secretary), 1);
    CuAssertPtrEquals(test, project, secretary_get_nth_project(secretary, 0));
}

CuSuite *test_sct_gtk_new_project_dialog_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_sct_gtk_new_project_dialog_create_project);
    return suite;
}


