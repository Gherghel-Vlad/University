#pragma once
#include "Building.h"
#include <vector>
#include <sstream>
#include <fstream>

class BuildingsRepository
{
private:
	vector<Building> buildingVector;

public:
	BuildingsRepository();

	vector<Building>& getBuildingVector() {
		return this->buildingVector;
	}

	vector<string> tokenize(string str, char delimiter);

	void readFromFile();

	void addBuilding(Building _b);

};

