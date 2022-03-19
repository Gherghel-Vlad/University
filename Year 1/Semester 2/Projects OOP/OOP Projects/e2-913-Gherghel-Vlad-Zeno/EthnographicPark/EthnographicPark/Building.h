#pragma once
#include <string>
#include <vector>
using namespace std;
class Building
{
private:
	string id;
	string description;
	string thematicArea;
	string location;

public:
	Building() {};

	Building(string _id, string _description, string _thematicArea, string _location);

	string getId() {
		return this->id;
	}
	string getDescription() {
		return this->description;
	}
	string getThematicArea() {
		return this->thematicArea;
	}
	string getLocation() {
		return this->location;
	}


	void setDescription(string value) {
		this->description = value;
	}


	void setLocations(string value) {
		this->location = value;
	}
};

