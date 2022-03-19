#pragma once
#include "Gene.h"
#include <vector>
#include <string>
using namespace std;

class GenesRepo {
private:
	vector<Gene> geneVector;

public:



	void insertGene(Gene gene);

	string showAllGenes();

	string showAllGenesWithCertainSequence(string sequence);

	string longestSequence(string organismName1, string geneName1, string organismName2, string geneName2);

	int getSize() {
		return this->geneVector.size();
	}
};