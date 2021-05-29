#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QThread>

#include <data/app_database.h>
#include <views/home_window.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap("res/images/splash.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    app.thread()->sleep(3);
    app.processEvents();
    splash.close();

    //Check if database exists otherwise create it
    AppDatabase* appDb = new AppDatabase();
    appDb->checkDatabase();

    HomeWindow home;
    home.showMaximized();
    return app.exec();
}
