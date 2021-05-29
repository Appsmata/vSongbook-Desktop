#include <QtCore>

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