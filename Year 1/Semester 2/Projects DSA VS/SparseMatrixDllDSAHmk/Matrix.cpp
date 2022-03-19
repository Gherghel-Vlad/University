#include "Matrix.h"
#include <exception>
#include "SparseMatrixDllDSAHmk/MatrixIterator.h"
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	if (nrLines <= 0 or nrCols <= 0)
		throw exception();


	this->nrOfLines = nrLines;
	this->nrOfColumns = nrCols;

	this->dll.head = NULL;
	this->dll.tail = NULL;
	
}
// Theta(1)


int Matrix::nrLines() const {
	//TODO - Implementation
	return this->nrOfLines;
}
//Theta(1)

int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->nrOfColumns;
}
// Theta(1)

TElem Matrix::element(int i, int j) const {
	// checking i and j
	if (i < 0 || i >= this->nrOfLines || j < 0 || j >= this->nrOfColumns)
		throw exception();


	// trying to find the element, stoping if i know i cant find anymore
	DLLNode* node = this->dll.head;

	while (node != NULL && (node->info.line != i || (node->info.line == i  && node->info.column != j))) {
		if (node->info.line > i || (node->info.line == i && node->info.column > j)) {
			// case in which i know i cannot find it anymore
			node = NULL;
			break;
		}
		node = node->next;
	}

	if (node == NULL)
		// case in which i didnt find the element in the list
		return NULL_TELEM;
	else
		// case in which i found it
		return node->info.value;

}
// O(n)

TElem Matrix::modify(int i, int j, TElem e) {
	// checking i and j
	if (i < 0 || i >= this->nrOfLines || j < 0 || j >= this->nrOfColumns)
		throw exception();

	TElem valueToReturn = NULL_TELEM;
	if (this->dll.head == NULL) {
		// case in which the list is empty
		this->insertFirst(i, j, e);
	}
	else {
		// finding the node to modify/that i have to insert after it
	// trying to find the element, stoping if i know i cant find anymore
		DLLNode* node = this->dll.head;

		while (node != NULL && (node->info.line != i || (node->info.line == i && node->info.column != j))) {
			if (node->info.line > i || (node->info.line == i && node->info.column > j)) {
				// case in which i know i cannot find it anymore
				break;
			}
			node = node->next;
		}

		if (node == NULL) {
			// case in which i have to insert after tail
			this->insertLast(i, j, e);
		}
		else {
			valueToReturn = node->info.value;
			// case in which i found a node that might or not might be the node that i am looking for
			if (node->info.line == i && node->info.column == j) {
				// case in which the node already exists in my list
				if (e == NULL_TELEM) {
					// this means i have to remove the node i found
					this->deleteNode(node);
				}
				else {
					// case in which i only have to modify the value
					node->info.value = e;
				}
			}
			else {
				if (e != NULL_TELEM)
				{
					// case in which i have to insert before a node, if it is NULL_TELEM, i do nothing

					if (node == this->dll.head) {
						this->insertFirst(i, j, e);
					}
					else {
						DLLNode* newNode = new DLLNode;
						newNode->info.line = i;
						newNode->info.column = j;
						newNode->info.value = e;
						newNode->next = node;
						newNode->prev = node->prev;
						node->prev->next = newNode;
						node->prev = newNode;
					}

				}
			}
		}
		
	}
	



	return valueToReturn;
}
// O(n)


void Matrix::insertFirst(int i, int j, TElem e) {
	DLLNode* newNode = new DLLNode;
	newNode->next = this->dll.head;
	newNode->prev = NULL;
	newNode->info.value = e;
	newNode->info.line = i;
	newNode->info.column = j;
	if (this->dll.tail == NULL) {
		// case in which the list is empty
		this->dll.head = newNode;
		this->dll.tail = newNode;
	}
	else {
		this->dll.head->prev = newNode;
		this->dll.head = newNode;
	}

}
// Theta(1)

void Matrix::insertLast(int i, int j, TElem e) {
	DLLNode* newNode = new DLLNode;
	newNode->next = NULL;
	newNode->prev = this->dll.tail;
	newNode->info.value = e;
	newNode->info.line = i;
	newNode->info.column = j;
	if (this->dll.head == NULL) {
		// case in which the list is empty
		this->dll.head = newNode;
		this->dll.tail = newNode;
	} 
	else {
		this->dll.tail->next = newNode;
		this->dll.tail = newNode;
	}
}
// Theta(1)

void Matrix::deleteNode(DLLNode* node) {

	if (node != NULL) {
		if (node == this->dll.head) {
			// case in which the node to be deleted is the head
			if (node == this->dll.tail) {
				// but it is the tail as well
				this->dll.head = NULL;
				this->dll.tail = NULL;
				delete node;
			}
			else {
				// case in which the list has more than one element
				this->dll.head = this->dll.head->next;
				this->dll.head->prev = NULL;
				delete node;
			}
		}
		else {
			if (node == this->dll.tail) {
				// case in which i have to delete the tail
				this->dll.tail = this->dll.tail->prev;
				this->dll.tail->next = NULL;
				delete node;
			}
			else {
				node->next->prev = node->prev;
				node->prev->next = node->next;
				delete node;
			}
		}
	}
}
// Theta(1)



MatrixIterator Matrix::iterator() const {
	return MatrixIterator(*this);
}