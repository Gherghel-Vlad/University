#include "AdministratorWindow.h"
#include "Validators.h"
#include "LocalMovieDatabase.h"
#include "UI.h"



void AdministratorWindow::addButtons() {
	// creating the buttons 
	this->addMovieBtn = new QPushButton("Add movie");
	this->addMovieBtn->setFont(this->fontBasic);
	this->addMovieBtn->setFixedSize(this->normalButtonSize);

	this->deleteMovieBtn = new QPushButton("Delete movie");
	this->deleteMovieBtn->setFont(this->fontBasic);
	this->deleteMovieBtn->setFixedSize(this->normalButtonSize);

	this->updateMovieBtn = new QPushButton("Update movie");
	this->updateMovieBtn->setFont(this->fontBasic);
	this->updateMovieBtn->setFixedSize(this->normalButtonSize);

	this->logOutBtn = new QPushButton("Log out");
	this->logOutBtn->setFont(this->fontBasic);
	this->logOutBtn->setFixedSize(this->normalButtonSize);

	this->exitBtn = new QPushButton("Exit");
	this->exitBtn->setFont(this->fontBasic);
	this->exitBtn->setFixedSize(this->normalButtonSize);

	this->showChartBtn = new QPushButton("Show chart");
	this->showChartBtn->setFont(this->fontBasic);
	this->showChartBtn->setFixedSize(this->normalButtonSize);

	this->undoBtn = new QPushButton("Undo");
	this->undoBtn->setFont(this->fontBasic);
	this->undoBtn->setFixedSize(this->normalButtonSize);

	this->redoBtn = new QPushButton("Redo");
	this->redoBtn->setFont(this->fontBasic);
	this->redoBtn->setFixedSize(this->normalButtonSize);

	// adding buttons
	this->rightPartDataGL->addWidget(this->addMovieBtn, 3, 0);
	this->rightPartDataGL->addWidget(this->deleteMovieBtn, 3, 2);
	this->rightPartDataGL->addWidget(this->updateMovieBtn, 4, 1);
	this->rightPartDataGL->addWidget(this->showChartBtn, 4, 2);
	this->rightPartDataGL->addWidget(this->logOutBtn, 5, 0);
	this->rightPartDataGL->addWidget(this->exitBtn, 5, 2);
	this->rightPartDataGL->addWidget(this->undoBtn, 6, 0);
	this->rightPartDataGL->addWidget(this->redoBtn, 6, 2);

}
void AdministratorWindow::addLabelsAndLineEdits() {
	// creating the labels and textlines
	this->movieTitleLbl = new QLabel("Title: ");
	this->movieTitleLbl->setFont(this->fontBasic);
	this->movieTitleLE = new QLineEdit();
	this->movieTitleLE->setFixedSize(this->normalLineEditSize);
	this->movieTitleLE->setFont(this->fontBasic);
	this->movieTitleLbl->setBuddy(this->movieTitleLE);

	this->movieGenreLbl = new QLabel("Genre: ");
	this->movieGenreLbl->setFont(fontBasic);
	this->movieGenreLE = new QLineEdit();
	this->movieGenreLE->setFixedSize(this->normalLineEditSize);
	this->movieGenreLE->setFont(this->fontBasic);
	this->movieGenreLbl->setBuddy(this->movieGenreLE);

	this->movieYearOfReleaseLbl = new QLabel("Year of release: ");
	this->movieYearOfReleaseLbl->setFont(this->fontBasic);
	this->movieYearOfReleaseLE = new QLineEdit();
	this->movieYearOfReleaseLE->setFixedSize(this->normalLineEditSize);
	this->movieYearOfReleaseLE->setFont(this->fontBasic);
	this->movieYearOfReleaseLbl->setBuddy(this->movieYearOfReleaseLE);

	this->movieNrOfLikesLbl = new QLabel("Number of likes: ");
	this->movieNrOfLikesLbl->setFont(this->fontBasic);
	this->movieNrOfLikesLE = new QLineEdit();
	this->movieNrOfLikesLE->setFixedSize(this->normalLineEditSize);
	this->movieNrOfLikesLE->setFont(this->fontBasic);
	this->movieNrOfLikesLbl->setBuddy(this->movieNrOfLikesLE);

	this->movieTrailerLbl = new QLabel("Trailer: ");
	this->movieTrailerLbl->setFont(this->fontBasic);
	this->movieTrailerLE = new QLineEdit();
	this->movieTrailerLE->setFixedSize(this->normalLineEditSize);
	this->movieTrailerLE->setFont(this->fontBasic);
	this->movieTrailerLbl->setBuddy(this->movieTrailerLE);

	this->movieIndexLbl = new QLabel("Index: ");
	this->movieIndexLbl->setFont(this->fontBasic);
	this->movieIndexLE = new QLineEdit();
	this->movieIndexLE->setFixedSize(this->normalLineEditSize);
	this->movieIndexLE->setFont(this->fontBasic);
	this->movieIndexLbl->setBuddy(this->movieIndexLE);


	// adding labels and line edits
	this->rightPartDataGL->addWidget(this->movieTitleLbl, 0, 0);
	this->rightPartDataGL->addWidget(this->movieTitleLE, 0, 1);
	this->rightPartDataGL->addWidget(this->movieGenreLbl, 0, 2);
	this->rightPartDataGL->addWidget(this->movieGenreLE, 0, 3);
	this->rightPartDataGL->addWidget(this->movieYearOfReleaseLbl, 1, 0);
	this->rightPartDataGL->addWidget(this->movieYearOfReleaseLE, 1, 1);
	this->rightPartDataGL->addWidget(this->movieNrOfLikesLbl, 1, 2);
	this->rightPartDataGL->addWidget(this->movieNrOfLikesLE, 1, 3);
	this->rightPartDataGL->addWidget(this->movieTrailerLbl, 2, 0);
	this->rightPartDataGL->addWidget(this->movieTrailerLE, 2, 1);
	this->rightPartDataGL->addWidget(this->movieIndexLbl, 2, 2);
	this->rightPartDataGL->addWidget(this->movieIndexLE, 2, 3);

}
void AdministratorWindow::addTable() {
	// table
	this->moviesTable = new QTableWidget();
	this->moviesTable->setColumnCount(5);
	this->moviesTable->setHorizontalHeaderLabels(QStringList() << "Title" << "Genre" << "Year of release" << "Nr of likes" << "Trailer");
	this->moviesTable->setFixedSize(this->tableSize);
	this->moviesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->moviesTable->horizontalHeader()->setStretchLastSection(true);

	// setting the data in table
	this->updateAdministratorMoviesTable();


	// adding the table
	this->mainHBL->addWidget(this->moviesTable);

}
void AdministratorWindow::setSizesMarginsFonts() {
	// fonts
	this->fontBasic = QFont("New Times Roman", 14);

	// sizes
	this->asWindowSize = QSize(1700, 700);
	this->tableSize = QSize(800, 600);
	this->normalButtonSize = QSize(250, 60);
	this->normalLineEditSize = QSize(200, 30);
	this->normalCheckBoxSize = QSize(200, 100);
	this->normalGroupButtonSize = QSize(200, 100);
}
void AdministratorWindow::setConnectionsAndSlots() {

	// creating connections
	QObject::connect(this->logOutBtn, &QPushButton::clicked, this, &AdministratorWindow::logOut);
	QObject::connect(this->exitBtn, &QPushButton::clicked, this, &QApplication::exit);
	QObject::connect(this->addMovieBtn, &QPushButton::clicked, this, &AdministratorWindow::addMovieAdministratorWindow);
	QObject::connect(this->deleteMovieBtn, &QPushButton::clicked, this, &AdministratorWindow::deleteMovieAdministratorWindow);
	QObject::connect(this->updateMovieBtn, &QPushButton::clicked, this, &AdministratorWindow::updateMovieAdministratorWindow);
	QObject::connect(this->showChartBtn, &QPushButton::clicked, this, &AdministratorWindow::createChart);
	QObject::connect(this->undoBtn, &QPushButton::clicked, this, &AdministratorWindow::undoAction);
	QObject::connect(this->redoBtn, &QPushButton::clicked, this, &AdministratorWindow::redoAction);
	this->undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this->undoBtn);
	QObject::connect(this->undoShortcut, &QShortcut::activated, this, &AdministratorWindow::undoAction);
	this->redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this->redoBtn);
	QObject::connect(this->redoShortcut, &QShortcut::activated, this, &AdministratorWindow::redoAction);



}


