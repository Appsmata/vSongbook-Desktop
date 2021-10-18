QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32:RC_ICONS += res/icons/appicon.ico

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data/app_database.cpp \
    data/delegates/book_delegate.cpp \
    data/delegates/pref_delegate.cpp \
    data/delegates/song_delegate.cpp \
    main.cpp \
    views/dialogs/app_about.cpp \
    views/dialogs/app_hints.cpp \
    views/dialogs/app_options.cpp \
    views/dialogs/book_select.cpp \
    views/dialogs/how_it_works.cpp \
    views/home_window.cpp \
    views/presentor_window.cpp

HEADERS += \
    data/app_database.h \
    data/delegates/book_delegate.h \
    data/delegates/pref_delegate.h \
    data/delegates/song_delegate.h \
    data/models/book.h \
    data/models/history.h \
    data/models/list_item.h \
    data/models/preference.h \
    data/models/search.h \
    data/models/song.h \
    services/app_preferences.h \
    services/exception.h \
    services/task.h \
    utils/api_utils.h \
    utils/app_utils.h \
    utils/database_utils.h \
    utils/preferences_utils.h \
    views/dialogs/app_about.h \
    views/dialogs/app_hints.h \
    views/dialogs/app_options.h \
    views/dialogs/book_select.h \
    views/dialogs/how_it_works.h \
    views/home_window.h \
    views/presentor_window.h

FORMS += \
    views/dialogs/app_about.ui \
    views/dialogs/app_hints.ui \
    views/dialogs/app_options.ui \
    views/dialogs/book_select.ui \
    views/dialogs/how_it_works.ui \
    views/home_window.ui \
    views/presentor_window.ui

TRANSLATIONS += \
    vSongBook_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    langs/vSongBook_en_GB.ts

RESOURCES += \
    res/icons.qrc \
    res/images.qrc \
    res/themes.qrc
