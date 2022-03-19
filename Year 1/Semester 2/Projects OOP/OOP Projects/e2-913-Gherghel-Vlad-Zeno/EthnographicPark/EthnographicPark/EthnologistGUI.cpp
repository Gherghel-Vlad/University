#include "EthnologistGUI.h"
#include <QMessageBox>


void EthnologistGUI::start_window(EthnologistsService* _ethServ, BuildingsService* _buildServ, Ethnologist e, QColor color)
{
	this->ethServ = _ethServ;
	this->buildServ = _buildServ;
	this->eth = e;
	this->color = color;
	/*this->buildServ->addObserver(this);
	this->ethServ->addObserver(this);*/

	this->mainWindow = new QWidget();
	this->mainWindow->resize(1000, 700);

	this->mainWindow->setWindowTitle(QString::fromStdString(this->eth.getName()));
	
	// settgint he abckground color
	QPalette pal = this->mainWindow->palette();
	pal.setColor(QPalette::Background, this->color);
	this->mainWindow->setAutoFillBackground(true);
	this->mainWindow->setPalette(pal);

	// setting the table view
	this->mainTableView = new QTableView();

	this->mainTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->bTableModel = new BuildingsTableModel(this->buildServ, this->eth);
	this->mainTableView->setModel(this->bTableModel);

	// setting the left side form
	this->formWidget = new QWidget();
	this->formGL = new QGridLayout();

	this->idLbl = new QLabel("ID(must be unique): ");
	this->descriptionLbl = new QLabel("Description: ");
	this->locationsLbl = new QLabel("Locations(write with ';' in between): ");

	this->idLE = new QLineEdit();
	this->descriptionLE = new QLineEdit();
	this->locationsLE = new QLineEdit();

	this->addButton = new QPushButton("Add new building");
	this->updateButton = new QPushButton("Update building (searched by id)");

	this->formGL->addWidget(this->idLbl, 0, 0);
	this->formGL->addWidget(this->idLE, 0, 1);
	this->formGL->addWidget(this->descriptionLbl, 1, 0);
	this->formGL->addWidget(this->descriptionLE, 1, 1);
	this->formGL->addWidget(this->locationsLbl, 2, 0);
	this->formGL->addWidget(this->locationsLE, 2, 1);
	this->formGL->addWidget(this->addButton, 3, 0);
	this->formGL->addWidget(this->updateButton, 3, 1);

	QObject::connect(this->addButton, &QPushButton::clicked, this, &EthnologistGUI::addNewBuilding);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &EthnologistGUI::updateBuilding);

	this->formWidget->setLayout(this->formGL);

	//setting the main layout
	this->mainHLayout = new QHBoxLayout();
	this->mainHLayout->addWidget(this->mainTableView);
	this->mainHLayout->addWidget(this->formWidget);

	
	this->mainWindow->setLayout(this->mainHLayout);
	this->mainWindow->show();

}




void EthnologistGUI::updateBuilding()
{

	string id = this->idLE->text().toLocal8Bit().constData();
	QMessageBox mb;
	string descr = this->descriptionLE->text().toLocal8Bit().constData();
	if (descr == "") {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Description problem!");
		mb.setInformativeText("The description cant be unique!");
		mb.exec();
		return;
	}
	for (int i = 0; i < this->buildServ->getBuildingsVector().size(); i++) {
		if (this->buildServ->getBuildingsVector()[i].getId() == id && this->buildServ->getBuildingsVector()[i].getThematicArea() != this->eth.getThematicArea()) {
			mb.setDefaultButton(QMessageBox::Ok);
			mb.setText("Cant change only your stuff!");
			mb.setInformativeText("Cant change only your stuff!");
			mb.exec();
			return;
		}
	
	}


	string locationsStr = this->locationsLE->text().toLocal8Bit().constData();
	vector<string> locations = this->tokenize(locationsStr, ';');
	string usedLocations = "";
	for (int i = 0; i < this->buildServ->getBuildingsVector().size(); i++) {
		if (this->buildServ->getBuildingsVector()[i].getId() != id) {
			usedLocations += this->buildServ->getBuildingsVector()[i].getLocation();
		}
	}

	for (int i = 0; i < locations.size(); i++) {
		if (usedLocations.find(locations[i]) != string::npos) {
			mb.setDefaultButton(QMessageBox::Ok);
			mb.setText("Position already used!");
			mb.setInformativeText("Check the locations that are correct!");
			mb.exec();
			return;
		}
	}


	this->buildServ->updateBuilding(Building(id, descr, this->eth.getThematicArea(), locationsStr));
	this->bTableModel->update();
}

void EthnologistGUI::addNewBuilding()
{
	// checkingn that the id is unique
	string id = this->idLE->text().toLocal8Bit().constData();
	QMessageBox mb;
	for (int i = 0; i < this->buildServ->getBuildingsVector().size(); i++) {
		if (id == this->buildServ->getBuildingsVector()[i].getId()) {
			mb.setDefaultButton(QMessageBox::Ok);
			mb.setText("Id problem!");
			mb.setInformativeText("The id is not unique");
			mb.exec();
			return;
		}
	}
	string descr = this->descriptionLE->text().toLocal8Bit().constData();
	if (descr == "") {
		mb.setDefaultButton(QMessageBox::Ok);
		mb.setText("Description problem!");
		mb.setInformativeText("The description cant be unique!");
		mb.exec();
		return;
	}

	string locationsStr = this->locationsLE->text().toLocal8Bit().constData();
	vector<string> locations = this->tokenize(locationsStr, ';');
	string usedLocations = "";
	for (int i = 0; i < this->buildServ->getBuildingsVector().size(); i++) {
		usedLocations += this->buildServ->getBuildingsVector()[i].getLocation();
	}

	for (int i = 0; i < locations.size(); i++) {
		if (usedLocations.find(locations[i]) != string::npos) {
			mb.setDefaultButton(QMessageBox::Ok);
			mb.setText("Position already used!");
			mb.setInformativeText("Check the locations that are correct!");
			mb.exec();
			return;
		}
	}
	this->buildServ->addBuilding(Building(id, descr, this->eth.getThematicArea(), locationsStr));
	this->bTableModel->update();
}


vector<string> EthnologistGUI::tokenize(string str, char delimiter) {
	vector<string> result;
	stringstream ss(str);
	string token;
	int i = 0;
	while (getline(ss, token, delimiter) && i < 3) {
		result.push_back(token);
		i++;
	}
	getline(ss, token);
	result.push_back(token);

	return result;
}

void EthnologistGUI::update()
{
	this->bTableModel->update();

}
