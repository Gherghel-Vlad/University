#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

void SMIterator::push(int index) {
	this->stack[this->currentStackPos] = index;
	this->currentStackPos++;
}// O(1)

int SMIterator::pop() {
	this->currentStackPos--;
	return this->stack[this->currentStackPos];
} // O(1)


SMIterator::SMIterator(SortedMap& m) : map(m){
	this->stack = new int[this->map.bst.capacity];
	this->currentStackPos = 0;
	int nodeIndex = this->map.bst.rootIndex;
	while (nodeIndex != -1) {
		this->push(nodeIndex);
		nodeIndex = this->map.bst.elements[nodeIndex].left;
	}

	if (this->currentStackPos != 0) {
		this->currentNodeIndex = this->pop();
	}
	else {
		this->currentNodeIndex = -1;
	}

}// O(1)

void SMIterator::first(){
	delete[] this->stack;
	this->stack = new int[this->map.bst.capacity];
	this->currentStackPos = 0;
	int nodeIndex = this->map.bst.rootIndex;
	while (nodeIndex != -1) {
		this->push(nodeIndex);
		nodeIndex = this->map.bst.elements[nodeIndex].left;
	}

	if (this->currentStackPos != 0) {
		this->currentNodeIndex = this->pop();
	}
	else {
		this->currentNodeIndex = -1;
	}
}// O(1)

void SMIterator::next(){
	if (this->currentNodeIndex == -1) {
		throw exception();
	}


	int node = this->currentNodeIndex;
	if (this->map.bst.elements[node].right != -1) {
		node = this->map.bst.elements[node].right;
		while (node != -1) {
			this->push(node);
			node = this->map.bst.elements[node].left;
		}
	}
	if (this->currentStackPos != 0) {
		this->currentNodeIndex = this->pop();
	}
	else {
		this->currentNodeIndex = -1;
	}
}// O(1)

bool SMIterator::valid() const{
	if (this->currentNodeIndex != -1) {
		return true;
	}
	else {
		return false;
	}
}// O(1)

TElem SMIterator::getCurrent() const{
	if (this->currentNodeIndex == -1) {
		throw exception();
	}
	return this->map.bst.elements[this->currentNodeIndex].info;
	
} // O(1)

TElem SMIterator::remove()
{
	if (this->currentNodeIndex == -1) {
		throw exception();
	}

	TElem removedValue = this->map.bst.elements[this->currentNodeIndex].info;

	this->next();

	this->map.remove(removedValue.first);


	return removedValue;
}
// BC: O(1) WC: O(n) AV: O(n)


