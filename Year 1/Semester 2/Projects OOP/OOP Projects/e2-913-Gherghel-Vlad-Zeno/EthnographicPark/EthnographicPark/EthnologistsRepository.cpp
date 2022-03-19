#include "EthnologistsRepository.h"

EthnologistsRepository::EthnologistsRepository()
{
	this->readFromFile();
}

vector<string> EthnologistsRepository::tokenize(string str, char delimiter) {
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}


void EthnologistsRepository::readFromFile() {
	ifstream inFile("ethnologists.txt");

	if (!inFile.is_open()) {
		return;
	}

	string line;

	while (getline(inFile, line)) {

		vector<string> strList = tokenize(line, ';');

		Ethnologist e{ strList[0], strList[1] };


		this->ethnologistVector.push_back(e);
	}

	inFile.close();
}