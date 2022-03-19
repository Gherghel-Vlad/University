#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
	
	// creating a deep copy
	this->copyOfHt.m = this->bag.ht.m;
	this->copyOfHt.T = new Node * [this->copyOfHt.m];
	Node* currentNodeInCopy, * currentNodeInMain, * prevNodeInCopy;
	for (int i = 0; i < this->copyOfHt.m; i++) {
		this->copyOfHt.T[i] = nullptr;

		if (this->bag.ht.T[i] != nullptr) {
			this->copyOfHt.T[i] = new Node;

			currentNodeInCopy = this->copyOfHt.T[i];
			currentNodeInMain = this->bag.ht.T[i];

			while (currentNodeInMain != nullptr) {
				currentNodeInCopy->key = currentNodeInMain->key;
				if (currentNodeInMain->next == nullptr) {
					currentNodeInCopy->next = nullptr;
					break;
				}
				else {
					currentNodeInMain = currentNodeInMain->next;
					prevNodeInCopy = currentNodeInCopy;
					currentNodeInCopy = new Node;
					prevNodeInCopy->next = currentNodeInCopy;
				}
			}
		}
	}


	// getting the first elem from the hasttable
	this->currentNode = nullptr;
	TComp minimumValue = NULL_TCOMP;
	int minimumValuePos;
	this->currentNode = nullptr;
	for (int i = 0; i < this->copyOfHt.m; i++) {
		if (this->copyOfHt.T[i] != nullptr) {
			if (minimumValue == -11111) {
				// case in which i dont have a minimum yet
				minimumValue = this->copyOfHt.T[i]->key;
				minimumValuePos = i;
			}
			else {
				if (this->bag.relation(this->copyOfHt.T[i]->key, minimumValue) == true) {
					// case in which i have and i found a new one
					minimumValue = this->copyOfHt.T[i]->key;
					minimumValuePos = i;
				}
			}
		}

	}
	if (minimumValue != -11111) {
		this->currentNode = this->copyOfHt.T[minimumValuePos];
		this->copyOfHt.T[minimumValuePos] = this->copyOfHt.T[minimumValuePos]->next;
	}
} // Theta(n + m)

TComp SortedBagIterator::getCurrent() {
	if (this->currentNode == nullptr)
		throw exception();

	return this->currentNode->key;
} // Theta(1)

bool SortedBagIterator::valid() {
	if (this->currentNode != nullptr)
		return true;
	else {
		return false;
	}
} // Theta(1)

void SortedBagIterator::next() {
	if (this->currentNode == nullptr)
		throw exception();

	TComp minimumValue = NULL_TCOMP;
	int minimumValuePos;
	currentNode = nullptr;
	for (int i = 0; i < this->copyOfHt.m; i++) {
		if (this->copyOfHt.T[i] != nullptr) {
			if (minimumValue == -11111) {
				// case in which i dont have a minimum yet
				minimumValue = this->copyOfHt.T[i]->key;
				minimumValuePos = i;
			}
			else {
				if (this->bag.relation(this->copyOfHt.T[i]->key ,minimumValue) == true) {
					// case in which i have and i found a new one
					minimumValue = this->copyOfHt.T[i]->key;
					minimumValuePos = i;
				}
			}
		}

	}
	if (minimumValue != -11111) {
		currentNode = this->copyOfHt.T[minimumValuePos];
		this->copyOfHt.T[minimumValuePos] = this->copyOfHt.T[minimumValuePos]->next;
	}
} // Theta(m)

void SortedBagIterator::first() {
	this->copyOfHt.m = this->bag.ht.m;
	this->copyOfHt.T = new Node * [this->copyOfHt.m];
	Node* currentNodeInCopy, * currentNodeInMain, * prevNodeInCopy;
	for (int i = 0; i < this->copyOfHt.m; i++) {
		this->copyOfHt.T[i] = nullptr;

		if (this->bag.ht.T[i] != nullptr) {
			this->copyOfHt.T[i] = new Node;

			currentNodeInCopy = this->copyOfHt.T[i];
			currentNodeInMain = this->bag.ht.T[i];

			while (currentNodeInMain != nullptr) {
				currentNodeInCopy->key = currentNodeInMain->key;
				if (currentNodeInMain->next == nullptr) {
					currentNodeInCopy->next = nullptr;
					break;
				}
				else {
					currentNodeInMain = currentNodeInMain->next;
					prevNodeInCopy = currentNodeInCopy;
					currentNodeInCopy = new Node;
					prevNodeInCopy->next = currentNodeInCopy;
				}
			}
		}

	}
	
	this->currentNode = nullptr;
	TComp minimumValue = NULL_TCOMP;
	int minimumValuePos;
	this->currentNode = nullptr;
	for (int i = 0; i < this->copyOfHt.m; i++) {
		if (this->copyOfHt.T[i] != nullptr) {
			if (minimumValue == -11111) {
				// case in which i dont have a minimum yet
				minimumValue = this->copyOfHt.T[i]->key;
				minimumValuePos = i;
			}
			else {
				if (this->bag.relation(this->copyOfHt.T[i]->key, minimumValue) == true) {
					// case in which i have and i found a new one
					minimumValue = this->copyOfHt.T[i]->key;
					minimumValuePos = i;
				}
			}
		}

	}
	if (minimumValue != -11111) {
		this->currentNode = this->copyOfHt.T[minimumValuePos];
		this->copyOfHt.T[minimumValuePos] = this->copyOfHt.T[minimumValuePos]->next;
	}
} // Theta(n + m)


TElem SortedBagIterator::remove() {

	if (!this->valid())
		throw exception();

	TElem deletedElem = NULL_TCOMP;
	deletedElem = this->currentNode->key;

	// removing the element
	this->bag.remove(this->currentNode->key);

	// going to the next one
	this->next();

	return deletedElem;
} // Theta(m+alpha), alpha - the number of elements in the sll


