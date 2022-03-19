
#include "GenesService.h"


GenesService::GenesService(GenesRepo& gr) {
	this->genesRepo = gr;
}

void GenesService::addGene(Gene g) {
	this->genesRepo.insertGene(g);
}

string GenesService::showAllGenes() {
	return this->genesRepo.showAllGenes();


}

string GenesService::showAllGenesWithTheGivenSequence(string sequence) {
	return this->genesRepo.showAllGenesWithCertainSequence(sequence);
}

string GenesService::getLongestSequence(string organismName1, string geneName1, string organismName2, string geneName2) {
	return this->genesRepo.longestSequence(organismName1, geneName1, organismName2, geneName2);
}


