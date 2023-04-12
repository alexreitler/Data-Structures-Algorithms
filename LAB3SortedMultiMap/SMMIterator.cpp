#include "SMMIterator.h"
#include "SortedMultiMap.h"
///theta (1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    this->current = map.head;
    if(this->current!=-1)
    this->current2 = map.elems[this->current].head;
}

///theta (1)
void SMMIterator::first(){
    this->current= map.head;
    this->current2 = map.elems[this->current].head;
}

///theta (1)
void SMMIterator::next(){
    if(this->current== -1) {
        exception ex;
        throw exception();

    }
    if(map.elems[this->current].values[current2].next ==-1) {
        this->current = map.elems[this->current].next;
        if(this->current!=-1)
        this->current2 = map.elems[this->current].head;
    }
    else
        this->current2=map.elems[this->current].values[this->current2].next;
}


///theta (1)
bool SMMIterator::valid() const{
	return this->current!=-1;
}


///theta (1)
TElem SMMIterator::getCurrent() const{
    if(this->current== -1) {
        exception ex;
        throw exception();

    }
	return make_pair(map.elems[this->current].key, map.elems[this->current].values[0].val);

}



//Best Case Theta(1)
//Worst Case O(steps)
//Average Case O(steps)
void SMMIterator::jumpForward(int k) {
    if (this->current == -1 || k<1) {
        exception ex;
        throw exception();

    }
    while (k) {
        if (map.elems[this->current].values[current2].next == -1) {
            this->current = map.elems[this->current].next;
            if (this->current != -1) {
                this->current2 = map.elems[this->current].head;
            }
            else
                break;
        }
        else
            this->current2 = map.elems[this->current].values[this->current2].next;
        k--;
    }
}

