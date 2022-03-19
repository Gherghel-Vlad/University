#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

NODE SortedMap::createNode(TElem e)
{
	NODE n;
	n.info = e;
	n.right = -1;
	n.left = -1;
	return n;
} // O(1)

void SortedMap::resize()
{
	this->bst.firstEmpty = this->bst.capacity;
	this->bst.capacity *= 2;
	NODE* newElements = new NODE[this->bst.capacity];
	int* newParents = new int[this->bst.capacity];
	// adding the elements back
	for (int i = 0; i < this->bst.capacity / 2; i++) {
		newElements[i] = this->bst.elements[i];
		newParents[i] = this->bst.parents[i];
	}

	// setting the next stuff to be able to use first empty easier and update it easier
	for (int i = this->bst.capacity / 2; i < this->bst.capacity; i++) {
		newElements[i].right = i + 1;
	}
	newElements[this->bst.capacity - 1].right = -1;

	delete[] this->bst.elements;
	delete[] this->bst.parents;

	this->bst.elements = newElements;
	this->bst.parents = newParents;

} // O(n)

SortedMap::SortedMap(Relation r) {
	this->relation = r;
	
	// initialising the BST
	this->bst.capacity = 20;
	this->bst.elements = new NODE[this->bst.capacity];
	this->bst.rootIndex = -1;
	this->bst.firstEmpty = 0;
	this->bst.size = 0;

	// setting the first empty stuff so i can use it
	// setting the parents as well
	this->bst.parents = new int[this->bst.capacity];
	for (int i = 0; i < this->bst.capacity-1; i++) {
		this->bst.elements[i].right = i + 1;
		this->bst.parents[i] = -1;
	}
	this->bst.elements[this->bst.capacity - 1].right = -1;


} // O(n)

TValue SortedMap::add(TKey k, TValue v) {
	
	if (this->bst.rootIndex == -1) {
		// case in which the bst is empty
		int nextEmpty = this->bst.elements[this->bst.firstEmpty].right;
		this->bst.elements[this->bst.firstEmpty] = this->createNode(TElem(k, v));
		this->bst.rootIndex = this->bst.firstEmpty;
		this->bst.size++;
		this->bst.firstEmpty = nextEmpty;
	}
	else {
		// case in which we already have elements in the bst

		// searching for it
		int currentIndex = this->bst.rootIndex, parent = -1;
		bool found = false;

		while (currentIndex != -1 && found != true) {
			if (this->bst.elements[currentIndex].info.first == k) {
				found = true;
			}
			else {
				parent = currentIndex;
				if (this->relation(this->bst.elements[currentIndex].info.first, k) == true) {
					currentIndex = this->bst.elements[currentIndex].right;
				}
				else {
					currentIndex = this->bst.elements[currentIndex].left;
				}
			}
		}

		if (found == true) {
			// case in which i found it in the bst
			TValue oldValue = this->bst.elements[currentIndex].info.second;
			this->bst.elements[currentIndex].info.second = v;
			return oldValue;
		}
		else {
			// case in which it wasnt found

			if (this->bst.firstEmpty == -1) {
				// i have to resize it
				this->resize();
			}

			int nextEmpty = this->bst.elements[this->bst.firstEmpty].right;
			this->bst.elements[this->bst.firstEmpty] = this->createNode(TElem(k, v));
			this->bst.parents[this->bst.firstEmpty] = parent;
			
			// choosing if it s in the left or right of the parent's node the new node
			if (this->relation(this->bst.elements[parent].info.first, k) == true) {
				this->bst.elements[parent].right = this->bst.firstEmpty;
			}
			else {
				this->bst.elements[parent].left = this->bst.firstEmpty;
			}
			this->bst.firstEmpty = nextEmpty;

			this->bst.size++;
		}

	}
	return NULL_TVALUE;
} // BC: O(1), WC: O(n), AV: O(n)

TValue SortedMap::search(TKey k) const {

	if (this->bst.rootIndex == -1) {
		return NULL_TVALUE;
	}

	int currentIndex = this->bst.rootIndex, parent = -1;
	bool found = false;

	while (currentIndex != -1 && found != true) {
		if (this->bst.elements[currentIndex].info.first == k) {
			found = true;
		}
		else {
			parent = currentIndex;
			if (this->relation(this->bst.elements[currentIndex].info.first, k) == true) {
				currentIndex = this->bst.elements[currentIndex].right;
			}
			else {
				currentIndex = this->bst.elements[currentIndex].left;
			}
		}
	}

	if (found == true) {
		return this->bst.elements[currentIndex].info.second;
	}

	return NULL_TVALUE;
} // O(n)

