#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>
#include <vector>
#include <exception>
using namespace std;


///Theta (1)
void KeyNode::addVal(TValue v) {
    if (this->length >= this->capacity)
        this->resize();

    if (this->head == -1)
    {
        this->values[0].val = v;
        this->values[0].next = -1;
        this->keyFree = 1;
        this->head = 0;
        this->length = 1;
        this->tail = 0;
    }
    else
    {
        int newNode = this->keyFree;
        this->keyFree = this->values[this->keyFree].next;
        this->values[this->tail].next = newNode;
        this->values[newNode].val = v;
        this->values[newNode].next = -1;
        this->length++;
        this->tail = newNode;

    }
}
///O(2*capacity)
void KeyNode::resize() {
    auto* els = new ValueNode[this->capacity * 2];

    for (int i = 0; i < this->length; i++)
        els[i] = this->values[i];

    for (int j = this->capacity; j < this->capacity * 2 - 1; j++)
        els[j].next = j + 1;

    this->keyFree = this->capacity;
    this->capacity *= 2;
    els[this->capacity - 1].next = -1;
    delete[] this->values;
    this->values = els;
}


///Best case: Theta(1)
///worst case: O(capacity)
///average: O(capacity)
void KeyNode::removeVal(TValue v) {
    if (this->length == 0)
        throw exception();
    else {
        int current = this->head;
        if (this->values[current].val == v)
        {
            this->head = this->values[current].next;
            this->values[current].next = this->keyFree;
            this->keyFree = current;
            this->length--;
        }
        else {
            while (this->values[current].next != -1 && this->values[this->values[current].next].val != v)
                current = this->values[current].next;
            if (this->values[this->values[current].next].val == v) {
                int newnext = this->values[current].next;
                this->values[current].next = this->values[this->values[current].next].next;
                this->values[newnext].next = this->keyFree;
                this->keyFree = newnext;
                this->length--;
            }
        }

    }

}

///O(capacity)
KeyNode::KeyNode(const KeyNode& smm) {
    this->capacity = smm.capacity;
    this->length = smm.length;
    this->head = smm.head;
    this->keyFree = smm.keyFree;
    this->tail = smm.tail;
    delete[] this->values;
    this->values = new ValueNode[this->capacity * 2];
    for (int i = 0; i < this->capacity - 1; i++)
        this->values[i] = smm.values[i];

}

///O(capacity)
KeyNode& KeyNode::operator=(const KeyNode& smm) {
    if (this == &smm)
        return *this;
    this->capacity = smm.capacity;
    this->length = smm.length;
    this->head = smm.head;
    this->keyFree = smm.keyFree;
    this->tail = smm.tail;
    delete[] this->values;
    this->values = new ValueNode[this->capacity * 2];
    for (int i = 0; i < this->capacity - 1; i++)
        this->values[i] = smm.values[i];
    return *this;

}
///Theta(1)
KeyNode::~KeyNode() {
    delete[] this->values;

}

///O(capacity)
KeyNode::KeyNode() {
    this->head = -1;
    this->length = 0;
    this->capacity = 10;
    this->keyFree = 0;
    this->tail = 0;

    this->values = new ValueNode[this->capacity];
    for (int i = 0; i < this->capacity - 1; i++)
        this->values[i].next = i + 1;
    this->values[this->capacity - 1].next = -1;




}


/// O(capacity)
SortedMultiMap::SortedMultiMap(Relation r) {
    this->r=r;
    this->capacity = 10000;
    this->length = 0;
    this->head = -1;
    this->firstFree = 0;
    this->elems= new KeyNode[this->capacity];
    for (int i=0; i<this->capacity-1;i++)
        this->elems[i].next=i+1;
    this->elems[this->capacity-1].next=-1;
}




