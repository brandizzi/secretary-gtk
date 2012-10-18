#include "test/test-secretary-gtk/date-cell-renderer.h"
#include "secretary-gtk/date-cell-renderer.h"
#include "secretary-gtk/_internal/date-cell-renderer.h"
#include "secretary-gtk/gettext.h"

#include "time.h"

static void test_sct_gtk_date_cell_renderer_set_date_thru_calendar_sets_entry(
        CuTest *test) {
    GtkCellRenderer *date_cell_renderer = sct_gtk_date_cell_renderer_new();
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
        
    time_t today = time(NULL);
    struct tm *date = localtime(&today);
    date->tm_year += 2; // Always in future, for assuring breakable test
    date->tm_mon = 11;
    date->tm_mday = 31;
    
    gtk_calendar_select_month(
            GTK_CALENDAR(des->calendar), 11, date->tm_year+1900);
    gtk_calendar_select_day(GTK_CALENDAR(des->calendar), 31);
    char date_string[12], *buffer;
    strftime(date_string, 12, _("%Y-%m-%d"), date);
    g_object_get(G_OBJECT(des->cell_renderer), "text", &buffer, NULL);
    CuAssertStrEquals(test, buffer, date_string);
}

static void test_sct_gtk_date_cell_renderer_set_date_thru_entry_sets_calendar(
        CuTest *test) {
    GtkCellRenderer *date_cell_renderer = sct_gtk_date_cell_renderer_new();
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
        
    time_t today = time(NULL);
    struct tm *date = localtime(&today);
    date->tm_year += 2; // Always in future, for assuring breakable test
    date->tm_mon = 11;
    date->tm_mday = 31;
    
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), date);
    g_object_set(G_OBJECT(des->cell_renderer), "text", buffer, NULL);
    
    int year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(des->calendar), &year, &month, &day);
    
    CuAssertIntEquals(test, year, date->tm_year+1900);
    CuAssertIntEquals(test, month, date->tm_mon);
    CuAssertIntEquals(test, day, date->tm_mday);
}

static void test_sct_gtk_date_cell_renderer_get_date(
        CuTest *test) {
    GtkCellRenderer *date_cell_renderer = sct_gtk_date_cell_renderer_new();
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
        
    time_t today = time(NULL);
    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_year += 2; // Always in future, for assuring breakable test
    date.tm_mon = 11;
    date.tm_mday = 31;
    
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    g_object_set(G_OBJECT(des->cell_renderer), "text", buffer, NULL);
    
    time_t selected = sct_gtk_date_cell_renderer_get_date(date_cell_renderer);
    CuAssertIntEquals(test, selected, mktime(&date));
}

static void test_sct_gtk_date_cell_renderer_has_selected_date(
        CuTest *test) {
    GtkCellRenderer *date_cell_renderer = sct_gtk_date_cell_renderer_new();
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);
    
    // Not selected by default
    CuAssertTrue(test, !sct_gtk_date_cell_renderer_has_selected_date(date_cell_renderer));

    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_year += 2; // Always in future, for assuring breakable test
    date.tm_mon = 11;
    date.tm_mday = 31;
    
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    g_object_set(G_OBJECT(date_cell_renderer), "text", buffer, NULL);
    
    CuAssertTrue(test, sct_gtk_date_cell_renderer_has_selected_date(date_cell_renderer));
}

static void test_sct_gtk_date_cell_renderer_set_date(
        CuTest *test) {
    GtkCellRenderer *date_cell_renderer = sct_gtk_date_cell_renderer_new();
    SctGtkDateCellRendererStruct *des = g_object_get_data(
            G_OBJECT(date_cell_renderer), SCT_GTK_DATE_CELL_RENDERER_STRUCT);

    CuAssertTrue(test, !sct_gtk_date_cell_renderer_has_selected_date(date_cell_renderer));
    
    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_year += 2; // Always in future, for assuring breakable test
    date.tm_mon = 11;
    date.tm_mday = 31;
    
    // Selecting date
    sct_gtk_date_cell_renderer_set_date(date_cell_renderer, mktime(&date));

    // Should change entry
    char buffer[12], *value;
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    g_object_get(G_OBJECT(des->cell_renderer), "text", &value, NULL);
    CuAssertStrEquals(test, value, buffer);
    
    // Date is selected now
    CuAssertTrue(test, sct_gtk_date_cell_renderer_has_selected_date(date_cell_renderer));
    time_t selected = sct_gtk_date_cell_renderer_get_date(date_cell_renderer);
    CuAssertIntEquals(test, selected, mktime(&date));
}


CuSuite *test_sct_gtk_date_cell_renderer_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, 
            test_sct_gtk_date_cell_renderer_set_date_thru_calendar_sets_entry);
    SUITE_ADD_TEST(suite, 
            test_sct_gtk_date_cell_renderer_set_date_thru_entry_sets_calendar);
    SUITE_ADD_TEST(suite,test_sct_gtk_date_cell_renderer_get_date);
    SUITE_ADD_TEST(suite,test_sct_gtk_date_cell_renderer_set_date);
    SUITE_ADD_TEST(suite,test_sct_gtk_date_cell_renderer_has_selected_date);
    return suite;
}


