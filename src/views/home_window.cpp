#include <memory>
#include <QMainWindow>
#include <QModelIndex>
#include <QListView>
#include <QDialog>
#include <QDialogButtonBox>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFile>
#include <QGraphicsDropShadowEffect>

#include "home_window.h"
#include "ui_home_window.h"
#include <utils/app_utils.h>
#include <data/delegates/song_delegate.h>
#include <views/dialogs/book_select.h>
#include <views/presentor_window.h>
#include <views/dialogs/app_options.h>
#include <services/app_preferences.h>

int fontSizePreview, fontSizePreviewType, selectedbook;
bool isReady, isEditMode, isSearchAll, isDarkMode, isPreviewBold;
QString selected_book, selected_song, search_term;
std::vector<Book> books;
std::vector<Song> songs, filters;
QFont homeFontPreview, homeFontGeneral;
QStandardItemModel* songModel = new QStandardItemModel();

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    ui->SplitterMain->setStretchFactor(1, 3);

	this->setWindowTitle("vSongBook v3.0.2 | " + prefAppUser::get());

	loadSettings();
	loadControls();
	requestData();
}

void HomeWindow::changeStyle(int type)
{
    QString fileName = "";
    switch ( type )
    {
        case 1:
            fileName = "black.qss";
            break;
        default:
            fileName = "brown.qss";
            break;
    }

    QFile file(":/themes/"+ fileName);

    if ( file.open(QFile::ReadOnly) )
    {
        QString qss = QLatin1String(file.readAll());
        this->setStyleSheet(qss);
        file.close();
    }
}

void HomeWindow::requestData()
{
    /*if (appDb->isDataLoaded()) {

    }
    else {
        BookSelect bookSelect(this);
        bookSelect.exec();
        //loadData();
    }*/
	if (populateSongbooks())
	{
		if (ui->cmbSongbooks->count() > 0)
		{
			appDb->connectionOpen("songs");
			songs = appDb->fetchSongs();
			appDb->connectionClose("songs");
			populateSongLists(0);
			isReady = true;
		}
		else
		{
			//AsBase::WriteLogs("Data", "Database is empty, resorting to user actions", "", "");
		}
	}
	else {
		QMessageBox::warning(this, qApp->applicationName(), tr("Oops! vSongBook could not generate view due to unknown error at the moment"));
	}
}

void HomeWindow::loadSettings()
{
    isDarkMode = prefDarkMode::get();
    isEditMode = prefEditMode::get();
    isSearchAll = prefSearchAllbooks::get();

    isPreviewBold = prefPreviewFontBold::get();
	fontSizePreview = prefPreviewFontSize::get();
    fontSizePreviewType = prefPreviewFontType::get();

    homeFontGeneral.setFamily(PrefUtils::preferencesFontTypes()[prefGeneralFontType::get()]);
    homeFontGeneral.setPointSize(prefGeneralFontSize::get());
    homeFontGeneral.setBold(prefGeneralFontBold::get());
    //homeFontGeneral.setWeight(50);

    homeFontPreview.setFamily(PrefUtils::preferencesFontTypes()[fontSizePreviewType]);
    homeFontPreview.setPointSize(prefPreviewFontSize::get());
    homeFontPreview.setBold(prefPreviewFontBold::get());
    //homeFontPreview.setWeight(50);
}

void HomeWindow::loadControls()
{
    ui->chkSearchCriteria->setChecked(isSearchAll);
    ui->menuSearchAll->setChecked(isSearchAll);
    ui->actionDarkMode->setChecked(isDarkMode);
    ui->menuDarkMode->setChecked(isDarkMode);

    ui->txtSearch->setFont(homeFontGeneral);
    ui->cmbSongbooks->setFont(homeFontGeneral);
    ui->chkSearchCriteria->setFont(homeFontGeneral);

    ui->txtTitle->setFont(homeFontPreview);
    ui->txtContent->setFont(homeFontPreview);
    ui->txtAlias->setFont(homeFontPreview);

    if (isDarkMode) changeStyle(1);
    else changeStyle(0);
}

