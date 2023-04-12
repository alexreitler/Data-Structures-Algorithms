#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

unsigned int defaultHash(TKey key) {
    return (unsigned int)key;
}

void SortedMap::resize() {
    auto oldHT = ht;

    ht.capacity *= 2;
    ht.array = new Node * [ht.capacity]{};
    length = 0;

    for (int i = 0; i < oldHT.capacity; ++i) {
        auto node = oldHT.array[i];

        while (node != nullptr) {
            add(node->info.first, node->info.second);
            node = node->next;
        }
    }

}
//comp. O(capacity)

SortedMap::SortedMap(Relation r) : rel{ r }, length{ 0 }, ht{ defaultHash, 8, new Node * [8]{} } {}


//returns a pointer to the array element corresponding to the key's hash value
Node** SortedMap::getSlot(TKey key) const {
    auto index = ht.hash(key) % ht.capacity;
    return &ht.array[index];
}
//comp O(1)



TValue SortedMap::add(TKey k, TValue v) {
    double loadFactor = (double)length / (double)ht.capacity;

    if (loadFactor >= 0.7)
        resize();

    auto slot = getSlot(k);

    if (*slot == nullptr) {
        *slot = new Node{ {k, v}, nullptr };
        ++length;
        return NULL_TVALUE;
    }

    while (*slot != nullptr && (*slot)->info.first != k && rel((*slot)->info.first, k) == true)
        slot = &((*slot)->next);

    if (*slot != nullptr) {
        if ((*slot)->info.first == k) {             //we found an element with the same key
            auto oldValue = (*slot)->info.second;
            (*slot)->info.second = v;

            return oldValue;
        }
        else {                                      //we add according to relation
            auto newInfo = (*slot)->info;
            (*slot)->info = { k, v };
            (*slot)->next = new Node{ newInfo, (*slot)->next };

            ++length;
            return NULL_TVALUE;
        }
    }
    else {
        *slot = new Node{ {k, v}, nullptr };
        ++length;

        return NULL_TVALUE;
    }
}
//Best case O(1)
//Worst case O(capacity)

TValue SortedMap::search(TKey k) const {

    auto slot = getSlot(k);

    while (*slot != nullptr && (*slot)->info.first != k)
        slot = &((*slot)->next);

    if (*slot != nullptr)
        return (*slot)->info.second;

    return NULL_TVALUE;
}
//Best case O(1)
//Worst case O(capacity)

TValue SortedMap::remove(TKey k) {
    auto slot = getSlot(k);

    if (*slot == nullptr)
        return NULL_TVALUE;

    if ((*slot)->info.first == k) {
        auto value = (*slot)->info.second;
        auto oldNode = *slot;

        *slot = (*slot)->next;

        delete oldNode;

        --length;
        return value;
    }

    auto next = &((*slot)->next);

    while (*next != nullptr && (*next)->info.first != k) {
        slot = next;
        next = &((*slot)->next);
    }

    if (*next != nullptr) {
        (*slot)->next = (*next)->next;
        auto value = (*next)->info.second;

        delete next;
        --length;
        return value;
    }

    return NULL_TVALUE;
}
//Best case O(1)
//Worst case O(capacity)


void SortedMap::replace(TKey k, TValue oldValue, TValue newValue) {

    auto slot = getSlot(k);

    if (*slot != nullptr) {

        while (*slot != nullptr && (*slot)->info.first != k && rel((*slot)->info.first, k) == true)
            slot = &((*slot)->next);

        if (*slot != nullptr) {
            if ((*slot)->info.first == k) {             //we found an element with the same key
                auto currentValue = (*slot)->info.second;
                if (currentValue == oldValue) {
                    (*slot)->info.second = newValue;
                }

            }
        }
    }
}
//Best case O(1)
//Worst case O(capacity)


int SortedMap::size() const {
	//TODO - Implementation
    return (int)length;
}

bool SortedMap::isEmpty() const {
    return (length == 0);
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    for (int i = 0; i < ht.capacity; ++i) {
        auto currentNode = ht.array[i];

        while (currentNode != nullptr) {
            auto oldNode = currentNode;
            currentNode = currentNode->next;
            delete oldNode;
        }
    }
    delete[] ht.array;
    ht = {};
}
