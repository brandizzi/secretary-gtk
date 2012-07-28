#include "test/test-secretary-gtk/date-entry.h"
#include "secretary-gtk/date-entry.h"
#include "secretary-gtk/_internal/date-entry.h"
#include "secretary-gtk/gettext.h"

#include "time.h"

static void test_sct_gtk_date_entry_set_date_thru_calendar_sets_entry(
        CuTest *test) {
    GtkWidget *date_entry = sct_gtk_date_entry_new();
    SctGtkDateEntryStruct *des = g_object_get_data(
            G_OBJECT(date_entry), SCT_GTK_DATE_ENTRY_STRUCT);
        
    time_t today = time(NULL);
    struct tm *date = localtime(&today);
    date->tm_year += 2; // Always in future, for assuring breakable test
    date->tm_mon = 11;
    date->tm_mday = 31;
    
    gtk_calendar_select_month(
            GTK_CALENDAR(des->calendar), 11, date->tm_year+1900);
    gtk_calendar_select_day(GTK_CALENDAR(des->calendar), 31);
    
    char date_string[12];
    strptime(date_string, _("%Y-%m-%d"), date);
    CuAssertStrEquals(
            test, gtk_entry_get_text(GTK_ENTRY(des->entry)), date_string);
}

static void test_sct_gtk_date_entry_set_date_thru_entry_sets_calendar(
        CuTest *test) {
    GtkWidget *date_entry = sct_gtk_date_entry_new();
    SctGtkDateEntryStruct *des = g_object_get_data(
            G_OBJECT(date_entry), SCT_GTK_DATE_ENTRY_STRUCT);
        
    time_t today = time(NULL);
    struct tm *date = localtime(&today);
    date->tm_year += 2; // Always in future, for assuring breakable test
    date->tm_mon = 11;
    date->tm_mday = 31;
    
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), date);
    gtk_entry_set_text(GTK_ENTRY(des->entry), buffer);
    
    int year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(des->calendar), &year, &month, &day);
    
    CuAssertIntEquals(test, year, date->tm_year+1900);
    CuAssertIntEquals(test, month, date->tm_mon);
    CuAssertIntEquals(test, day, date->tm_mday);
}

static void test_sct_gtk_date_entry_get_date(
        CuTest *test) {
    GtkWidget *date_entry = sct_gtk_date_entry_new();
    SctGtkDateEntryStruct *des = g_object_get_data(
            G_OBJECT(date_entry), SCT_GTK_DATE_ENTRY_STRUCT);
        
    time_t today = time(NULL);
    struct tm date;
    memset(&date, '\0', sizeof(struct tm));
    date.tm_year += 2; // Always in future, for assuring breakable test
    date.tm_mon = 11;
    date.tm_mday = 31;
    
    char buffer[12];
    strftime(buffer, 12, _("%Y-%m-%d"), &date);
    gtk_entry_set_text(GTK_ENTRY(des->entry), buffer);
    
    time_t selected = sct_gtk_date_entry_get_date(date_entry);
    CuAssertIntEquals(test, selected, mktime(&date));
}


CuSuite *test_sct_gtk_date_entry_suite(void) {
    CuSuite *suite  = CuSuiteNew();
    SUITE_ADD_TEST(suite, 
            test_sct_gtk_date_entry_set_date_thru_calendar_sets_entry);
    SUITE_ADD_TEST(suite, 
            test_sct_gtk_date_entry_set_date_thru_entry_sets_calendar);
    SUITE_ADD_TEST(suite,test_sct_gtk_date_entry_get_date);
    return suite;
}


