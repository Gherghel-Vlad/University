#pragma once
#include "Programmer.h"
#include <vector>

class ProgrammersRepository
{
private:
	vector<Programmer> programmersVector;

public:
	vector<Programmer>& getVectorProgrammers() {
		return this->programmersVector;
	}



};