// Changing of font of the song preview
void HomeWindow::fontChange()
{
	switch (fontSizePreviewType)
	{
	case 12:
		fontSizePreviewType = 1;
		break;

	default:
		fontSizePreviewType = fontSizePreviewType + 1;
		break;
	}
	prefPresentFontType::set(fontSizePreviewType);
    loadSettings();
	loadControls();
}

// Reduce Preview Font Size
void HomeWindow::fontSmaller()
{
	if ((fontSizePreview - 2) > 9)
	{
		fontSizePreview = fontSizePreview - 2;
        homeFontPreview.setPointSize(fontSizePreview);
		prefPreviewFontSize::set(fontSizePreview);
        loadSettings();
		loadControls();
	}
}

void HomeWindow::fontBigger()
{
	if ((fontSizePreview + 2) < 51)
	{
		fontSizePreview = fontSizePreview + 2;
		prefPreviewFontSize::set(fontSizePreview);
        loadSettings();
		loadControls();
	}
}

bool HomeWindow::populateSongbooks()
{
	bool retval = false;

	appDb->connectionOpen("books");
	books = appDb->fetchBooks();
	appDb->connectionClose("books");
	
	if (books.size() != 0)
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			ui->cmbSongbooks->addItem(books[i].title);
		}
		retval = true;
	}
	return true;
}

void HomeWindow::populateSongLists(size_t book)
{
	if (book == 0 || book < books.size())
	{
		if (songs.size() != 0)
		{
			
			filters.clear();
			songModel->clear();

			for (size_t i = 0; i < songs.size(); i++)
			{
				if (songs[i].categoryid == books[book].categoryid)
				{
					filters.push_back(songs[i]);
					QStandardItem* songItem = new QStandardItem;
					songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
					songModel->appendRow(songItem);
				}
			}
			filterSonglists();
		}
	}
}

void HomeWindow::populateSongSearch(QString SearchStr)
{
	if (SearchStr.size() > 0)
	{
		if (songs.size() != 0)
		{
			filters.clear();
			songModel->clear();

            if (SearchStr.size() < 5)
            {
                if (SearchStr.toInt() != 0)
                {
                    for (size_t i = 0; i < songs.size(); i++)
                    {
                        if (songs[i].number == SearchStr.toInt())
                        {
                            filters.push_back(songs[i]);
                            QStandardItem* songItem = new QStandardItem;
                            songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
                            songModel->appendRow(songItem);
                        }
                    }
                }
                else searchSonglists(SearchStr);
            }
            else searchSonglists(SearchStr);
			filterSonglists();
		}
	}
}

void HomeWindow::searchSonglists(QString SearchStr)
{
    for (size_t i = 0; i < songs.size(); i++)
    {
        if (songs[i].title.toLower().contains(SearchStr.toLower()) ||
                songs[i].alias.toLower().contains(SearchStr.toLower()) ||
                songs[i].content.toLower().contains(SearchStr.toLower()))
        {
            filters.push_back(songs[i]);
            QStandardItem* songItem = new QStandardItem;
            songItem->setData(QVariant::fromValue(songs[i]), Qt::UserRole + 1);
            songModel->appendRow(songItem);
        }
    }
}

void HomeWindow::filterSonglists()
{
	if (filters.size() != 0)
	{
		SongDelegate* songDelegate = new SongDelegate(this);
		ui->lstResults->setItemDelegate(songDelegate);
		ui->lstResults->setModel(songModel);
		ui->lstResults->setSpacing(1);
		ui->lstResults->setCurrentIndex(songModel->index(0, 0));
		openSongPreview(songModel->index(0, 0));
	}
}

void HomeWindow::openSongPreview(const QModelIndex& index)
{
	int song = index.row();
	QString songTitle = AppUtils::replaceView(filters[song].title);
	QString songAlias = AppUtils::replaceView(filters[song].alias);
	QString songContent = AppUtils::replaceView(filters[song].content);

	prefSelectedSong::set(filters[song].songid);

	ui->txtTitle->setText(songTitle);
	ui->txtContent->setPlainText(songContent);

	if (songAlias.length() < 3)
	{
		//ui->txtAlias->hide();
	}
	else
	{
		//ui->TxtPreviewAlias->show();
		//ui->TxtPreviewAlias->setPlainText(songAlias);
	}
}

