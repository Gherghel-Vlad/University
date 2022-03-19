#include "Person.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void Person::addMeasurement(Measurement* a) {
	this->measurementsVector.push_back(a);
}

vector<Measurement*> Person::getAllMeasurements() {
	return this->measurementsVector;
}

vector<Measurement*> Person::getMeasurementsByMonth(int month) {
	int monthOfM;
	stringstream ss;
	string monthM;
	string date;
	vector<Measurement*> v;

	for (auto m : this->measurementsVector) {
		date = m->getDate();
		stringstream ss(date);
		getline(ss, monthM, '.');
		getline(ss, monthM, '.');
		monthOfM = atoi(monthM.c_str());
		
		if (month == 1)
		{
			if(monthOfM == 4)
				v.push_back(m);
		}
		else {
			if (monthOfM >= month - 1 || monthOfM == month) {
				v.push_back(m);
			}
		}

	}

	return v;

}

bool Person::isHealthy(int month) {

	int monthOfM;
	stringstream ss;
	string monthM;
	string date;
	vector<Measurement*> v;

	for (auto m : this->measurementsVector) {
		date = m->getDate();
		stringstream ss(date);
		getline(ss, monthM, '.');
		getline(ss, monthM, '.');
		monthOfM = atoi(monthM.c_str());

		
		if (monthOfM == month) {
			if (!m->isNormalValue())
				return false;
		}
	}
	return true;

}

vector<Measurement*> Person::getMeasurementsNewerThan(string date) {

	int monthOfM, year, day;
	stringstream ss;
	string monthM;

	int givenMonth, givenYear, givenDay;

	stringstream s(date);
	getline(s, monthM, '.');
	givenYear = atoi(monthM.c_str());
	getline(s, monthM, '.');
	givenMonth = atoi(monthM.c_str());
	getline(s, monthM, '.');
	givenDay = atoi(monthM.c_str());
	vector<Measurement*> v;

	for (auto m : this->measurementsVector) {
		stringstream ss(m->getDate());
		getline(ss, monthM, '.');
		year = atoi(monthM.c_str());
		getline(ss, monthM, '.');
		monthOfM = atoi(monthM.c_str());
		getline(ss, monthM, '.');
		day = atoi(monthM.c_str());

		if (givenYear < year) {
			v.push_back(m);
		}
		else {
			if (givenMonth < monthOfM && givenYear == year) {
				v.push_back(m);
			}
			else {
				if (day > givenDay && givenYear == year && givenMonth == monthOfM) {
					v.push_back(m);
				}
			}
		}

	}

	return v;


}

void Person::writeToFile(string filename, string date) {
	ofstream f(filename);

	if (!f.is_open()) {
		return;
	}
	for (auto m : this->getMeasurementsNewerThan(date))
		f << m->toString() << "\n";

	f.close();

}