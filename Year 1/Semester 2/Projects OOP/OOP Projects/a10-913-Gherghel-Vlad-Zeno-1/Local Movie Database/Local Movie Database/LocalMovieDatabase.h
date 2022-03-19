#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ui_LocalMovieDatabase.h"
#include "UserService.h"
#include "AdministratorService.h"
#include "AdministratorWindow.h"
#include "UserWindow.h"
#include "UndoRedoService.h"

class LocalMovieDatabase : public QMainWindow
{
    Q_OBJECT

public:
    LocalMovieDatabase(QWidget *parent = Q_NULLPTR);


    void start_application(AdministratorService& as, UserService& us);

private:
    Ui::LocalMovieDatabaseClass ui;

    AdministratorService* administratorService = nullptr;
    UserService* userService = nullptr;

    QWidget* wndStart = nullptr;
    AdministratorWindow* asWnd = nullptr;
    UserWindow* usWnd = nullptr;
    
    // common used functions
    void logOut();

    // main functions
	void start_administrator();
	void start_user();



};