// Open the presentor window
void HomeWindow::openPresenter()
{
	PresentorWindow* present = new PresentorWindow();
	present->showFullScreen();
}

void HomeWindow::on_txtSearch_textChanged(const QString &arg1)
{
	populateSongSearch(arg1);
}

void HomeWindow::on_txtSearch_returnPressed()
{
	populateSongSearch(ui->txtSearch->text());
}

void HomeWindow::on_cmbSongbooks_currentIndexChanged(int index)
{
	if (isReady) populateSongLists(index);
}

void HomeWindow::on_lstResults_clicked(const QModelIndex &index)
{
	openSongPreview(index);
}

void HomeWindow::on_lstResults_doubleClicked(const QModelIndex &index)
{
	openSongPreview(index);
	openPresenter();
}

void HomeWindow::on_menuPrint_triggered()
{

}

void HomeWindow::on_menuExit_triggered()
{
	close();
}

void HomeWindow::on_menuNewSong_triggered()
{

}

void HomeWindow::on_menuEditSong_triggered()
{

}

void HomeWindow::on_menuBooks_triggered()
{

}

void HomeWindow::on_menuPresent_triggered()
{
	openPresenter();
}

void HomeWindow::on_menuManageSettings_triggered()
{
	on_toolbarSettings_triggered();
}

void HomeWindow::on_menuResetSettings_triggered()
{

}

void HomeWindow::on_menuHowItWorks_triggered()
{

}

void HomeWindow::on_menuContactUs_triggered()
{

}

void HomeWindow::on_menuAboutThisApp_triggered()
{

}

void HomeWindow::on_toolbarPresent_triggered()
{
	openPresenter();
}

void HomeWindow::on_toolbarEdit_triggered()
{

}

void HomeWindow::on_toolbarPrevious_triggered()
{

}

void HomeWindow::on_toolbarNext_triggered()
{

}

void HomeWindow::on_toolbarSmaller_triggered()
{
    if ((fontSizePreview - 2) > 9)
    {
        fontSizePreview = fontSizePreview - 2;
        prefPresentFontSize::set(fontSizePreview);
        loadSettings();
        loadControls();
    }
}

void HomeWindow::on_toolbarBigger_triggered()
{
    if ((fontSizePreview + 2) < 51)
    {
        fontSizePreview = fontSizePreview + 2;
        prefPresentFontSize::set(fontSizePreview);
        loadSettings();
        loadControls();
    }
}

void HomeWindow::on_toolbarSettings_triggered()
{
    AppOptions preferences(this);
	preferences.exec();
}

void HomeWindow::on_toolbarBold_triggered()
{
    if (ui->toolbarBold->isChecked())isPreviewBold = false;
    else isPreviewBold = true;
    prefPreviewFontBold::set(isPreviewBold);
    loadSettings();
    loadControls();
}

void HomeWindow::on_menuDarkMode_triggered()
{
    if (ui->menuDarkMode->isChecked())isDarkMode = false;
    else isDarkMode = true;
    prefDarkMode::set(isDarkMode);
    loadSettings();
    loadControls();
}


void HomeWindow::on_actionDarkMode_triggered()
{
    if (ui->actionDarkMode->isChecked())isDarkMode = false;
    else isDarkMode = true;
    prefDarkMode::set(isDarkMode);
    loadSettings();
    loadControls();
}

void HomeWindow::on_chkSearchCriteria_stateChanged(int value)
{
    if (value == 1) isSearchAll = true;
    else isSearchAll = false;
    prefSearchAllbooks::set(isSearchAll);
    loadSettings();
    loadControls();
}

void HomeWindow::on_menuSearchAll_triggered()
{
    if (ui->menuSearchAll->isChecked())isSearchAll = false;
    else isSearchAll = true;
    prefSearchAllbooks::set(isSearchAll);
    loadSettings();
    loadControls();
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

