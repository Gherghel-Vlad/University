#pragma once

#include "GenesRepo.h"

class GenesService {

private:
	GenesRepo genesRepo;

public:
	GenesService() {};

	GenesService(GenesRepo& gr);

	void addGene(Gene g);

	string showAllGenes();

	string showAllGenesWithTheGivenSequence(string sequence);

	string getLongestSequence(string organismName1, string geneName1, string organismName2, string geneName2);


};
