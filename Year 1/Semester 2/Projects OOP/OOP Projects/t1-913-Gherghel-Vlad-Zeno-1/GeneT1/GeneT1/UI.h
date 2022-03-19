#pragma once

#include "GenesService.h"

class UI {
private:
	GenesService genesService;

public:
	UI() {};

	UI(GenesService gs);

	void startUI();

	void printMenu();

	void insertGeneUI();

	void showAllGenesUI();

	void showAllGenesWithGivenSequenceUI();

	void longestSequence();

};

