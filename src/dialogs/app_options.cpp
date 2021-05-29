#include "app_options.h"
#include "ui_app_options.h"

AppOptions::AppOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppOptions)
{
    ui->setupUi(this);
}

AppOptions::~AppOptions()
{
    delete ui;
}
