#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	SortedBag& bag;
	SortedBagIterator(SortedBag& b);

	//TODO - Representation
	HashTable copyOfHt;
	Node* currentNode;


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	//removes and returns the current element from the iterator
//after the operation the current element from the Iterator is the next element from the SortedBag, or, if the removed element was the last one, the iterator is invalid
//throws exception if the iterator is invalid
	TElem remove();

};

