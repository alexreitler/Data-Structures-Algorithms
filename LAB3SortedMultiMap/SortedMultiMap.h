#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class ValueNode {
public:
    TValue val;
    int next;
};

class KeyNode {
private:
    void resize();
public:
    TKey key;
    int next;
    ValueNode* values;
    int head;
    int length;
    int capacity;
    int keyFree;
    int tail;
    void addVal(TValue v);
    void removeVal(TValue v);


    KeyNode(const KeyNode& smm);

    KeyNode& operator=(const KeyNode& smm);

    ~KeyNode();

    // constructor
    KeyNode();
};


class SortedMultiMap {
	friend class SMMIterator;
    private:
        KeyNode *elems;
        Relation r;
        int length;
        int capacity;
        int head;
        int firstFree;
        void resize();


    public:

    SortedMultiMap(const SortedMultiMap &smm);

    SortedMultiMap & operator=(const SortedMultiMap &smm);


    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

};
