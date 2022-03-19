
#include "Gene.h"
#include "GenesRepo.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

/// <summary>
/// Inserts a new gene if it doesnt exist already
/// </summary>
/// <param name="gene">The instance of Gene that will be added</param>
void GenesRepo::insertGene(Gene gene) {
	for (auto i = this->geneVector.begin(); i != this->geneVector.end(); ++i)
		if ((*i).organismName == gene.organismName && (*i).geneName == gene.geneName)
			throw "Gene already exists";

	this->geneVector.push_back(gene);
}

string GenesRepo::showAllGenes() {
	stringstream txt;
    vector<Gene> vg;
    vg = this->geneVector;
    sort(vg.begin(), vg.end(), [](Gene g1, Gene g2) { return g1.geneSequence.size() > g2.geneSequence.size(); });

	for (auto i = vg.begin(); i != vg.end(); ++i) {
        txt << std::left << std::setw(20) << (*i).organismName << " | " << std::left << std::setw(20) << (*i).geneName << " | " << std::right << std::setw(40) << (*i).geneSequence << "\n";
    }

	return txt.str();

}

string GenesRepo::showAllGenesWithCertainSequence(string sequence) {

	stringstream txt;
    vector<Gene> vg;
    vg = this->geneVector;
    sort(vg.begin(), vg.end(), [](Gene g1, Gene g2) { return g1.geneSequence.size() > g2.geneSequence.size(); });

    for (auto i = vg.begin(); i != vg.end(); ++i) {
		if ((*i).geneSequence.find(sequence) != std::string::npos) {
            txt << std::left << std::setw(20) << (*i).organismName << " | " << std::left << std::setw(20) << (*i).geneName << " | " << std::right << std::setw(40) << (*i).geneSequence << "\n";
        }
	}

	return txt.str();
}

/// <summary>
/// Finds the longest subsequence of 2 genes sequences
/// </summary>
/// <param name="organismName1">First organism's name</param>
/// <param name="geneName1">Fisrt gene s name</param>
/// <param name="organismName2">Second organism name</param>
/// <param name="geneName2">Second gene name</param>
/// <returns>String represeting the common subsequence of the gene s sequence</returns>
string GenesRepo::longestSequence(string organismName1, string geneName1, string organismName2, string geneName2) {

    string result = "";
    string sequence1, sequence2;
    int count = 0;


    for (auto i = this->geneVector.begin(); i != this->geneVector.end(); ++i) {
        if ((*i).organismName == organismName1 && (*i).geneName == geneName1) {
            sequence1 = (*i).geneSequence;
        }
        if ((*i).organismName == organismName2 && (*i).geneName == geneName2) {
            sequence2 = (*i).geneSequence;
        }
    }
    char buffer[40];
    string str;
    size_t length;
    for (int i = 0; i <= sequence1.size(); i++)
    {
        for (int j = 0; j <= sequence2.size(); j++)
        {
            for (int k = sequence2.size() ; k > 0 ; k--)
            {
                str = "";

                for (int k1 = j; k1 < k; k1++) {
                    str = str + sequence2[k1];
                }
                
                if (sequence1.find(str) != std::string::npos && str.size() > result.size())
                    result = str;

            }
        }
    }

    return result;




}




