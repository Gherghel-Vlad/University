#include <iostream>
#include "Lista.h"
#include <stdexcept>


// deleteOccurencesOfElementRec(l1l2…ln, elem) = [], , n=0
//												 deleteOccurencesOfElementRec(l2…ln, elem), l1=elem
//												 l1 U deleteOccurencesOfElementRec(l2…ln, elem), otherwise
void deleteOccurencesOfElementRec(List *l, Node** prevNode, Node** currentNode, TElem elem)
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
			if (cn == l->getFirstNode()) {
				l->setFirstNode(l->getFirstNode()->next);
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


	deleteOccurencesOfElementRec(l, &pn, &cn, elem);
}

//hasEvenNrOfElementsRec(l1l2…ln) = true, n=0  
//									false, n=1 
//									hasEvenNrOfElementsRec(l3l4…ln)

bool hasEvenNrOfElementsRec(List l)
{
	if (l.getFirstNode() == nullptr) {
		// even nr
		return true;
	}
	else {
		if ((l.getFirstNode())->next == nullptr)
		{
			// odd nr
			return false;
		}
		else {
			l.deleteFirst();
			l.deleteFirst();
			return hasEvenNrOfElementsRec(l);

		}
	}
	throw std::exception("Sth went horribly wrong!.");
}

int main() {

	List l;

	TElem val;

	std::cout << "val = ";
	std::cin >> val;

	while (val != 0) {
		l.addNewNodeAtTheEnd(val);
		std::cout << "val = ";
		std::cin >> val;
	}

	/*
	l.printList();
	l.deleteFirst();
	l.deleteFirst();
	*/

	l.printList();

	try {
		bool result = hasEvenNrOfElementsRec(l);
		//bool result = l.hasEvenNrOfElements();
		if (result == true) {
			std::cout << "\nIt has even number of elements." << "\n";
		}
		else {
			std::cout << "\nIt doesn't have even number of elements." << "\n";
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	
	TElem elem;
	std::cout << "Give element to delete: ";
	std::cin >> elem;

	//l.deleteOccurencesOfElement(elem);
	deleteOccurencesOfElementRec(&l, nullptr, l.getFirstNodeAsReference(), elem);

	l.printList();

	

	return 0;
}
