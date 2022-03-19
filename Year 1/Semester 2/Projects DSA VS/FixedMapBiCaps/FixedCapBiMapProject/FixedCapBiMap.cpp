#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
FixedCapBiMap::FixedCapBiMap(int capacity) {

    if (capacity <= 0){
        throw -1;
    }

    this->capacity = capacity;
    this->nrPairs = 0;
    this->elements = new TElem[capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
}

ValuePair FixedCapBiMap::removeKey(TKey k){
    int index=0;
    int count=0;
    int i;
    ValuePair vl;
    vl.first = NULL_TVALUE;
    vl.second = NULL_TVALUE;

    while(count<2 && index < this->nrPairs){
        if(this->elements[index].first == k){
            if(count == 0){
                vl.first = this->elements[index].second;
            }
            else{
                vl.second = this->elements[index].second;
            }
            count++;

            // removing the element
            this->elements[index] = this->elements[this->nrPairs-1];
            this->nrPairs--;
        }
        else
            index++;
    }

    return vl;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if(this->capacity == this->nrPairs){
	    throw -1;
	}

	int index=0;
	int count=0;
	while(count<2 && index <this->nrPairs){
	    if(this->elements[index].first == c){
	        count++;
	    }
	    index++;
	}
	if(count == 2){
	    return false;
	}
	else{
        this->elements[this->nrPairs].first = c;
        this->elements[this->nrPairs].second = v;
        this->nrPairs++;
        return true;
    }


	return false;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	return std::pair<TValue, TValue>(NULL_TVALUE, NULL_TVALUE);
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	return false;
}


int FixedCapBiMap::size() const {
	return this->nrPairs;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return false;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return false;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



