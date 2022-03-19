#pragma once

#include <vector>
#include "Measurement.h"
#include "BMI.h"
#include "BP.h"
using namespace std;



class Person
{
private:
	string name;
	vector<Measurement*> measurementsVector;

public:
	Person() {

	}

	Person(string name) : name(name) {

	}

	string getName() {
		return this->name;
	}

	void addMeasurement(Measurement* a);

	vector<Measurement*> getAllMeasurements();

	vector<Measurement*> getMeasurementsByMonth(int month);

	bool isHealthy(int month);

	vector<Measurement*> getMeasurementsNewerThan(string date);

	void writeToFile(string filename, string date);


};

