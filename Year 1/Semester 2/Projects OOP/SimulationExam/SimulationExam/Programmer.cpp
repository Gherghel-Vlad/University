#include "Programmer.h"

Programmer::Programmer(string _name, int _nrOfRevisedFiles, int _totalNrOfFilesThatMustBeRevised): name(_name)
{
	this->nrOfRevisedFiles = _nrOfRevisedFiles;
	this->totalNrOfFilesThatMustBeRevised = _totalNrOfFilesThatMustBeRevised;
}