void AdministratorWindow::createChart() {


	QWidget* chartWnd = new QWidget();
	chartWnd->setFixedSize(QSize(1200, 900));
	QVBoxLayout* vl = new QVBoxLayout();
	QStringList categories;
	QCategoryAxis* axisX = new QCategoryAxis();
	QBarSeries* series = new QBarSeries();
	QBarSet* set = new QBarSet("Nothing");
	QString str = "";
	int count = 0;
	for (auto movie : this->administratorService->getAllMovies()) {
		set = new QBarSet(QString::fromStdString(movie.getTitle()));
		*set << movie.getNumberOfLikes();
		series->append(set);
		str += QString::fromStdString(movie.getTitle());
		count++;
	}
	categories << str;
	QChart* chart = new QtCharts::QChart();
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->addSeries(series);
	chart->setAxisX(axisX, series);
	series->attachAxis(axisX);
	chart->setTitle("Title and number of likes");

	QBarCategoryAxis* axis = new QBarCategoryAxis();
	axis->append(categories);

	chart->createDefaultAxes();
	chart->setAxisX(axis, series);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);


	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	vl->addWidget(chartView);
	chartWnd->setLayout(vl);

	chartWnd->show();


	/*QWidget* chartWnd = new QWidget();
	chartWnd->setFixedSize(QSize(1200, 900));
	QVBoxLayout* vl = new QVBoxLayout();
	QStringList categories;
	QCategoryAxis* axisX = new QCategoryAxis();
	QLineSeries* series = new QLineSeries();
	int count = 0;
	for (auto movie : this->administratorService->getAllMovies()) {
		series->append(count, movie.getNumberOfLikes());
		axisX->append(QString::fromStdString(movie.getTitle()), count);
		count++;
	}

	QChart* chart = new QtCharts::QChart();
	chart->addSeries(series);
	chart->setAxisX(axisX, series);
	chart->setTitle("Title and number of likes");
	chart->legend()->setVisible(false);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QValueAxis* axisY = new QValueAxis;
	axisY->setLinePenColor(series->pen().color());

	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	vl->addWidget(chartView);
	chartWnd->setLayout(vl);

	chartWnd->show();*/
}



