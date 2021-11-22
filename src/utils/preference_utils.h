#include <QtCore>
#include "../data/models/preference.h"

class PrefUtils
{
public:
    static QString preferencesAppUser() { return "preferences_app_user"; }
    static QString preferencesDarkMode() { return "preferences_dark_mode"; }
    static QString preferencesEditMode() { return "preferences_edit_mode"; }
    static QString preferencesGeneralFontBold() { return "preferences_general_font_bold"; }
    static QString preferencesGeneralFontSize() { return "preferences_general_font_size"; }
    static QString preferencesGeneralFontType() { return "preferences_general_font_type"; }
    static QString preferencesInstalledDate() { return "preferences_installed_date"; }
    static QString preferencesLanguage() { return "preferences_language"; }
    static QString preferencesLastWindowStartup() { return "preferences_last_window_startup"; }
    static QString preferencesLastWindowWidth() { return "preferences_last_window_width"; }
    static QString preferencesListFontBold() { return "preferences_list_font_bold"; }
    static QString preferencesPresentFontBold() { return "preferences_present_font_bold"; }
    static QString preferencesPresentFontSize() { return "preferences_present_font_size"; }
    static QString preferencesPresentFontType() { return "preferences_present_font_type"; }
    static QString preferencesPreviewFontBold() { return "preferences_preview_font_bold"; }
    static QString preferencesPreviewFontSize() { return "preferences_preview_font_size"; }
    static QString preferencesPreviewFontType() { return "preferences_preview_font_type"; }
    static QString preferencesSearchAllbooks() { return "preferences_search_all_books"; }
    static QString preferencesSelectedBook() { return "preferences_selected_book"; }
    static QString preferencesSelectedSong() { return "preferences_selected_song"; }
    static QString preferencesShowHelpFirst() { return "preferences_show_help_first"; }
    static QString preferencesShowStartpage() { return "preferences_show_startpage"; }
    static QString preferencesTabletMode() { return "preferences_tablet_mode"; }
    static QString preferencesTheme() { return "preferences_theme"; }

    static std::vector<QString> preferencesFontTypes()
    {
        std::vector<QString> fonts;

        fonts.push_back("Arial");
        fonts.push_back("Calibri");
        fonts.push_back("Century Gothic");
        fonts.push_back("Comic Sans MS");
        fonts.push_back("Corbel");
        fonts.push_back("Courier New");
        fonts.push_back("Palatino");
        fonts.push_back("Linotype");
        fonts.push_back("Tahoma");
        fonts.push_back("Tempus Sans ITC");
        fonts.push_back("Times New Roman");
        fonts.push_back("Trebuchet MS");
        fonts.push_back("Verdana");

        return fonts;
    }

    static std::vector<Preference> preferencePages()
    {
        std::vector<Preference> pages;
        Preference page1, page2, page3;

        page1.category = 1;
        page1.title = "General Options";
        page1.content = "Essential preferences";

        page2.category = 2;
        page2.title = "App Font Options";
        page2.content = "Font management";

        page3.category = 3;
        page3.title = "Presentation Themes";
        page3.content = "Set your preffered theme";

        pages.push_back(page1);
        pages.push_back(page2);
        pages.push_back(page3);
        return pages;
    }

    static std::vector<Preference> preferenceList()
    {
        std::vector<Preference> prefs;
        Preference pref1, pref2, pref3, pref4, pref5, pref6, pref7, pref8, pref9, pref10;

        pref1.category = 1;
        pref1.preferenceid = 1;
        pref1.title = "Tablet Mode";
        pref1.content = "Use touchscreen mode";
        pref1.key = "preferences_tablet_mode";

        pref2.category = 1;
        pref2.preferenceid = 2;
        pref2.title = "Search Criteria";
        pref2.content = "Search all songbooks";
        pref2.key = "preferences_search_all_books";

        pref3.category = 1;
        pref3.preferenceid = 3;
        pref3.title = "Preffered Language";
        pref3.content = "Choose app language";
        pref3.key = "preferences_language";

        pref4.category = 1;
        pref4.preferenceid = 4;
        pref4.title = "Dark Mode";
        pref4.content = "Enable dark mode";
        pref4.key = "preferences_dark_mode";

        pref5.category = 1;
        pref5.preferenceid = 5;
        pref5.title = "Your Name/Name of your Church";
        pref5.content = "App User Name";
        pref5.key = "preferences_app_user";

        pref6.category = 1;
        pref6.preferenceid = 6;
        pref6.title = "Song Edit Mode";
        pref6.content = "Enable etitting of songs";
        pref6.key = "preferences_edit_mode";

        pref7.category = 2;
        pref7.preferenceid = 7;
        pref7.title = "General App font";
        pref7.content = "";
        pref7.key = "preferences_general_font";

        pref8.category = 2;
        pref8.preferenceid = 8;
        pref8.title = "Song Preview Font";
        pref8.content = "";
        pref8.key = "preferences_preview_font";

        pref9.category = 1;
        pref9.preferenceid = 9;
        pref9.title = "Song Present Font";
        pref9.content = "";
        pref9.key = "preferences_present_font";

        pref10.category = 1;
        pref10.preferenceid = 10;
        pref10.title = "Presentation Themes";
        pref10.content = "";
        pref10.key = "preferences_theme";

        prefs.push_back(pref1);
        prefs.push_back(pref2);
        prefs.push_back(pref3);
        prefs.push_back(pref4);
        prefs.push_back(pref5);
        prefs.push_back(pref6);
        prefs.push_back(pref7);
        prefs.push_back(pref8);
        prefs.push_back(pref9);
        prefs.push_back(pref10);
        return prefs;
    }

};

class PrefDefaults
{
public:
    static QString preferencesAppUser() { return "App User"; }
    static QString preferencesDarkMode() { return "0"; }
    static QString preferencesEditMode() { return "1"; }
    static QString preferencesGeneralFontBold() { return "1"; }
    static QString preferencesGeneralFontSize() { return "20"; }
    static QString preferencesGeneralFontType() { return "1"; }
    static QString preferencesInstalledDate() { return ""; }
    static QString preferencesLanguage() { return "English"; }
    static QString preferencesLastWindowStartup() { return "1"; }
    static QString preferencesLastWindowWidth() { return "0"; }
    static QString preferencesListFontBold() { return "0"; }
    static QString preferencesPresentFontBold() { return "1"; }
    static QString preferencesPresentFontSize() { return "40"; }
    static QString preferencesPresentFontType() { return "1"; }
    static QString preferencesPreviewFontBold() { return "1"; }
    static QString preferencesPreviewFontSize() { return "30"; }
    static QString preferencesPreviewFontType() { return "1"; }
    static QString preferencesSearchAllbooks() { return "1"; }
    static QString preferencesSelectedBook() { return "1"; }
    static QString preferencesSelectedSong() { return "1"; }
    static QString preferencesShowHelpFirst() { return "1"; }
    static QString preferencesShowStartpage() { return "1"; }
    static QString preferencesTabletMode() { return "0"; }
    static QString preferencesTheme() { return "0"; }

};