#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->length = 0;
	this->ht.T = new Node * [this->ht.m];

	for (int i = 0; i < this->ht.m; i++) {
		this->ht.T[i] = nullptr;
	}

} // Theta(m)


void SortedBag::addNodeToSortedPlace(Node** newT, Node* startNode, int pos, Node* nodeToBeAdded) {

	Node* prev = nullptr, * currentNode;
	currentNode = startNode;
	while (currentNode != nullptr && this->relation(nodeToBeAdded->key, currentNode->key) == false) {
		prev = currentNode; 
		currentNode = currentNode->next;
	}

	if (currentNode == nullptr && prev != nullptr) {
		// case in which i have to add the new node at the end
		prev->next = nodeToBeAdded;
		nodeToBeAdded->next = nullptr;
	}
	else {
		if (currentNode == startNode) {
			// case in which i add at the beginning
			nodeToBeAdded->next = startNode;
			newT[pos] = nodeToBeAdded;
		}
		else {
			// case in which i add between 2 nodes
			prev->next = nodeToBeAdded;
			nodeToBeAdded->next = currentNode;
		}

	}

} // Theta(alpha) - alpha is the nubmer of elements in the sll

void SortedBag::rehashHashTable() {

	// resizing and creating a new array
	this->ht.m *= 2;
	int nr = this->ht.m;
	Node** newT  = new Node*[this->ht.m];

	for (int i = 0; i < this->ht.m; i++) {
		newT[i] = nullptr;
	}

	int currentLength = 0, pos, currentPos = 0;
	Node* currentNode = nullptr;
	Node* newNode;
	Node* compareNode;
	while (currentLength < this->length && currentPos < this->ht.m/2) {
		if (currentNode == nullptr) {
			// case in which i am trying to find the next non null element in the array 
			while (currentNode == nullptr) {
				currentNode = this->ht.T[currentPos];
				currentPos++;
			}
		}
		else {
			// means that i already have a current node and i go to the next one
			currentNode = currentNode->next;
			if (currentNode == nullptr)
				continue;
		}
		currentLength++;

		// starting the adding of elements in the new hashtable
		pos = this->ht.h(currentNode->key);

		if (newT[pos] == nullptr) {
			// case in which this is the first node on that pos
			newNode = new Node;
			newNode->key = currentNode->key;
			newNode->next = nullptr;

			newT[pos] = newNode;
		}
		else {
			// case in which there are already some nodes there so i add it where it belongs
			newNode = new Node;
			newNode->key = currentNode->key;
			newNode->next = nullptr;

			// adding the new node where it should be added in the SLL
			this->addNodeToSortedPlace(newT, newT[pos], pos, newNode);
		}


	}
	// deleting and allocating the new hashtable
	delete[] this->ht.T;

	this->ht.T = newT;
} // Theta(n * alpha+ m) - n the number of elements, m the number of singly linked lists, alpha = the number of elements from the respective linked list


void SortedBag::add(TComp e) {
	
	// resize and rehash the hashtable if necessarry
	if (this->length / (float)this->ht.m > 0.7)
		this->rehashHashTable();

	Node* nodeToBeAdded = new Node;
	nodeToBeAdded->key = e;
	nodeToBeAdded->next = nullptr;

	int pos = this->ht.h(e);

	if (this->ht.T[pos] == nullptr) {
		// case in which this is the first node on that pos
		this->ht.T[pos] = nodeToBeAdded;
	}
	else {
		// case in which there are already some nodes there so i add it where it belongs
		// adding the new node where it should be added in the SLL
		this->addNodeToSortedPlace(this->ht.T, this->ht.T[pos], pos, nodeToBeAdded);
	}
	this->length++;

} // WC: Theta(n*alpha+ m + alpha) BC: Theta(alpha) AC: Theta(alpha)


bool SortedBag::remove(TComp e) {
	
	if (this->length == 0) {
		return false;
	}
	int pos = this->ht.h(e);

	Node* prev = nullptr, *currentNode;
	currentNode = this->ht.T[pos];
	while (currentNode != nullptr && currentNode->key != e) {
		prev = currentNode;
		currentNode = currentNode->next;
	}
	int found = 0;
	if (currentNode == nullptr) {
		// case in which it didnt find the value e or threre arent elements
		return false;
	}
	else {
		// case in which an instance of e was found
		if (prev == nullptr) {
			// case in which is the first one
			this->ht.T[pos] = this->ht.T[pos]->next;
			delete currentNode;
			found = 1;
		}
		else {
			if (currentNode->next == nullptr) {
				// case in which is the last node from the sll
				prev->next = nullptr;
				delete currentNode;
				found = 1;
			}
			else {
				// case in which is in the middle of the sll
				prev->next = currentNode->next;
				delete currentNode;
				found = 1;
			}
		}
		
	}

	if (found == 1) {
		this->length--;
		return true;
	}


	return false;
} // Theta(alpha)


bool SortedBag::search(TComp elem) {
	
	if (this->length == 0)
		return false;

	Node* currentNode;
	int pos = this->ht.h(elem);
	currentNode = this->ht.T[pos];
	while (currentNode != nullptr && currentNode->key != elem) {
		currentNode = currentNode->next;
	}

	if (currentNode == nullptr) {
		// case in which it didnt find it
		return false;
	}
	else {
		return true;
	}
} // Theta(alpha)


int SortedBag::nrOccurrences(TComp elem)  {
	if (this->length == 0)
		return 0;

	Node* currentNode;
	int pos = this->ht.h(elem);
	int occurrences = 0;
	currentNode = this->ht.T[pos];
	while (currentNode != nullptr ) {
		if (currentNode->key == elem)
			occurrences++;
		currentNode = currentNode->next;
	}
	return occurrences;
} // Theta(alpha)



int SortedBag::size() const {
	return this->length;
} // Theta(1)


bool SortedBag::isEmpty() const {
	if (this->length == 0)
		return true;
	else
		return false;
} // Theta(1)


SortedBagIterator SortedBag::iterator() {
	return SortedBagIterator(*this);
} //Theta(1)


SortedBag::~SortedBag() {

	Node* currentNode, *deleteNode;

	for (int i = 0; i < this->ht.m; i++) {
		currentNode = this->ht.T[i];
		while (currentNode != nullptr) {
			deleteNode = currentNode;
			currentNode = currentNode->next;
			delete deleteNode;
		}
	}


	delete[] this->ht.T;
} // Theta(n+m)