void AdministratorWindow::logOut() {

	this->asWnd->close();
}



void AdministratorWindow::addRadioBoxAndGroupBox() {


	// creating the checkbox and group box
	this->choiceGB = new QGroupBox();
	this->choiceIndexRB = new QRadioButton(tr("&Use the index."));
	this->choiceTitleRB = new QRadioButton(tr("U&se the title."));
	choiceIndexRB->setChecked(true);

	// creating the layout for the group box
	this->choiceVBL = new QVBoxLayout();
	this->choiceVBL->addWidget(this->choiceIndexRB);
	this->choiceVBL->addWidget(this->choiceTitleRB);
	this->choiceGB->setLayout(this->choiceVBL);


	// adding the check boxes
	this->rightPartDataGL->addWidget(this->choiceGB, 4, 0);
}


void AdministratorWindow::start_window(AdministratorService* as)
{
	//this->administratorService = as;

	//// widgets
	this->asWnd = new QWidget();
	//this->rightPartWidget = new QWidget();



	//// layouts
	//this->mainHBL = new QHBoxLayout();
	//this->rightPartDataGL = new QGridLayout();


	//// adding the elements up

	//this->setSizesMarginsFonts();
	//this->addButtons();
	//this->addLabelsAndLineEdits();
	//this->addTable();
	//this->addRadioBoxAndGroupBox();
	//this->setConnectionsAndSlots();

	//// adding the main data asking
	//// adding the layouts together
	//// main data form
	//this->rightPartWidget->setLayout(this->rightPartDataGL);
	//this->mainHBL->addWidget(this->rightPartWidget);

	//this->asWnd->setFixedSize(this->asWindowSize);
	//this->asWnd->setLayout(this->mainHBL);

	//this->mainHBL->addWidget(this->movieGenreLbl);
	//this->setLayout(this->mainHBL);



}


void AdministratorWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen2{ Qt::red, 1, Qt::SolidLine, Qt::RoundCap };
	painter.setPen(pen2);
	QBrush brush{ Qt::red, Qt::FDiagPattern };
	painter.setBrush(brush);
	painter.drawEllipse(150, 100, 250, 130);

	painter.drawText(QPoint(150, 100), "haha");

	this->repaint();

}

void AdministratorWindow::updateAdministratorMoviesTable() {

	this->moviesTable->setRowCount(0);
	int row;
	for (auto movie : this->administratorService->getAllMovies()) {
		this->moviesTable->insertRow(this->moviesTable->rowCount());
		row = this->moviesTable->rowCount() - 1;
		this->moviesTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
		this->moviesTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
		this->moviesTable->setItem(row, 2, new QTableWidgetItem(QString::number(movie.getYearOfRelease())));
		this->moviesTable->setItem(row, 3, new QTableWidgetItem(QString::number(movie.getNumberOfLikes())));
		this->moviesTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
	}
}

void AdministratorWindow::deleteMovieAdministratorWindow()
{

	QMessageBox mb;
	mb.setIcon(QMessageBox::Critical);
	try {
		if (this->choiceIndexRB->isChecked()) {

			this->administratorService->deleteMovieFromPosition(this->movieIndexLE->text().toInt()-1);
		}
		else {
			this->administratorService->deleteMovieWithTitle(this->movieTitleLE->text().toStdString());
		}
	}
	catch (MoviesRepositoryException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (ValidatorsException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (AdministratorServiceException& e) {
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
		mb.setInformativeText("Something went really wrong.");
		mb.exec();
	}

	this->updateAdministratorMoviesTable();
}

void AdministratorWindow::addMovieAdministratorWindow()
{

	QMessageBox mb;
	mb.setIcon(QMessageBox::Critical);
	try {
		
		this->administratorService->addMovie(Movie(this->movieTitleLE->text().toStdString(), this->movieGenreLE->text().toStdString(), 
			this->movieYearOfReleaseLE->text().toInt(), this->movieNrOfLikesLE->text().toInt(), this->movieTrailerLE->text().toStdString()));
		
	}
	catch (MoviesRepositoryException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (ValidatorsException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (AdministratorServiceException& e) {
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
		mb.setInformativeText("Something went really wrong.");
		mb.exec();
	}

	this->updateAdministratorMoviesTable();
}

void AdministratorWindow::updateMovieAdministratorWindow()
{

	QMessageBox mb;
	mb.setIcon(QMessageBox::Critical);

	try {
		if (this->choiceIndexRB->isChecked()) {

			this->administratorService->updateMovieFromPositionn(Movie(this->movieTitleLE->text().toStdString(), this->movieGenreLE->text().toStdString(),
				this->movieYearOfReleaseLE->text().toInt(), this->movieNrOfLikesLE->text().toInt(), this->movieTrailerLE->text().toStdString()), this->movieIndexLE->text().toInt() -1);
		}
		else {
			this->administratorService->updateMovieWithTitle(Movie(this->movieTitleLE->text().toStdString(), this->movieGenreLE->text().toStdString(),
				this->movieYearOfReleaseLE->text().toInt(), this->movieNrOfLikesLE->text().toInt(), this->movieTrailerLE->text().toStdString()), this->movieTitleLE->text().toStdString());

		}
	}
	catch (MoviesRepositoryException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (ValidatorsException& e) {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText(e.what());
		mb.exec();
	}
	catch (AdministratorServiceException& e) {
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
		mb.setInformativeText("Something went really wrong.");
		mb.exec();
	}

	this->updateAdministratorMoviesTable();

}

void AdministratorWindow::undoAction()
{
	if (this->administratorService->undoRedoService->executeUndoCommand() == false) {
		QMessageBox mb;
		mb.setIcon(QMessageBox::Critical);
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText("There are no undoes to be made.");
		mb.exec();
		return;
	}
	this->updateAdministratorMoviesTable();
}

void AdministratorWindow::redoAction()
{
	if (this->administratorService->undoRedoService->executeRedoCommand() == false) {
		QMessageBox mb;
		mb.setIcon(QMessageBox::Critical);
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Error");
		mb.setInformativeText("There are no redoes to be made.");
		mb.exec();
		return;
	}
	this->updateAdministratorMoviesTable();
}

