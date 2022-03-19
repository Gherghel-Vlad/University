#include "UI.h"
#include <iostream>


void UI::printMenu() {
	cout << "\nCommands: " << endl;
	cout << "1 Add measurement" << endl;
	cout << "2 Get all measurements " << endl;
	cout << "3 Check if person healthy" << endl;
	cout << "4  Write to file" << endl;
	cout << "0 Exit " << endl;
}

void UI::getAllMeasurementsUI() {

	vector<Measurement*> v = this->person.getAllMeasurements();
	cout << this->person.getName() << endl;
	for (auto m : v) {
		cout << m->toString() << endl;
	}

}

void UI::addMeasurementUI() {

	string type, date;
	Measurement* m;

	cout << "Type of measurement: ";
	cin >> type;
	cout << "Date of measurement: ";
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin >> date;

	if (type == "BMI") {
		double value;

		cout << "Value of BMI: ";
		cin >> value;

		m = new BMI(date, value);

		this->person.addMeasurement(m);
	}
	else {
		if (type == "BP") {
			int sys;
			int dis;

			cout << "Systolic value of BP: ";
			cin >> sys;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Diastolic value of BP: ";
			cin >> dis;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			m = new BP(date, sys, dis);

			this->person.addMeasurement(m);
		}
		else {
			throw "Type invalid!";
		}
	}

	if (m->isNormalValue())
		cout << "Values are in normal range.\n";
	else
		cout << "Values are not in normal range.\n";
}

void UI::createPerson() {
	string name;
	cout << "Name of person: ";
	cin >> name;

	this->person = Person{ name };
}

void UI::checkIfPersonHelthyUI() {
	int month;

	cout << "Give month to start the check from: ";
	cin >> month;

	vector<Measurement*> m = this->person.getMeasurementsByMonth(month);

	bool isHealthy = true;

	for (auto mm : m) {
		if (!mm->isNormalValue())
		{
			isHealthy = false;
			break;
		}
	}

	if (isHealthy == false) {
		cout << "Person is not healthy" << endl;
	}
	else {
		cout << "Person is healthy" << endl;
	}

}

void UI::writeToFile() {

	string filename;
	string date;
	cout << "Give filename to save to: ";
	cin >> filename;
	cout << "Give date from which to save: ";
	cin >> date;

	this->person.writeToFile(filename, date);

}

void UI::startMenu() {
	bool done = false;

	char command[10];

	this->createPerson();

	this->person.addMeasurement(new BMI("2021.03.07", 100));
	this->person.addMeasurement(new BMI("2020.08.27", 120));
	this->person.addMeasurement(new BMI("2021.02.17", 70));
	this->person.addMeasurement(new BP("2021.02.17", 70.5, 80));
	this->person.addMeasurement(new BP("2021.03.17", 70.5, 80));
	this->person.addMeasurement(new BP("2021.01.27", 70.5, 80));
	this->person.addMeasurement(new BP("2021.03.09", 70.5, 80));

	while (!done) {
		this->printMenu();
		cout << "Give command: ";
		cin >> command;
		try {
			switch (atoi(command))
			{
			case 1:
				this->addMeasurementUI();
				break;
			case 2:
				this->getAllMeasurementsUI();
				break;
			case 3:
				this->checkIfPersonHelthyUI();
				break;
			case 4:
				this->writeToFile();
				break;
			case 0:
				return;
			default:
				cout << "Wrong command" << endl;
				break;
			}
			cout << "Command succesfully executed!\n";
		}
		catch (char const* str) {
			cout << str << endl;
		}
		catch (...) {
			cout << "Careful, you are writing some bad input!";

		}

	}



}