TValue SortedMap::remove(TKey k) {

	// searching for the element with key k
	int currentIndex = this->bst.rootIndex, parent = -1;
	bool found = false;

	while (currentIndex != -1 && found != true) {
		if (this->bst.elements[currentIndex].info.first == k) {
			found = true;
		}
		else {
			parent = currentIndex;
			if (this->relation(this->bst.elements[currentIndex].info.first, k) == true) {
				currentIndex = this->bst.elements[currentIndex].right;
			}
			else {
				currentIndex = this->bst.elements[currentIndex].left;
			}
		}
	}

	if (found == true) {
		// case in which it was found
		this->bst.size--;
		if (this->bst.elements[currentIndex].left == -1 && this->bst.elements[currentIndex].right == -1) {
			// case in which it has no descendants
			if (currentIndex == this->bst.rootIndex) {
				// case in which i delete the root
				this->bst.firstEmpty = currentIndex;
				this->bst.rootIndex = -1;
			}
			else {
				// case in which is just a normal node, a leaf
				// checking if it s at the right or left of the parent node
				if (this->bst.elements[parent].left == currentIndex) {
					// case in which is the left node of the parent
					this->bst.elements[parent].left = -1;
				}
				else {
					// case in which is the right node
					this->bst.elements[parent].right = -1;
				}

			}
		}
		else {
			// case in which it has descendants
			if (this->bst.elements[currentIndex].left != -1 && this->bst.elements[currentIndex].right != -1) {
				// case in which it has 2 descendants
				int currentIndex1 = this->bst.elements[currentIndex].left, parent1 = -1;
				
				// searching for the rightest most node starting from the left of the currentIndex element
				while (this->bst.elements[currentIndex1].right != -1) {
					parent1 = currentIndex1;
					currentIndex1 = this->bst.elements[currentIndex1].right;
				}


				if (this->bst.elements[currentIndex].right != currentIndex1) {
					// case in which the found node is right the right node of the soon to be deleted node
					this->bst.elements[currentIndex1].right = -1;
				}
				else {
					// case in which it isnt
					this->bst.elements[currentIndex1].right = this->bst.elements[currentIndex].right;
					if (currentIndex != this->bst.rootIndex) {
						this->bst.elements[parent1].right = -1;
					}
					this->bst.elements[parent1].left = this->bst.elements[currentIndex1].left;
				}

				this->bst.elements[currentIndex1].left = this->bst.elements[currentIndex].left;

				if (currentIndex == this->bst.rootIndex) {
					// case in which the deleted index was the root
					this->bst.rootIndex = currentIndex1;
				}
				else {
					// case in which it wasnt the root
					// checking if it s at the right or left of the parent node
					if (this->bst.elements[parent].left == currentIndex) {
						// case in which is the left node of the parent
						this->bst.elements[parent].left = currentIndex1;
					}
					else {
						// case in which is the right node
						this->bst.elements[parent].right = currentIndex1;
					}
				
						this->bst.parents[currentIndex1] = parent;
				}

			}
			else {
				// case in which it has one descendant
				if (currentIndex == this->bst.rootIndex) {
					// case in which the deleted index was the root

					if (this->bst.elements[currentIndex].left != -1) {
						this->bst.rootIndex = this->bst.elements[currentIndex].left;
					}
					else {
						this->bst.rootIndex = this->bst.elements[currentIndex].right;
					}
					this->bst.parents[this->bst.rootIndex] = -1;
					
				}
				else {
					// checking if it s at the right or left of the parent node
					if (this->bst.elements[parent].left == currentIndex) {
						// case in which is the left node of the parent
						if (this->bst.elements[currentIndex].left != -1) {
							this->bst.elements[parent].left = this->bst.elements[currentIndex].left;
						}
						else {
							this->bst.elements[parent].left = this->bst.elements[currentIndex].right;
						}
					}
					else {
						// case in which is the right node
						if (this->bst.elements[currentIndex].left != -1) {
							this->bst.elements[parent].right = this->bst.elements[currentIndex].left;
						}
						else {
							this->bst.elements[parent].right = this->bst.elements[currentIndex].right;
						}
					}
				}
			}
		}

		this->bst.parents[currentIndex] = -1;
		this->bst.elements[currentIndex].right = this->bst.firstEmpty;
		this->bst.firstEmpty = currentIndex;
		return this->bst.elements[currentIndex].info.second;

	}

	return NULL_TVALUE;
} // BC: O(1) WC: O(n) AV: O(n)

int SortedMap::size() const {
	return this->bst.size;
} // O(1)

bool SortedMap::isEmpty() const {
	if (this->bst.size == 0) {
		return true;
	}
	else {
		return false;
	}
} // O(1)

SMIterator SortedMap::iterator() {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[] this->bst.elements;
	delete[] this->bst.parents;
} // O(1)
