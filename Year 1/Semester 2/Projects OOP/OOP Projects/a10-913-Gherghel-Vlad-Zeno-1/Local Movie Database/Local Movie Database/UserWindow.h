#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "UserService.h"
#include "WatchListModel.h"

class UserWindow : public QWidget
{


public:

	UserWindow() {};

	void start_window(UserService* userService);

private:

	UserService* userService = nullptr;

	// widgets
	QWidget* usWnd = nullptr;
	QWidget* rightPartWidget;
	QWidget* buttonsWidget;

	// fonts
	QFont fontBasic;

	// layouts
	QHBoxLayout* mainHBL = nullptr;
	QGridLayout* rightPartDataGL = nullptr;
	QVBoxLayout* buttonsVBL = nullptr;

	// sizes
	QSize usWindowSize;
	QSize tableSize;
	QSize normalButtonSize;
	QSize normalLineEditSize;
	QMargins buttonsMargins;

	// table
	QTableView* watchListTable = nullptr;

	// models
	WatchListModel* watchListModel = nullptr;

	// buttons
	QPushButton* deleteMovieBtn;
	QPushButton* seeMovieByGenreBtn;
	QPushButton* openInHTMLFormatBtn;
	QPushButton* openInCSVFormatBtn;
	QPushButton* logOutBtn;
	QPushButton* exitBtn;

	// labels
	QLabel* movieIndexLbl;
	QLabel* movieGenreLbl;

	// line edits
	QLineEdit* movieIndexLE;
	QLineEdit* movieGenreLE;


	void updateUserWatchListTable();
	void addButtons();
	void addLabelsAndLineEdits();
	void addTable();
	void setSizesMarginsFonts();
	void setConnectionsAndSlots();

	void seeMoviesByGenreUserWindow();
	void deleteMovieFromWatchListFromIndex();
	void openInCSVFormat();
	void openInHTMLFormat();
	void logOut();

	

};

