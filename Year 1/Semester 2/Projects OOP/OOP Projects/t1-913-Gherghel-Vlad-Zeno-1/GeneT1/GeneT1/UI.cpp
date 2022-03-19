
#include <iostream>
#include <string>
#include <cmath>
#include "UI.h"

UI::UI(GenesService gs) {
	this->genesService = gs;
}


void UI::printMenu() {
	cout << "\nCommands: " << endl;
	cout << "1 Insert gene" << endl;
	cout << "2 Show all genes " << endl;
	cout << "3 Show all genes that contain given gen sequence " << endl;
	cout << "4 Longest common subsequence " << endl;
	cout << "0 Exit " << endl;

}


void UI::insertGeneUI() {

	string organismName, geneName, geneSequence;

	cout << "Organism name: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, organismName);
	cout << "Gene name: ";
	getline(cin, geneName);
	cout << "Gene sequence: ";
	getline(cin, geneSequence);
	
	this->genesService.addGene(Gene(organismName, geneName, geneSequence));

}

void UI::showAllGenesUI() {
	cout << this->genesService.showAllGenes();
}

void UI::showAllGenesWithGivenSequenceUI() {
	string sequence;
	cout << "Sequence to look for: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, sequence);


	cout << this->genesService.showAllGenesWithTheGivenSequence(sequence);

}

void UI::longestSequence() {
	string organismName1, geneName1, organismName2, geneName2;

	cout << "Organism 1 name: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, organismName1);
	cout << "Gene 1 name: ";
	getline(cin, geneName1); 
	cout << "Organism 2 name: ";
	getline(cin, organismName2);
	cout << "Gene 2 name: ";
	getline(cin, geneName2);

	cout << this->genesService.getLongestSequence(organismName1, geneName1, organismName2, geneName2);


}

void UI::startUI() {
	bool done = false;

	char command[10];

	while (!done) {
		this->printMenu();

		cout << "\nGive command: ";
		cin >> command;
		try {
			switch (atoi(command))
			{
			case 1:
				this->insertGeneUI();
				break;
			case 2:
				this->showAllGenesUI();
				break;
			case 3:
				this->showAllGenesWithGivenSequenceUI();
				break;
			case 4:
				this->longestSequence();
				break;
			case 0:
				return;
			default:
				cout << "Wrong command" << endl;
				break;
			}
		}
		catch (char const* str) {
			cout << str << endl;
		}
		catch (...) {
			cout << "Careful, you are writing some bad input!";

		}

		


	}
}

