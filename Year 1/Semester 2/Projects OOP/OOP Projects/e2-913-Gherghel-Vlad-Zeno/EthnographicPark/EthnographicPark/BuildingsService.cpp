#include "BuildingsService.h"

void BuildingsService::addBuilding(Building _b)
{
	this->builRepo->addBuilding(_b);
	this->notify();

}

void BuildingsService::updateBuilding(Building _b)
{
	for (int i = 0; i < this->builRepo->getBuildingVector().size(); i++) {
		if (_b.getId() == this->builRepo->getBuildingVector()[i].getId()) {
			this->builRepo->getBuildingVector()[i].setDescription(_b.getDescription());
			this->builRepo->getBuildingVector()[i].setLocations(_b.getLocation());
		}
	}
	this->notify();

}
