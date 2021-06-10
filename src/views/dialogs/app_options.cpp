#include <QtWidgets>
#include <QStandardItemModel>
#include <QObject>
#include <QGroupBox>
#include <QComboBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>

#include "app_options.h"
#include "ui_app_options.h"
#include <data/models/preference.h>
#include <data/delegates/pref_delegate.h>
#include <utils/preferences_utils.h>

int fontgeneral, fontpreview, fontpresent;
std::vector<QString> languages, pref_sets, navigations, pref_fonts;
QFont PrefFontGeneral, PrefFontPreview, PrefFontPresent, Font1, Font2;

PrefDelegate* prefDelegate;
Preference* preference;
QScrollArea* ScrollArea;
QWidget* ScrollPane;
QVBoxLayout* LstSettings;
std::vector<Preference> pages, prefs, filtered;
QStandardItemModel* prefModel = new QStandardItemModel();

AppOptions::AppOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppOptions)
{
    ui->setupUi(this);
    
    setupStuff();
    loadNavigation();
}

void AppOptions::setupStuff()
{
    ui->btnTheme1->setText("Black\nand\nWhite");
    ui->btnTheme1->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");

    ui->btnTheme2->setText("White\nand\nBlack");
    ui->btnTheme2->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");

    ui->btnTheme3->setText("Grey\nand\nBlack");
    ui->btnTheme3->setStyleSheet("* { background-color: #A9A9A9; color: #000000; }");

    ui->btnTheme4->setText("Black\nand\nGrey");
    ui->btnTheme4->setStyleSheet("* { background-color: #000000; color: #A9A9A9; }");

    ui->btnTheme5->setText("Blue\nand\nWhite");
    ui->btnTheme5->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");

    ui->btnTheme6->setText("White\nand\nBlue");
    ui->btnTheme6->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");

    ui->btnTheme7->setText("Green\nand\nWhite");
    ui->btnTheme7->setStyleSheet("* { background-color: #006400; color: #FFFFFF; }");

    ui->btnTheme8->setText("White\nand\nGreen");
    ui->btnTheme8->setStyleSheet("* { background-color: #FFFFFF; color: #006400; }");

    ui->btnTheme9->setText("Orange\nand\nBlack");
    ui->btnTheme9->setStyleSheet("* { background-color: #FFA500; color: #000000; }");

    ui->btnTheme10->setText("Black\nand\nOrange");
    ui->btnTheme10->setStyleSheet("* { background-color: #000000; color: #FFA500; }");

    ui->btnTheme11->setText("Red\nand\nWhite");
    ui->btnTheme11->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");

    ui->btnTheme12->setText("White\nand\nRed");
    ui->btnTheme12->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");

    ui->btnTheme13->setText("Black\nand\nYellow");
    ui->btnTheme13->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");

    ui->btnTheme14->setText("Yellow\nand\nBlack");
    ui->btnTheme14->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");

    ui->btnTheme15->setText("Custom\n\nTheme");
    ui->btnTheme15->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");

}

// Get the settings navigation
void AppOptions::loadNavigation()
{
    pages = PrefUtils::preferencePages();
    prefs = PrefUtils::preferenceList();
    
    if (pages.size() != 0)
    {
        prefModel->clear();
        for (size_t i = 0; i < pages.size(); i++)
        {
            QStandardItem* prefItem = new QStandardItem;
            prefItem->setData(QVariant::fromValue(pages[i]), Qt::UserRole + 1);
            prefModel->appendRow(prefItem);
        }
        
        PrefDelegate* prefDelegate = new PrefDelegate(this);
        ui->lstNavigation->setItemDelegate(prefDelegate);
        ui->lstNavigation->setModel(prefModel);
        ui->lstNavigation->setSpacing(1);
        ui->lstNavigation->setCurrentIndex(prefModel->index(0, 0));
        loadPreferences(1, "");
    }

}

