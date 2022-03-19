#pragma once
#include "Ethnologist.h"
#include <vector>
#include <sstream>
#include <fstream>
class EthnologistsRepository
{
private:
	vector<Ethnologist> ethnologistVector;

public:
	EthnologistsRepository();

	vector<Ethnologist>& getEthnologistVector() {
		return this->ethnologistVector;
	}

	vector<string> tokenize(string str, char delimiter);
	
	void readFromFile();

};

