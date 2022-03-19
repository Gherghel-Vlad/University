#include "Lista.h"
#include <iostream>

Node* List::createEmptyNode()
{
	Node* new_node = new Node();
	new_node->next = nullptr;
	new_node->value = 0;
	return new_node;
}



// deleteOccurencesOfElementRec(l1l2…ln, elem) = [], , n=0
//												 deleteOccurencesOfElementRec(l2…ln, elem), l1=elem
//												 l1 U deleteOccurencesOfElementRec(l2…ln, elem), otherwise
void List::deleteOccurencesOfElementRec(Node** prevNode, Node** currentNode, TElem elem)
{
	Node* pn;
	if (prevNode != nullptr) {
		pn = (*prevNode);
	}
	else {
		pn = nullptr;
	}
	Node* cn = (*currentNode);

	if (cn == nullptr) {
		return;
	}
	else {
		if (cn->value == elem) {
			Node* n = cn->next;
			if (cn == this->firstNode) {
				this->firstNode = cn->next;
			}
			if (pn == nullptr) {
				delete cn;
				cn = n;
			}
			else {
				pn->next = n;
				delete cn;
				cn = n;
			}
		}
		else {
			pn = cn;
			cn = cn->next;
		}
	}


	this->deleteOccurencesOfElementRec(&pn, &cn, elem);
}

List::List()
{
	this->firstNode = nullptr;
}

Node* List::getFirstNode()
{
	return this->firstNode;
}

Node** List::getFirstNodeAsReference()
{
	return &(this->firstNode);
}

void List::setFirstNode(Node* n)
{
	this->firstNode = n;
}

void List::addNewNodeAtTheEnd(TElem value)
{
	this->addNewNodeAtTheEndRec(&this->firstNode, value);
}


void List::addNewNodeAtTheEndRec(Node** node, TElem value)
{
	if (*node == nullptr)
	{
		Node* addedNode = this->createEmptyNode();
		addedNode->value = value;
		*node = addedNode;
		return;
	}
	else {
		if ((*node)->next == nullptr) {
			Node* addedNode = this->createEmptyNode();
			addedNode->value = value;
			(*node)->next = addedNode;
			return;
		}
		else {
			;
			this->addNewNodeAtTheEndRec(&(*node)->next, value);
			return;
		}
	}

}

void List::destroyList()
{
	this->destroyListRec(this->firstNode);
}

void List::destroyListRec(Node* n)
{
	if (n != nullptr){
		this->destroyListRec(n->next);
		delete n;
	}
}


void List::printList()
{
	this->printListRec(this->firstNode);
}

void List::deleteFirst()
{
	if (this->firstNode != nullptr)
	{
		this->firstNode = this->firstNode->next;
	}
}

void List::deleteOccurencesOfElement(TElem elem)
{
	this->deleteOccurencesOfElementRec(nullptr, &this->firstNode, elem);
}

List List::deepCopy()
{
	List list;

	this->deepCopyRec(&list, this->firstNode);

	return list;
}

void List::deepCopyRec(List* l, const Node* n)
{
	if (n == nullptr) {
		return;
	}
	else{
		l->addNewNodeAtTheEnd(n->value);
		this->deepCopyRec(l, n->next);
	}

}



void List::printListRec(Node* node)
{
	if (node != nullptr) {
		std::cout << node->value << " ";
		this->printListRec(node->next);
	}
}

bool List::hasEvenNrOfElements()
{
	return this->hasEvenNrOfElementsRec(this->firstNode);
}


//hasEvenNrOfElementsRec(l1l2…ln) = true, n=0  
//									false, n=1 
//									hasEvenNrOfElementsRec(l3l4…ln)
bool List::hasEvenNrOfElementsRec(Node* n)
{
	if (n == nullptr) {
		// even nr
		return true;
	}
	else {
		if (n->next == nullptr)
		{
			// odd nr
			return false;
		}
		else {
			this->hasEvenNrOfElementsRec(n->next->next);

		}
	}
}