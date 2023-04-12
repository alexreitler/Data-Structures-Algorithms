#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
    friend class KeyNode;
    friend class ValueNode;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
    int current;
    int current2;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;

	//extra 
	void jumpForward(int k);
};
