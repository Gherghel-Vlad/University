#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(IndexedList& list) : list(list){
    this->currentElementPos = list.dlla.head;
} // Theta(1)

void ListIterator::first(){
    this->currentElementPos = this->list.dlla.head;
} //Theta(1)

void ListIterator::next(){
    if (this->currentElementPos == -1) {
        throw std::exception();
    }
    this->currentElementPos = this->list.dlla.nodes[this->currentElementPos].next;
} // Theta(1)

bool ListIterator::valid() const{
    if (this->currentElementPos != -1)
        return true;
	return false;
} // Theta(1)

TElem ListIterator::getCurrent() const{
    if (this->currentElementPos == -1)
        throw std::exception();
    return this->list.dlla.nodes[this->currentElementPos].info;
} //Theta(1)


TElem ListIterator::remove() {
    if (this->currentElementPos == -1)
        throw std::exception();

    TElem returnElem = this->list.dlla.nodes[this->currentElementPos].info;
    int nextCurrentElemPos = this->list.dlla.nodes[this->currentElementPos].next;



    // deleting the node
    int nodC = this->currentElementPos;
    if (this->list.dlla.size == 1) {
        // case in which the tail and the head are the same
        this->list.free(nodC);
        this->list.dlla.tail = -1;
        this->list.dlla.head = -1;
    }
    else {
        // case in which i have more elements in the dlla
        if (nodC == 0) {
            // case in which i delete the head
            this->list.dlla.head = this->list.dlla.nodes[this->list.dlla.head].next;
            this->list.free(nodC);
        }
        else {
            if (nodC == this->list.dlla.tail) {
                // case in which i remove the tail
                this->list.dlla.tail = this->list.dlla.nodes[this->list.dlla.tail].prev;
                this->list.dlla.nodes[this->list.dlla.tail].next = -1;
                this->list.free(nodC);
            }
            else {
                // case in which i remove an element from inside the array
                int prevNode = this->list.dlla.nodes[nodC].prev;
                int nextNode = this->list.dlla.nodes[nodC].next;
                this->list.dlla.nodes[prevNode].next = nextNode;
                this->list.dlla.nodes[nextNode].prev = prevNode;
                this->list.free(nodC);
            }
        }

    }
    this->list.dlla.size--;

    // going to the next element
    this->currentElementPos = nextCurrentElemPos;

    return returnElem;
} // Theta(1)