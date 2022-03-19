#include "UserWindow.h"


#include "CSVFile.h"
#include "HTMLFile.h"

void UserWindow::addButtons() {

	// creating buttons
	this->deleteMovieBtn = new QPushButton("Delete movie");
	this->deleteMovieBtn->setFont(this->fontBasic);
	this->deleteMovieBtn->setContentsMargins(this->buttonsMargins);
	this->deleteMovieBtn->setFixedSize(this->normalButtonSize);

	this->seeMovieByGenreBtn = new QPushButton("See movies by genre");
	this->seeMovieByGenreBtn->setFont(this->fontBasic);
	this->seeMovieByGenreBtn->setContentsMargins(this->buttonsMargins);
	this->seeMovieByGenreBtn->setFixedSize(this->normalButtonSize);

	this->openInHTMLFormatBtn = new QPushButton("Open in HTML format");
	this->openInHTMLFormatBtn->setFont(this->fontBasic);
	this->openInHTMLFormatBtn->setContentsMargins(this->buttonsMargins);
	this->openInHTMLFormatBtn->setFixedSize(this->normalButtonSize);

	this->openInCSVFormatBtn = new QPushButton("Open in CSV format");
	this->openInCSVFormatBtn->setFont(this->fontBasic);
	this->openInCSVFormatBtn->setContentsMargins(this->buttonsMargins);
	this->openInCSVFormatBtn->setFixedSize(this->normalButtonSize);

	this->logOutBtn = new QPushButton("Log out");
	this->logOutBtn->setFont(this->fontBasic);
	this->logOutBtn->setContentsMargins(this->buttonsMargins);
	this->logOutBtn->setFixedSize(this->normalButtonSize);

	this->exitBtn = new QPushButton("Exit");
	this->exitBtn->setFont(this->fontBasic);
	this->exitBtn->setContentsMargins(this->buttonsMargins);
	this->exitBtn->setFixedSize(this->normalButtonSize);



	// adding the buttons
	this->buttonsVBL->addWidget(this->seeMovieByGenreBtn);
	this->buttonsVBL->addWidget(this->deleteMovieBtn);
	this->buttonsVBL->addWidget(this->openInCSVFormatBtn);
	this->buttonsVBL->addWidget(this->openInHTMLFormatBtn);
	this->buttonsVBL->addWidget(this->logOutBtn);
	this->buttonsVBL->addWidget(this->exitBtn);

	this->buttonsVBL->setAlignment(Qt::AlignCenter);
	this->buttonsVBL->setContentsMargins(this->buttonsMargins);
	this->buttonsWidget->setLayout(this->buttonsVBL);

	// add the buttons to the grid
	this->rightPartDataGL->addWidget(this->buttonsWidget, 2, 0, 1, 3);

}
void UserWindow::addLabelsAndLineEdits() {

	// adding the labels and line edits
	this->movieIndexLbl = new QLabel("Index: ");
	this->movieIndexLbl->setFont(this->fontBasic);
	this->movieIndexLE = new QLineEdit();
	this->movieIndexLE->setFixedSize(this->normalLineEditSize);
	this->movieIndexLE->setFont(this->fontBasic);
	this->movieIndexLbl->setBuddy(this->movieIndexLE);


	this->movieGenreLbl = new QLabel("Genre to look for (leave empty for all): ");
	this->movieGenreLbl->setFont(this->fontBasic);
	this->movieGenreLE = new QLineEdit();
	this->movieGenreLE->setFixedSize(this->normalLineEditSize);
	this->movieGenreLE->setFont(this->fontBasic);
	this->movieGenreLbl->setBuddy(this->movieGenreLE);

	// adding the widgets to the grid

	this->rightPartDataGL->addWidget(this->movieIndexLbl, 0, 0);
	this->rightPartDataGL->addWidget(this->movieIndexLE, 0, 1, 1, 2);
	this->rightPartDataGL->addWidget(this->movieGenreLbl, 1, 0);
	this->rightPartDataGL->addWidget(this->movieGenreLE, 1, 1, 1, 2);

}
void UserWindow::addTable() {
	// table
	this->watchListTable = new QTableWidget();
	this->watchListTable->setColumnCount(5);
	this->watchListTable->setHorizontalHeaderLabels(QStringList() << "Title" << "Genre" << "Year of release" << "Nr of likes" << "Trailer");
	this->watchListTable->setFixedSize(this->tableSize);
	this->watchListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->watchListTable->horizontalHeader()->setStretchLastSection(true);

	// setting the data in table
	this->updateUserWatchListTable();


	// adding the table
	this->mainHBL->addWidget(this->watchListTable);


}
void UserWindow::setSizesMarginsFonts() {

	// fonts
	this->fontBasic = QFont("New Times Roman", 14);

	// sizes
	this->usWindowSize = QSize(1400, 650);
	this->tableSize = QSize(800, 600);
	this->normalButtonSize = QSize(250, 50);
	this->normalLineEditSize = QSize(150, 30);
	this->buttonsMargins = QMargins(0, 20, 0, 20);
}


void UserWindow::setConnectionsAndSlots() {

	// creating connections
	QObject::connect(this->logOutBtn, &QPushButton::clicked, this, &UserWindow::logOut);
	QObject::connect(this->exitBtn, &QPushButton::clicked, this, &QApplication::exit);
	QObject::connect(this->seeMovieByGenreBtn, &QPushButton::clicked, this, &UserWindow::seeMoviesByGenreUserWindow);
	QObject::connect(this->deleteMovieBtn, &QPushButton::clicked, this, &UserWindow::deleteMovieFromWatchListFromIndex);
	QObject::connect(this->openInHTMLFormatBtn, &QPushButton::clicked, this, &UserWindow::openInHTMLFormat);
	QObject::connect(this->openInCSVFormatBtn, &QPushButton::clicked, this, &UserWindow::openInCSVFormat);

}

