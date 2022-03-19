#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	IndexedList& list;
    int currentElementPos;
		
    ListIterator(IndexedList& lista);
public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
    //removes and returns the current element from the iterator
    //after the operation the current element from the Iterator is the next element from the List, or, if the removed element was the last one, the iterator is invalid
    //throws exception if the iterator is invalid
    TElem remove();

};

