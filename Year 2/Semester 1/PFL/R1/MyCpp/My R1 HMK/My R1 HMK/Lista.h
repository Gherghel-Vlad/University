#pragma once

typedef int TElem;

typedef struct Node {
	TElem value;
	Node* next;
};

class List
{
private:
	Node* firstNode;

	Node* createEmptyNode();
	void addNewNodeAtTheEndRec(Node** node, TElem value);
	void printListRec(Node* node);
	void destroyListRec(Node* n);

	bool hasEvenNrOfElementsRec(Node* n);


	void deleteOccurencesOfElementRec(Node** prevNode, Node** currentNode, TElem elem);

public:

	List();

	Node* getFirstNode();

	Node** getFirstNodeAsReference();

	void setFirstNode(Node* n);
	
	void addNewNodeAtTheEnd(TElem value);

	void destroyList();

	void printList();
	
	void deleteFirst();

	bool hasEvenNrOfElements();

	void deleteOccurencesOfElement(TElem elem);

	List deepCopy();
	void deepCopyRec(List* l, const Node* n);

};


