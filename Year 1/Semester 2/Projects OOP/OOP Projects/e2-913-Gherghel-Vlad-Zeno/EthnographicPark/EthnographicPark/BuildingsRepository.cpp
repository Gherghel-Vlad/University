#include "BuildingsRepository.h"

BuildingsRepository::BuildingsRepository()
{
	this->readFromFile();
}

vector<string> BuildingsRepository::tokenize(string str, char delimiter) {
	vector<string> result;
	stringstream ss(str);
	string token;
	int i=0;
	while (getline(ss, token, delimiter) && i < 3) {
		result.push_back(token);
		i++;
	}
	getline(ss, token);
	result.push_back(token);

	return result;
}


void BuildingsRepository::readFromFile() {
	ifstream inFile("buildings.txt");

	if (!inFile.is_open()) {
		return;
	}

	string line;

	while (getline(inFile, line)) {

		vector<string> strList = tokenize(line, ';');

		Building b{ strList[0], strList[1], strList[2], strList[3]};


		this->buildingVector.push_back(b);
	}

	inFile.close();
}

void BuildingsRepository::addBuilding(Building _b)
{
	this->buildingVector.push_back(_b);

}
