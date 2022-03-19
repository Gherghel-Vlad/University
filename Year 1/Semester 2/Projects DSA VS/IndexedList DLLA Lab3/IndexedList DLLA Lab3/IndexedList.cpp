#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() {
    this->dlla.nodes = new DLLANode[10];
    this->dlla.capacity = 10;

    this->dlla.head = -1;
    this->dlla.tail = -1;
    this->dlla.size = 0;

    for (int i = 0; i < this->dlla.capacity - 1; i++) {
        this->dlla.nodes[i].next = i + 1;
    }
    this->dlla.nodes[this->dlla.capacity -1].next = -1;
    this->dlla.firstEmpty = 0;


} // Theta(n)

int IndexedList::size() const {
	return this->dlla.size;
} // Theta(1)


bool IndexedList::isEmpty() const {
    if (this->dlla.size == 0)
        return true;
    return false;
} // Theta(1)

TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= this->dlla.size)
        throw std::exception();

    int pozC = 0;
    TElem nodC = this->dlla.head;

    // searching for the element on the given position
    while (nodC != -1 && pozC < pos) {
        nodC = this->dlla.nodes[nodC].next;
        pozC++;
    }

    if (nodC != -1) {
        return this->dlla.nodes[nodC].info;
    }
    return NULL_TELEM;

} // Theta(n)

TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= this->dlla.size)
        throw std::exception();

    int pozC = 0;
    TElem nodC = this->dlla.head;

    // searching for the element on the given position
    while (nodC != -1 && pozC < pos) {
        nodC = this->dlla.nodes[nodC].next;
        pozC++;
    }

    // modifing the value if it was found
    TElem oldValue;
    if (nodC != -1) {
        oldValue = this->dlla.nodes[nodC].info;
        this->dlla.nodes[nodC].info = e;
        return oldValue;
    }
    return NULL_TELEM;

} // Theta(n)

void IndexedList::addToEnd(TElem e) {
    
    int newNodePos = this->allocate();

    if (newNodePos == -1) {
        this->resize();
        newNodePos = this->allocate();
    }

    if (this->dlla.size == 0)
        this->dlla.head = newNodePos;

    this->dlla.nodes[newNodePos].info = e;
    this->dlla.nodes[newNodePos].next = -1;
    this->dlla.nodes[newNodePos].prev = this->dlla.tail;
    this->dlla.nodes[this->dlla.tail].next = newNodePos;
    this->dlla.tail = newNodePos;
    this->dlla.size++;

} // BC: Theta(1) WC: Theta(n)

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > this->dlla.size -1)
        throw std::exception();

    int newElemPos = this->allocate();

    if (newElemPos == -1) {
        this->resize();
        newElemPos = this->allocate();
    }

    this->dlla.nodes[newElemPos].info = e;

    if (pos == 0) {
        // case in which i add at the beginning
        if (this->dlla.head == -1) {
            // case of no elems in the list
            this->dlla.head = newElemPos;
            this->dlla.tail = newElemPos;
        }
        else {
            //case in which i already have a head
            this->dlla.nodes[this->dlla.head].prev = newElemPos;
            this->dlla.nodes[newElemPos].next = this->dlla.head;
            this->dlla.head = newElemPos;
        }
    }
    else {
        // case in which i add at given pos
        int pozC = 0;
        TElem nodC = this->dlla.head;

        // searching for the element on the given position
        while (nodC != -1 && pozC < pos - 1) {
            nodC = this->dlla.nodes[nodC].next;
            pozC++;
        }
        int nodNext;
        if (nodC != -1) {
            // found the position (always found)
            nodNext = this->dlla.nodes[nodC].next;
            this->dlla.nodes[nodNext].prev = newElemPos;
            this->dlla.nodes[nodC].next = newElemPos;
            this->dlla.nodes[newElemPos].prev = nodC;
            this->dlla.nodes[newElemPos].next = nodNext;
        }
        if (nodNext == -1) {
            this->dlla.tail = newElemPos;
        }
        else {
            this->dlla.nodes[nodNext].prev = newElemPos;
        }
    }
    this->dlla.size++;

} // O(n)

TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos > this->dlla.size -1) {
        throw std::exception();
    }

    int pozC = 0;
    TElem nodC = this->dlla.head;

    // searching for the element on the given position
    while (nodC != -1 && pozC < pos ) {
        nodC = this->dlla.nodes[nodC].next;
        pozC++;
    }
    
    int removedValue = this->dlla.nodes[nodC].info;

    if (this->dlla.size == 1) {
        // case in which the tail and the head are the same
        this->free(nodC);
        this->dlla.tail = -1;
        this->dlla.head = -1;
    }
    else {
        // case in which i have more elements in the dlla
        if (pos == 0) {
            // case in which i delete the head
            this->dlla.head = this->dlla.nodes[this->dlla.head].next;
            this->free(nodC);
        }
        else {
            if (nodC == this->dlla.tail) {
                // case in which i remove the tail
                this->dlla.tail = this->dlla.nodes[this->dlla.tail].prev;
                this->dlla.nodes[this->dlla.tail].next = -1;
                this->free(nodC);
            }
            else {
                // case in which i remove an element from inside the array
                int prevNode = this->dlla.nodes[nodC].prev;
                int nextNode = this->dlla.nodes[nodC].next;
                this->dlla.nodes[prevNode].next = nextNode;
                this->dlla.nodes[nextNode].prev = prevNode;
                this->free(nodC);
            }
        }

    }

    this->dlla.size--;
    return removedValue;

} // O(n)

int IndexedList::search(TElem e) const{
    int pozC = 0;
    TElem nodC = this->dlla.head;

    // searching for the element on the given position
    while (nodC != -1 && this->dlla.nodes[nodC].info != e) {
        nodC = this->dlla.nodes[nodC].next;
        pozC++;
    }

    if (nodC != -1) {
        return pozC;
    }
    return -1;


}

ListIterator IndexedList::iterator(){
    return ListIterator(*this);        
} // Theta(1)

IndexedList::~IndexedList() {
    delete[] this->dlla.nodes;
} //Theta(1)



int IndexedList::allocate() {

    int newElemPos = this->dlla.firstEmpty;

    if (newElemPos != -1) {
        // means we have a free spot to allocate
        this->dlla.firstEmpty = this->dlla.nodes[this->dlla.firstEmpty].next;
        if (this->dlla.firstEmpty != -1) {
            // setting the rpev of the next firstEmpty to -1
            this->dlla.nodes[this->dlla.firstEmpty].prev = -1;
        }

        dlla.nodes[newElemPos].next = -1;
        dlla.nodes[newElemPos].prev = -1;
    }

    return newElemPos;
} // Theta(1)

void IndexedList::free(int poz) {
    // frees the node from pozition poz in the array
    this->dlla.nodes[poz].next = this->dlla.firstEmpty;
    this->dlla.nodes[poz].prev = -1;

    if (this->dlla.firstEmpty != -1) {
        this->dlla.nodes[this->dlla.firstEmpty].prev = poz;
    }

    this->dlla.firstEmpty = poz;
} // Theta(1)

void IndexedList::resize() {

    DLLANode* newElems = new DLLANode[this->dlla.capacity * 2];
    int newCap = this->dlla.capacity * 2;

    for (int i = 0; i < this->dlla.capacity; i++) {
        newElems[i] = this->dlla.nodes[i];
    }

    for (int i = this->dlla.capacity; i < newCap; i++) {
        newElems[i].next = i + 1;
        newElems[i].prev = -1;
    }

    newElems[newCap - 1].next = -1;
    this->dlla.nodes = newElems;
    this->dlla.firstEmpty = this->dlla.capacity;
    this->dlla.capacity = newCap;
} // Theta(n)