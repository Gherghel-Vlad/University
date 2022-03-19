#pragma once
#include <QWidget>
#include <QTableView>
#include "EthnologistsService.h"
#include "BuildingsService.h"
#include "BuildingsTableModel.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class EthnologistGUI: public QWidget, Observer
{
	Q_OBJECT
private:
	EthnologistsService* ethServ;
	BuildingsService* buildServ;
	QColor color;
	Ethnologist eth;

	QWidget* mainWindow = nullptr;
	QWidget* formWidget = nullptr;

	QTableView* mainTableView = nullptr;
	BuildingsTableModel* bTableModel = nullptr;

	// Layouts
	QHBoxLayout* mainHLayout = nullptr;
	QGridLayout* formGL = nullptr;

	// labels and text fields
	QLabel* idLbl = nullptr;
	QLabel* descriptionLbl = nullptr;
	QLabel* locationsLbl = nullptr;


	QLineEdit* idLE = nullptr;
	QLineEdit* descriptionLE = nullptr;
	QLineEdit* locationsLE = nullptr;

	QPushButton* addButton = nullptr;
	QPushButton* updateButton = nullptr;


	vector<string> tokenize(string str, char delimiter);

	void update();

public:

	void start_window(EthnologistsService* _ethServ, BuildingsService* _buildServ, Ethnologist e, QColor color);

	void updateBuilding();
	void addNewBuilding();
};

