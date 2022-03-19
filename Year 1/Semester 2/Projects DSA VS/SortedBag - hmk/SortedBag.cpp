#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>
using namespace std;

SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->capacity = 10;
	this->nrOfElements = 0;
	this->elements = new TComp[this->capacity];
	this->frequency = new int[this->capacity]();
}

void SortedBag::add(TComp e) {
	int index = 0, i;

	//searching for the element
	for (i = 0; i < this->nrOfElements; i++)
	{
		//found it, so i increase the frequeancy and leave
		if (e == this->elements[i]) {
			this->frequency[i]++;
			return;
		}
	}

	// i didnt find it, so i need to know where to insert the element based on the given relation
	// searching for the position where to be put
	index = 0;
	while (index < this->nrOfElements && this->relation(this->elements[index], e)) {
		index++;
	}

	// resize the dynamic vector if it s full
	if (this->nrOfElements == this->capacity) {
		this->resize();
	}

	// shift elements to the right from index
	for (i = this->nrOfElements; i > index; i--) {
		this->elements[i] = this->elements[i-1];
		this->frequency[i] = this->frequency[i-1];
	}
	//added a new item, so increase the value of nrofelements
	this->nrOfElements++;
	this->elements[index] = e;
	this->frequency[index] = 1;
}
// BC: Theta(1) WC: Theta(n) => Total complexity: O(n)

void SortedBag::resize() {
	this->capacity = this->capacity * 2;
	TComp* newElementsArray = new TComp[this->capacity];
	int* newFrequencyArray = new int[this->capacity];

	//copying the elements
	int i;
	for (i = 0; i < this->nrOfElements; i++) {
		newElementsArray[i] = this->elements[i];
		newFrequencyArray[i] = this->frequency[i];
	}

	// freeing the ex-arrays
	delete[] this->elements;
	delete[] this->frequency;

	// setting the new arrays
	this->elements = newElementsArray;
	this->frequency = newFrequencyArray;
}
// Theta(n)

bool SortedBag::remove(TComp e) {
	int i, j;

	//searching for e
	for (i = 0; i < this->nrOfElements; i++)
	{
		if (e == this->elements[i]) {
			this->frequency[i]--;
			if (this->frequency[i] == 0) {
				// if the freq is 0, shifting everything to the left starting from i
				for (j = i; j < this->nrOfElements - 1; j++)
				{
					this->elements[j] = this->elements[j + 1];
					this->frequency[j] = this->frequency[j + 1];
				}
				this->nrOfElements--;
			}
			return true;
		}
	}

	return false;
}
// BC: Theta(1) WC: Theta(n) => Total complexity: O(n)

bool SortedBag::search(TComp elem) const {
	
	int i;

	for (i = 0; i < this->nrOfElements; i++) {
		if (this->relation(this->elements[i], elem)) {
			if (elem == this->elements[i]) {
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;
}
// BC: Theta(1) WC: Theta(n) => Total complexity: O(n)


int SortedBag::nrOccurrences(TComp elem) const {
	int i;

	for (i = 0; i < this->nrOfElements; i++) {
		if (this->relation(this->elements[i], elem)) {
			if (elem == this->elements[i]) {
				return this->frequency[i];
			}
		}
		else {
			return 0;
		}
	}
	return 0;
}
// BC: Theta(1) WC: Theta(n) => Total complexity: O(n)



int SortedBag::size() const {
	int sum = 0; 
	int i;
	for (i = 0; i < this->nrOfElements; i++) {
		sum += this->frequency[i];
	}
	return sum;
}
//Theta(n)


bool SortedBag::isEmpty() const {
	if (this->nrOfElements > 0) {
		return false;
	}
	else {
		return true;
	}
}
// Theta(1)


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)


SortedBag::~SortedBag() {
	delete[] this->elements;
	delete[] this->frequency;
}
//Theta(1)


void SortedBag::addOccurrences(int nr, TComp elem) {
	if (nr < 0) {
		throw exception();
	}
	int index = 0, i;

	//searching for the element
	for (i = 0; i < this->nrOfElements; i++)
	{
		//found it, so i increase the frequeancy and leave
		if (elem == this->elements[i]) {
			this->frequency[i]+=nr;
			return;
		}
	}

	// i didnt find it, so i need to know where to insert the element based on the given relation
	// searching for the position where to be put
	index = 0;
	while (index < this->nrOfElements&& this->relation(this->elements[index], elem)) {
		index++;
	}

	// resize the dynamic vector if it s full
	if (this->nrOfElements == this->capacity) {
		this->resize();
	}

	// shift elements to the right from index
	for (i = this->nrOfElements; i > index; i--) {
		this->elements[i] = this->elements[i - 1];
		this->frequency[i] = this->frequency[i - 1];
	}
	//added a new item, so increase the value of nrofelements
	this->nrOfElements++;
	this->elements[index] = elem;
	this->frequency[index] = nr;
}
// BC: Theta(1) WC: Theta(n) => Total complexity: O(n)