void AppOptions::loadPreferences(int page, QString searchStr)
{
    if (prefs.size() != 0)
    {
        if (searchStr.length() < 2)
        {
            ui->grpTabletMode->hide();
            ui->grpSearchCriteria->hide();
            ui->grpLanguage->hide();
            ui->grpUserName->hide();
            ui->grpSampleText->hide();
            ui->grpFontGeneral->hide();
            ui->grpFontPreview->hide();
            ui->grpFontPresent->hide();
            ui->grpThemes->hide();

            switch (page)
            {
                case 1:
                    ui->grpTabletMode->show();
                    ui->grpTabletMode->setFocus();
                    ui->grpSearchCriteria->show();
                    ui->grpLanguage->show();
                    ui->grpUserName->show();
                    break;

                case 2:
                    ui->grpSampleText->show();
                    ui->grpSampleText->setFocus();
                    ui->grpFontGeneral->show();
                    ui->grpFontPreview->show();
                    ui->grpFontPresent->show();
                    break;

                case 3:
                    ui->grpThemes->show();
                    ui->grpThemes->setFocus();
                    break;
            }
        }
        else
        {
            filtered.clear();
            ui->grpTabletMode->hide();
            ui->grpSearchCriteria->hide();
            ui->grpLanguage->hide();
            ui->grpUserName->hide();
            ui->grpSampleText->hide();
            ui->grpFontGeneral->hide();
            ui->grpFontPreview->hide();
            ui->grpFontPresent->hide();
            ui->grpThemes->hide();

            for (size_t i = 0; i < prefs.size(); i++)
            {
                if (prefs[i].title.contains(searchStr) || prefs[i].content.contains(searchStr))
                {
                    filtered.push_back(prefs[i]); 
                    
                    switch (prefs[i].preferenceid)
                    {
                        case 1:
                            ui->grpTabletMode->show();
                            break;

                        case 2:
                            ui->grpSearchCriteria->show();
                            break;

                        case 3:
                            ui->grpLanguage->show();
                            break;

                        case 5:
                            ui->grpUserName->show();
                            break;

                        case 7:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 8:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 9:
                            ui->grpSampleText->show();
                            ui->grpFontGeneral->show();
                            break;

                        case 10:
                            ui->grpThemes->show();
                            break;

                    }
                }
            }
        }
    }

}

void AppOptions::on_lstNavigation_clicked(const QModelIndex &index)
{
    int item = index.row();
    loadPreferences(pages[item].category, "");
}

void AppOptions::on_lstNavigation_doubleClicked(const QModelIndex &index)
{
    int item = index.row();
    loadPreferences(pages[item].category, "");
}

void AppOptions::on_txtSearch_textChanged(const QString &arg1)
{
    loadPreferences(0, arg1);
}

void AppOptions::on_btnTabletMode_clicked(bool checked)
{

}

void AppOptions::on_btnSearchCritria_clicked(bool checked)
{

}

void AppOptions::on_cmbLanguage_currentIndexChanged(int index)
{

}

void AppOptions::on_txtUserName_textChanged(const QString &arg1)
{

}


void AppOptions::on_sldFontGeneral_valueChanged(int value)
{

}

void AppOptions::on_cmbFontGeneral_currentIndexChanged(int index)
{

}

void AppOptions::on_btnFontGeneral_clicked(bool checked)
{

}

void AppOptions::on_sldFontPreview_valueChanged(int value)
{

}

void AppOptions::on_cmbFontPreview_currentIndexChanged(int index)
{

}

void AppOptions::on_btnFontPreview_clicked(bool checked)
{

}

void AppOptions::on_sldFontPresent_valueChanged(int value)
{

}

void AppOptions::on_cmbFontPresent_currentIndexChanged(int index)
{

}

void AppOptions::on_btnFontPresent_clicked(bool checked)
{

}

void AppOptions::on_btnTheme1_clicked()
{

}

void AppOptions::on_btnTheme2_clicked()
{

}

void AppOptions::on_btnTheme3_clicked()
{

}

void AppOptions::on_btnTheme4_clicked()
{

}

void AppOptions::on_btnTheme5_clicked()
{

}

void AppOptions::on_btnTheme6_clicked()
{

}

void AppOptions::on_btnTheme7_clicked()
{

}

void AppOptions::on_btnTheme8_clicked()
{

}

void AppOptions::on_btnTheme9_clicked()
{

}

void AppOptions::on_btnTheme10_clicked()
{

}

void AppOptions::on_btnTheme11_clicked()
{

}

void AppOptions::on_btnTheme12_clicked()
{

}

void AppOptions::on_btnTheme13_clicked()
{

}

void AppOptions::on_btnTheme14_clicked()
{

}

void AppOptions::on_btnTheme15_clicked()
{

}

AppOptions::~AppOptions()
{
    delete ui;
}
