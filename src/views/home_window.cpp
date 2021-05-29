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

#include "home_window.h"
#include "ui_home_window.h"
#include <utils/app_utils.h>
#include <dialogs/book_select.h>
#include <data/delegates/song_delegate.h>
#include <views/presentor_window.h>
#include <services/app_preferences.h>

int fontSizePreview, fontSizePreviewType, selectedbook;
bool isReady, searchAll, isDarkMode, isPreviewBold;
QString selected_book, selected_song, search_term;
std::vector<Book> books;
std::vector<Song> songs, filters;
QFont HomeFontPreview, HomeFontGeneral;
QStandardItemModel* songModel = new QStandardItemModel();

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    ui->SplitterMain->setStretchFactor(1, 3);

	this->setWindowTitle("vSongBook v3.0.1 | " + prefAppUser::get());

	loadSettings();
	loadControls();
	requestData();
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
			populateSonglists(0);
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
	fontSizePreviewType = prefPreviewFontType::get();
	fontSizePreview = prefPreviewFontSize::get();

	HomeFontGeneral.setFamily(PrefUtils::preferencesFontTypes()[prefGeneralFontType::get()]);
	HomeFontGeneral.setPointSize(prefGeneralFontSize::get());
	HomeFontGeneral.setBold(prefGeneralFontBold::get());
	HomeFontGeneral.setWeight(50);

	HomeFontPreview.setFamily(PrefUtils::preferencesFontTypes()[fontSizePreviewType]);
	HomeFontPreview.setPointSize(prefPreviewFontSize::get());
	HomeFontPreview.setBold(prefPreviewFontBold::get());
	HomeFontPreview.setWeight(50);
}

void HomeWindow::loadControls()
{
	//ui->chkSearchCriteria->setChecked(searchAll);
	//ui->actionSearchAll->setChecked(searchAll);
	//ui->ChkDarkMode->setChecked(isDarkMode);
	//ui->actionDarkMode->setChecked(isDarkMode);

	ui->txtSearch->setFont(HomeFontGeneral);
	ui->cmbSongbooks->setFont(HomeFontGeneral);
	ui->chkSearchCriteria->setFont(HomeFontGeneral);

	ui->txtTitle->setFont(HomeFontPreview);
	ui->txtContent->setFont(HomeFontPreview);
	ui->txtAlias->setFont(HomeFontPreview);
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
	loadControls();
}

// Reduce Preview Font Size
void HomeWindow::fontSmaller()
{
	if ((fontSizePreview - 2) > 9)
	{
		fontSizePreview = fontSizePreview - 2;
		HomeFontPreview.setPointSize(fontSizePreview);
		prefPreviewFontSize::set(fontSizePreview);
		loadControls();
	}
}

void HomeWindow::fontBigger()
{
	if ((fontSizePreview + 2) < 51)
	{
		fontSizePreview = fontSizePreview + 2;
		prefPreviewFontSize::set(fontSizePreview);
		loadControls();
	}
}

void HomeWindow::fontBold()
{
	if (isPreviewBold) isPreviewBold = false;
	else isPreviewBold = true;
	prefPreviewFontBold::set(isPreviewBold);
	loadControls();
}

bool HomeWindow::populateSongbooks()
{
	bool retval = false;

	appDb->connectionOpen("books");
	books = appDb->fetchBooks();
	appDb->connectionClose("books");
	
	if (books.size() != 0)
	{
		for (int i = 0; i < books.size(); i++)
		{
			ui->cmbSongbooks->addItem(books[i].title);
		}
		retval = true;
	}
	return true;
}

void HomeWindow::populateSonglists(int book)
{
	if (book == 0 || book < books.size())
	{
		if (songs.size() != 0)
		{
			
			filters.clear();
			songModel->clear();

			for (int i = 0; i < songs.size(); i++)
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

HomeWindow::~HomeWindow()
{
    delete ui;
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

}

void HomeWindow::on_txtSearch_returnPressed()
{

}

void HomeWindow::on_cmbSongbooks_currentIndexChanged(int index)
{
	if (isReady) populateSonglists(index);
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

void HomeWindow::on_toolbarBigger_triggered()
{

}

void HomeWindow::on_toolbarSmaller_triggered()
{

}

void HomeWindow::on_toolbarBold_triggered()
{

}

void HomeWindow::on_toolbarSettings_triggered()
{

}
