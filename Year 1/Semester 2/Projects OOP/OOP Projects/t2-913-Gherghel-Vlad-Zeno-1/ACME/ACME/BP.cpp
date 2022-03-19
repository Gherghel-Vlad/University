#include "BP.h"

#include <iostream>
#include <iomanip>
#include <sstream>

bool BP::isNormalValue() {

	if (this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79)
		return true;

	return false;
}

string BP::toString() {

	stringstream buffer;

	buffer << setw(10) << left << "BP" << setw(15) << left << this->date << setw(10) << left << this->systolicValue << setw(10) << left << this->diastolicValue;

	return buffer.str();
}



