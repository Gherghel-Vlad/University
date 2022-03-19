

#include <exception>
#include "MatrixIterator.h"
using namespace std;

MatrixIterator::MatrixIterator(const Matrix& matrix) : matrix{ matrix } {
	this->currentNode = matrix.dll.head;
	this->currentLine = 0;
	this->currentColumn = 0;

}
//Theta(1)

TElem MatrixIterator::getCurrent() {
	if (this->currentLine == matrix.nrOfLines && this->currentColumn == matrix.nrOfColumns) {
		throw exception();
	}

	if (this->currentNode != NULL && this->currentLine == this->currentNode->info.line && this->currentColumn == this->currentNode->info.column)
	{
		return this->currentNode->info.value;
	}
	else {
		return NULL_TELEM;
	}
}
bool MatrixIterator::valid() {

	if (this->currentLine < matrix.nrOfLines) {
		return true;
	}
	else {
		return false;
	}


}
//Theta(1)

void MatrixIterator::next() {

	if (this->currentLine == matrix.nrOfLines && this->currentColumn == matrix.nrOfColumns) {
		throw exception();
	}

	if (this->currentNode != NULL && this->currentLine == this->currentNode->info.line && this->currentColumn == this->currentNode->info.column)
	{
		if(this->currentNode != NULL)
			this->currentNode = this->currentNode->next;
	}
	if (this->currentColumn < this->matrix.nrColumns() - 1) {
		this->currentColumn++;
	}
	else {
		this->currentLine++;
		this->currentColumn = 0;
	}
	
}
//Theta(1)