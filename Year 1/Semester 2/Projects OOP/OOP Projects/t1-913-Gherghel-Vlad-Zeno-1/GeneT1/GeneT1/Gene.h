#pragma once

#include <string>
using namespace std;

class Gene {
	
public:
	 string organismName;
	 string geneName;
	 string geneSequence;

	 Gene() {};

	 Gene(string organismName, string geneName, string geneSeq) {
		 this->organismName = organismName;
		 this->geneName = geneName;
		 this->geneSequence = geneSeq;
	 }
};
