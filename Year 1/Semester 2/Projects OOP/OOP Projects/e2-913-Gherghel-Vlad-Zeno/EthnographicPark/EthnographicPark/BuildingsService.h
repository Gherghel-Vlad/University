#pragma once
#include "BuildingsRepository.h"
#include "Observer.h"

class BuildingsService: public Observable
{
private:
	BuildingsRepository* builRepo;

public:
	BuildingsService(BuildingsRepository* _builRepo): builRepo(_builRepo) {

	}

	vector<Building> getBuildingsVector() {
		return this->builRepo->getBuildingVector();
	}

	void addBuilding(Building _b);
	void updateBuilding(Building _b);

};

