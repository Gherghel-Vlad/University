#pragma once
#include <string>
using namespace std;

class SourceFile
{
private:
	string name;
	string status;
	string creator;
	string reviewer;

public:

	const string& getName() const {
		return this->name;
	}

	const string& getStatus() const {
		return this->status;
	}

	const string& getCreator() const {
		return this->creator;
	}

	const string& getReviewer() const {
		return this->reviewer;
	}
	
	void setCreator(const string& str) {
		this->creator = str;
	}

	void setReviewer(const string& str) {
		this->reviewer = str;
	}
};

