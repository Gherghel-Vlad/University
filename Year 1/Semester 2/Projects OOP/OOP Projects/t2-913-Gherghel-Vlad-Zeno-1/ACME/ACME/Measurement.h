#pragma once

#include <string>
#include <exception>
using namespace std;


class Measurement
{
protected:
	string date;

public:
	Measurement(string date) : date{ date } {
		if (date.length() != 10)
			throw "Date is incorrect!";

	}

	string getDate() {
		return this->date;
	}

	virtual bool isNormalValue() = 0;

	virtual string toString()=0;


};