void UserWindow::start_window(UserService* userService)
{
	this->userService = userService;
	this->userService->setFile(new CSVFile());
	// widgets
	this->usWnd = new QWidget();
	this->rightPartWidget = new QWidget();
	this->buttonsWidget = new QWidget();

	// fonts


	// layouts
	this->mainHBL = new QHBoxLayout();
	this->rightPartDataGL = new QGridLayout();
	this->buttonsVBL = new QVBoxLayout();
	
	this->setSizesMarginsFonts();
	this->addButtons();
	this->addLabelsAndLineEdits();
	this->addTable();
	this->setConnectionsAndSlots();
	

	// main data form
	this->rightPartWidget->setLayout(this->rightPartDataGL);
	this->mainHBL->addWidget(this->rightPartWidget);

	this->usWnd->setFixedSize(this->usWindowSize);
	this->usWnd->setLayout(this->mainHBL);

	this->usWnd->show();
}

void UserWindow::updateUserWatchListTable() {

	this->watchListTable->setRowCount(0);
	int row;
	for (auto movie : this->userService->getWatchListAsVector()) {
		this->watchListTable->insertRow(this->watchListTable->rowCount());
		row = this->watchListTable->rowCount() - 1;
		this->watchListTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
		this->watchListTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
		this->watchListTable->setItem(row, 2, new QTableWidgetItem(QString::number(movie.getYearOfRelease())));
		this->watchListTable->setItem(row, 3, new QTableWidgetItem(QString::number(movie.getNumberOfLikes())));
		this->watchListTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
	}

}


void UserWindow::seeMoviesByGenreUserWindow() {

	QMessageBox movieMsg{};
	movieMsg.setFixedSize(QSize(400, 150));
	QPushButton* yesButton = movieMsg.addButton(tr("Yes"), QMessageBox::ActionRole);
	QPushButton* noButton = movieMsg.addButton(tr("No"), QMessageBox::ActionRole);
	QPushButton* exitButton = movieMsg.addButton(tr("Exit"), QMessageBox::ActionRole);

	QMessageBox mb;
	mb.setStyleSheet("QLabel{min-width: 100px;}");
	mb.setIcon(QMessageBox::Critical);

	Movie movie;
	string str;
	movieMsg.setStyleSheet("QLabel{min-width: 100px;}");
	movieMsg.setIcon(QMessageBox::Information);
	while (1) {
		movie = this->userService->getCurrentMovieToShowToUser(this->movieGenreLE->text().toStdString());
		movieMsg.setText("Movie: ");
		str = "Title: " + movie.getTitle() + "\n" + "Genre: " + movie.getGenre() + "\nYear of release: " + std::to_string(movie.getYearOfRelease()) + "\nNumber of likes: " + std::to_string(movie.getNumberOfLikes()) + "\nTrailer: " + movie.getTrailer();
		movieMsg.setInformativeText(QString::fromUtf8(str.c_str()));
		system(std::string("start " + movie.getTrailer()).c_str());
		movieMsg.exec();


		if (movieMsg.clickedButton() == yesButton) {
			try {
				this->userService->addMovieToWatchList(movie);
			}
			catch (UserServiceException& e) {
				mb.setDefaultButton(QMessageBox::Ok);
				mb.setText("Error");
				mb.setInformativeText(e.what());
				mb.exec();
			}
			catch (char const* str) {
				mb.setDefaultButton(QMessageBox::Ok);
				mb.setText("Error");
				mb.setInformativeText(str);
				mb.exec();
			}
			catch (...) {
				mb.setDefaultButton(QMessageBox::Ok);
				mb.setText("Error");
				mb.setInformativeText("Soemthing went wrong really bad.");
				mb.exec();
			}
		}
		else {
			if (movieMsg.clickedButton() == noButton) {
				continue;
			}
			else {
				break;
			}
		}
		this->updateUserWatchListTable();
	}
	this->userService->restartFromStart();
}

void UserWindow::deleteMovieFromWatchListFromIndex() {

	QMessageBox mb, mb2;
	string str;
	mb.setStyleSheet("QLabel{min-width: 100px;}");
	mb.setIcon(QMessageBox::Critical);
	mb2.setIcon(QMessageBox::Information);
	mb2.setFixedSize(QSize(500, 150));


	if (this->movieIndexLE->text() == "") {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText("No index given!");
		mb.exec();
		return;
	}

	try {


		mb2.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		str = "Do you want to give the movie " + this->userService->getWatchListAsVector()[this->movieIndexLE->text().toInt() - 1].getTitle() + " a like?";
		mb2.setText(QString::fromUtf8(str.c_str()));

		auto choice = mb2.exec();
		if (choice == QMessageBox::Yes) {
			this->userService->deleteMovieFromWatchList(this->movieIndexLE->text().toInt() - 1, true);
		}
		else {
			this->userService->deleteMovieFromWatchList(this->movieIndexLE->text().toInt() - 1, false);
		}


		
	}
	catch (UserServiceException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (char const* str) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(str);
		mb.exec();
	}
	catch (...) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText("Something went wrong really bad.");
		mb.exec();
	}


	this->updateUserWatchListTable();
}

void UserWindow::openInCSVFormat() {


	this->userService->setFile(new CSVFile());
	this->userService->openFile();

}

void UserWindow::openInHTMLFormat() {


	this->userService->setFile(new HTMLFile());
	this->userService->openFile();

}

void UserWindow::logOut() {
	this->usWnd->close();
}