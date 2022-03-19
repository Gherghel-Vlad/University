#include "BMI.h"
#include <iostream>
#include <iomanip>
#include <sstream>

bool BMI::isNormalValue() {

	if (this->value >= 18.5 && this->value <= 25)
		return true;

	return false;
}

string BMI::toString() {

	stringstream buffer;

	buffer << setw(10) << left << "BMI" << setw(15) << left << this->date << setw(10) << left << this->value;

	return buffer.str();
}


