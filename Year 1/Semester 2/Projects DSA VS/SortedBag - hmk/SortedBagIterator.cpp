#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentIndex = 0;
	this->currentFrequency = 0;
}

TComp SortedBagIterator::getCurrent() {
	if (this->currentIndex == this->bag.nrOfElements) {
		throw exception();
	}
	else {
		return this->bag.elements[this->currentIndex];	
	}

}
//Theta(1)

bool SortedBagIterator::valid() {
	if (this->currentIndex < this->bag.nrOfElements) {
		return true;
	}
	else {
		return false;
	}
}
//Theta(1)

void SortedBagIterator::next() {
	if (this->currentIndex == this->bag.nrOfElements) {
		throw exception();
	}

	// checking if i have to more frequecny to cover
	if (this->bag.frequency[this->currentIndex] > this->currentFrequency) {
		this->currentFrequency++;

		if (this->bag.frequency[this->currentIndex] == this->currentFrequency) {
			this->currentIndex++;
			this->currentFrequency = 0;
		}
	}
	else {

		
		this->currentIndex++;
		this->currentFrequency = 1;

		if (this->bag.frequency[this->currentIndex] == 1) {
			this->currentIndex++;
			this->currentFrequency = 0;
		}
		

	}
}
//Theta(1)

void SortedBagIterator::first() {
	this->currentIndex = 0;
	this->currentFrequency = 0;
}
//Theta(1)

