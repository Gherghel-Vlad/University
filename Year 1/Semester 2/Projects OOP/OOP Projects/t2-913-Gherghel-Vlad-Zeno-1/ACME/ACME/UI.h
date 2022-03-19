#pragma once
#include "Person.h"


class UI
{

private:
	Person person;

public:

	UI() {

	}

	void printMenu();

	void getAllMeasurementsUI();

	void addMeasurementUI();

	void checkIfPersonHelthyUI();


	void writeToFile();

	void createPerson();

	void startMenu();




};

