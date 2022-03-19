#pragma once
#include <string>
using namespace std;
class Programmer
{
private:
	string name;
	int nrOfRevisedFiles;
	int totalNrOfFilesThatMustBeRevised;

public:

	Programmer(string _name, int _nrOfRevisedFiles, int _totalNrOfFilesThatMustBeRevised);

	string getName() {
		return this->name;
	}

	void setName(string value) {
		this->name = value;
	}

	int getNrOfRevisedFiles() {
		return this->nrOfRevisedFiles;
	}

	void setNrOfRevisedFiles(int value) {
		this->nrOfRevisedFiles = value;
	}

	int getTotalNrOfFilesThatMustBeRevised() {
		return this->totalNrOfFilesThatMustBeRevised;
	}

	void setTotalNrOfFilesThatMustBeRevised(int value) {
		this->totalNrOfFilesThatMustBeRevised = value;
	}

};