///Best case: Theta(1)
///worst case: O(capacity)
///average: O(capacity)
void SortedMultiMap::add(TKey c, TValue v) {
    if(this->length >= this->capacity)
        resize();
    TKey current = this->head;
    //when empty
    if(this->head ==-1){
        this->head = 0;
        this->firstFree = 1;
        this->elems[0].key= c;
        this->elems[0].next= -1;
        this->length = 1;
        this->elems[0].addVal(v);
    }
    //when first and key exists
    else if (this->elems[current].key == c)
    {
        this->elems[current].addVal(v);
        //this->length++;
        return;
    }
    //when first after relation
    else if(!r(this->elems[current].key,c)){
        int newnode = this->firstFree;
        this->firstFree =this->elems[this->firstFree].next;
        this->elems[newnode].key = c;
        this->elems[newnode].next = this->head;
        this->head = newnode;
        this->elems[newnode].addVal(v);
        this->length++;
    }
    else{
        //do until relation is false
        while( this->elems[current].next != -1 && r(this->elems[this->elems[current].next].key,c)){
            current=this->elems[current].next;
            //if we found the key
            if(this->elems[current].key==c)
            {
                this->elems[current].addVal(v);
                //this->length++;
                return;
            }
        }
        //if key not found, we add it
        int newnode = this->firstFree;
        this->firstFree =this->elems[this->firstFree].next;
        this->elems[newnode].key=c;
        this->elems[newnode].next= this->elems[current].next;
        this->elems[current].next=newnode;
        this->length++;
        this->elems[newnode].addVal(v);

    }



}
///Best case: Theta(1)
///worst case: O(length)
///average: O(length)
vector<TValue> SortedMultiMap::search(TKey c) const {
    TKey current = this->head;
    std::vector<TValue> search_requirement;

    while(this->elems[current].key != c && current != -1){
        current = this->elems[current].next;
    }
    if(current != -1){
    int current2= this->elems[current].head;
    while(current2 !=-1){
        search_requirement.push_back(this->elems[current].values[current2].val);
        current2=this->elems[current].values[current2].next;
    }
        }
    return search_requirement;

}
///Best case: Theta(1)
///worst case: O(length)
///average: O(length)
bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = this->head;
    if(this->length ==0)
        return false;
    while( this->elems[current].key != c && current !=-1)
        current = this->elems[current].next;
    if (current == -1)
        return false;
    int l_teste = this->elems[current].length;
    this->elems[current].removeVal(v);
    if( this->elems[current].length == l_teste)
        return false;
    else if ( this->elems[current].length!=0)
        return true;
    else
    {
        if(current == this->head)
        {
          this->head = this->elems[current].next;
          this->elems[current].next=this->firstFree;
          this->firstFree = current;
        }
        else
        {
            int current2= this->head;
            while(this->elems[current2].next != current)
                current2 = this->elems[current2].next;
            this->elems[current2].next = this->elems[current].next;
            this->elems[current].next=this->firstFree;
            this->firstFree = current;

        }
        this->length--;
        return true;
    }

}

///Best case: Theta(1)
///worst case: O(length)
///average: O(length)
int SortedMultiMap::size() const {

    int l=0;
    TKey current = this->head;

    while( current != -1)
    {
        l+=this->elems[current].length;
        current=this->elems[current].next;
    }
    return l;


}
///Theta(1)
bool SortedMultiMap::isEmpty() const {
	if(this->length==0)
        return true;
	return false;
}
///Theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
///Theta(1)
SortedMultiMap::~SortedMultiMap() {
	delete[] this->elems;
}

/// O(2*capacity)
void SortedMultiMap::resize() {
    auto *els = new KeyNode[this->capacity*2];
    for( int i=0; i<this->length; i++)
        els[i] = this->elems[i];
    this->firstFree = this->length;
    els[this->firstFree].next = this->length+1;

    for( int j= this->length+1; j< this->capacity*2-1; j++)
        els[j].next= j + 1;

    els[this->capacity*2-1].next = -1;
    this->capacity*=2;


    delete[] this->elems;
    this->elems= els;
}

///O(capacity)
SortedMultiMap::SortedMultiMap(const SortedMultiMap &smm) {
    this->r=smm.r;
    this->capacity = smm.capacity;
    this->length = smm.length;
    this->head = smm.head;
    this->firstFree = smm.firstFree;
    delete[] this->elems;
    this->elems= new KeyNode[this->capacity];
    for (int i=0; i<this->capacity-1;i++)
        this->elems[i]=smm.elems[i];

}

///O(capacity)
SortedMultiMap &SortedMultiMap::operator=(const SortedMultiMap &smm) {
    if(this==&smm)
        return *this;
    this->r=smm.r;
    this->capacity = smm.capacity;
    this->length = smm.length;
    this->head = smm.head;
    this->firstFree = smm.firstFree;
    delete[] this->elems;
    this->elems= new KeyNode[this->capacity];
    for (int i=0; i<this->capacity-1;i++)
        this->elems[i]=smm.elems[i];

    return *this;
}




