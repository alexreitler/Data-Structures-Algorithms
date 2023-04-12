#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0){
        throw exception();
    }
    this->capacity = capacity;
    this->nrElements = 0;
    this->elements = new TElem[capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->capacity==this->nrElements){
        throw exception();
    }
    int index= 0;
    int count = 0;
    while(count < 2 && index < this->nrElements){
        if(this->elements[index].first == c) count++;
        index++;
    }
    if(count == 2){
        return false;
    }
    else{
        this->elements[this->nrElements].first = c;
        this->elements[this->nrElements].second = v;
        this->nrElements++;
        return true;
    }
	return false;
}

ValuePair FixedCapBiMap::search(TKey c) const{
    ValuePair returnedValue;
    returnedValue.first = NULL_TVALUE;
    returnedValue.second = NULL_TVALUE;
    int index= 0;
    int count = 0;
    while(count < 2 && index < this->nrElements){
        if(this->elements[index].first == c){
            if(count == 0) returnedValue.first = this->elements[index].second;
            if(count == 1) returnedValue.second = this->elements[index].second;
            count++;
        }
        index++;
    }
	return returnedValue;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
    bool found = false;
    while(index < this->nrElements && !found){
        if (this->elements[index].first == c && this->elements[index].second == v){
            found = true;
        }
        else{
            index++;
        }
    }
    if(!found){
        return false;
    }
    else{
        this->elements[index] = this->elements[this->nrElements-1];
        this->nrElements--;
        return true;
    }
	return false;
}


int FixedCapBiMap::size() const {
	return this->nrElements;
	return 0;
}

bool FixedCapBiMap::isEmpty() const{
    if(this->nrElements == 0) return true;
	return false;
}

bool FixedCapBiMap::isFull() const {
    if(this->nrElements==this->capacity) return true;
	return false;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



