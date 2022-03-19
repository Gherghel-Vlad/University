#pragma once

#include "Measurement.h"

class BMI: public Measurement
{
private:
	double value;

public:
	BMI(string date, double value) : Measurement{date}, value(value) {

	}

	bool isNormalValue();

	string toString();



};

