#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

struct Node {
	TComp key;
	Node* next;
};

struct HashTable {
	Node** T;
	int m = 7;
	int h(int key) {
		if(key < 0)
			return (-1)*(key % m);
		else
			return (key % m);
	}

};


class SortedBag {
	friend class SortedBagIterator;

private:
	//TODO - Representation
	Relation relation;
	HashTable ht;
	int length;

	void rehashHashTable();
	void addNodeToSortedPlace(Node** newT, Node *startNode, int pos, Node* nodeToBeAdded);

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) ;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) ;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator();

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};