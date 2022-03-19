#pragma once
#include "Measurement.h"


class BP: public Measurement
{
private:
	int systolicValue;
	int diastolicValue;

public:
	BP(string date, int sistolic, int diastolic) : Measurement{ date }, systolicValue(sistolic), diastolicValue(diastolic){

	}

	bool isNormalValue();

	string toString();



};

