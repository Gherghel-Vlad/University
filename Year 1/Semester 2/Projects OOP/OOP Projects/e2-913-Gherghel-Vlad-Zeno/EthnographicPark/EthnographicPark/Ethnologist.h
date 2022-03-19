#pragma once
#include <string>
using namespace std;
class Ethnologist
{

private:
	string name;
	string thematicArea;

public:
	Ethnologist() {};

	Ethnologist(string _name, string _thematicArea);

	string getName() {
		return this->name;
	}

	string getThematicArea() {
		return this->thematicArea;
	}

	

};

