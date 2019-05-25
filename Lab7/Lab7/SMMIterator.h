#pragma once
#include "SortedMultiMap.h"
#include <stack>

class SortedMultiMap;

class SMMIterator
{
	friend class SortedMultiMap;
private: 
	SMMIterator(const SortedMultiMap &smm);
	const SortedMultiMap& smm;
	int currentNode;
	std::stack<int> stack;
	

public:

	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};

