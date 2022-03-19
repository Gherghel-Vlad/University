#include "LocalMovieDatabase.h"
#include "AdministratorWindow.h"
#include "UndoRedoService.h"

LocalMovieDatabase::LocalMovieDatabase(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void LocalMovieDatabase::start_administrator() {
	// starting administrator gui
	this->asWnd = new AdministratorWindow();

	this->asWnd->start_window(this->administratorService);
	
}

void LocalMovieDatabase::logOut() {
	if (this->asWnd != NULL)
		this->asWnd->close();
	if (this->usWnd != NULL)
		this->usWnd->close();

	this->wndStart->show();

}


void LocalMovieDatabase::start_user() {

	
	// starting administrator gui
	this->usWnd = new UserWindow();


	this->usWnd->start_window(this->userService);

}


void LocalMovieDatabase::start_application(AdministratorService& as, UserService& us){

	// allocating variables
	this->administratorService = &as;
	this->userService = &us;

	// creating widgets
	this->wndStart = new QWidget{};
	this->wndStart->setFixedSize(700, 300);
	QWidget* buttonsWnd = new QWidget();

	// creating layout
	QVBoxLayout* vblStart = new QVBoxLayout();
	QHBoxLayout* hblButtons = new QHBoxLayout();

	// creating labels
	QLabel* lblStart = new QLabel("Welcome to the local movie database! :)");
	QFont fontStart = QFont("New Times Roman", 14);
	lblStart->setFont(fontStart);
	lblStart->setAlignment(Qt::AlignCenter);

	// creating buttons
	QSize btnSize = QSize(300, 70);
	QPushButton* asPushButton = new QPushButton();
	asPushButton->setFont(fontStart);
	asPushButton->setFixedSize(btnSize);
	asPushButton->setText("Start administrator service.");

	QPushButton* usPushButton = new QPushButton();
	usPushButton->setFont(fontStart);
	usPushButton->setFixedSize(btnSize);
	usPushButton->setText("Start user service.");

	// connections
	QObject::connect(asPushButton, &QPushButton::clicked, this, &LocalMovieDatabase::start_administrator);
	QObject::connect(usPushButton, &QPushButton::clicked, this, &LocalMovieDatabase::start_user);

	// adding everything up
	hblButtons->addWidget(asPushButton);
	hblButtons->addWidget(usPushButton);
	buttonsWnd->setLayout(hblButtons);
	

	vblStart->addWidget(lblStart);
	vblStart->addWidget(buttonsWnd);
	this->wndStart->setLayout(vblStart);

	this->wndStart->show();
}

