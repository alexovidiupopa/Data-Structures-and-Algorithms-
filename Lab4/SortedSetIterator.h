#pragma once
#include "SortedSet.h"

//unidirectional iterator for a container
class SortedSet;

class SortedSetIterator {
	friend class SortedSet;
private:

	SortedSetIterator(const SortedSet& s);

	//contains a reference of the container it iterates over

	const SortedSet& s;



	/* representation specific for the iterator*/

	DLLA list;
	int currentElement;

public:



	//sets the iterator to the first element of the container

	void first();

	void previous();

	//moves the iterator to the next element

	//throws exception if the iterator is not valid

	void next();



	//checks if the iterator is valid

	bool valid() const;



	//returns the value of the current element from the iterator

	// throws exception if the iterator is not valid

	TElem getCurrent() const;



};



