#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QShortcut>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPainterPath>
#include "UndoRedoService.h"

#include "AdministratorService.h"
using namespace QtCharts;
class AdministratorWindow : public QWidget
{
    Q_OBJECT
public:
    AdministratorWindow() {
    
    };


    void start_window(AdministratorService* as);


private:
    // widgets
    QWidget* asWnd = nullptr;
    QWidget* rightPartWidget = nullptr;

    // fonts
    QFont fontBasic;

    // layouts
    QHBoxLayout* mainHBL = nullptr;
    QGridLayout* rightPartDataGL = nullptr;
    QVBoxLayout* choiceVBL = nullptr;

    // Shortcuts
    QShortcut* undoShortcut = nullptr;
    QShortcut* redoShortcut = nullptr;

    //sizes
    QSize asWindowSize;
    QSize tableSize;
    QSize normalButtonSize;
    QSize normalLineEditSize;
    QSize normalCheckBoxSize;
    QSize normalGroupButtonSize;


    // buttons
    QPushButton* addMovieBtn = nullptr;
    QPushButton* deleteMovieBtn = nullptr;
    QPushButton* updateMovieBtn = nullptr;
    QPushButton* logOutBtn = nullptr;
    QPushButton* exitBtn = nullptr;
    QPushButton* showChartBtn = nullptr;
    QPushButton* undoBtn = nullptr;
    QPushButton* redoBtn = nullptr;

    // labels
    QLabel* movieTitleLbl = nullptr;
    QLabel* movieGenreLbl = nullptr;
    QLabel* movieYearOfReleaseLbl = nullptr;
    QLabel* movieNrOfLikesLbl = nullptr;
    QLabel* movieTrailerLbl = nullptr;
    QLabel* movieIndexLbl = nullptr;

    // Line edits
    QLineEdit* movieTitleLE = nullptr;
    QLineEdit* movieGenreLE = nullptr;
    QLineEdit* movieYearOfReleaseLE = nullptr;
    QLineEdit* movieNrOfLikesLE = nullptr;
    QLineEdit* movieTrailerLE = nullptr;
    QLineEdit* movieIndexLE = nullptr;

    // table widget
    QTableWidget* moviesTable = nullptr;

    // group box and radio buttons
    QGroupBox* choiceGB = nullptr;
    QRadioButton* choiceIndexRB = nullptr;
    QRadioButton* choiceTitleRB = nullptr;

    // 

    AdministratorService* administratorService = nullptr;

    void updateAdministratorMoviesTable();
    void deleteMovieAdministratorWindow();
    void addMovieAdministratorWindow();
    void updateMovieAdministratorWindow();

    void undoAction();
    void redoAction();

    void addButtons();
    void addLabelsAndLineEdits();
    void addTable();
    void setSizesMarginsFonts();
    void addRadioBoxAndGroupBox();
    void setConnectionsAndSlots();
    void createChart();
    void logOut();

    void paintEvent(QPaintEvent* event) override;

    
};

