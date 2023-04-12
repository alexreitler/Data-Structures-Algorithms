#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

void swap(Node** a, Node** b) {
    auto t = *a;
    *a = *b;
    *b = t;
}

int partition(Node* arr[], int low, int high, Relation rel) {
    int pivot = arr[high]->info.first;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (rel(arr[j]->info.first, pivot) == true) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Node* arr[], int low, int high, Relation rel) {
    if (low < high) {
        int pi = partition(arr, low, high, rel);

        quickSort(arr, low, pi - 1, rel);
        quickSort(arr, pi + 1, high, rel);
    }
}

SMIterator::SMIterator(const SortedMap& map) : map{ map } {
    nodesLists = new Node * [map.ht.capacity];
    listsCount = 0;

    for (unsigned int i = 0; i < map.ht.capacity; ++i) {
        auto node = map.ht.array[i];

        if (node != nullptr)
            nodesLists[listsCount++] = node;
    }

    quickSort(nodesLists, 0, listsCount - 1, map.rel);

    currentListIndex = 0;
    if (listsCount != 0)
        currentNode = nodesLists[currentListIndex];
    else
        currentNode = nullptr;
}

void SMIterator::first(){
	//TODO - Implementation
    currentListIndex = 0;
    currentNode = nodesLists[currentListIndex];
}

void SMIterator::next(){
	//TODO - Implementation
    if(!valid())
        throw std::exception();

    currentNode = currentNode->next;

    if (currentNode == nullptr && currentListIndex < listsCount - 1) {
        ++currentListIndex;
        currentNode = nodesLists[currentListIndex];
    }
}

bool SMIterator::valid() const{

    if (currentListIndex >= listsCount || currentNode == nullptr)
        return false;
    return true;
}

TElem SMIterator::getCurrent() const{

    if (!valid())
        throw std::exception();
    return currentNode->info;
	//TODO - Implementation
	return NULL_TPAIR;
}


