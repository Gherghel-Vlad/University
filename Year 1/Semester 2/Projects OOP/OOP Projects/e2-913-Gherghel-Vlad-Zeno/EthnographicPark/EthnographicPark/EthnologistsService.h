#pragma once
#include "EthnologistsRepository.h"
#include "Observer.h"

class EthnologistsService: public Observable
{
private:
	EthnologistsRepository* ethRepo;

public:

	EthnologistsService(EthnologistsRepository* _ethRepo) : ethRepo(_ethRepo) {

	}

	vector<Ethnologist>& getEthnologistVector() {
		return this->ethRepo->getEthnologistVector();
	}

};

