#ifndef APP_OPTIONS_H
#define APP_OPTIONS_H

#include <QDialog>

namespace Ui {
class AppOptions;
}

class AppOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AppOptions(QWidget *parent = nullptr);
    ~AppOptions();

private:
    Ui::AppOptions *ui;
};

#endif // APP_OPTIONS_H
