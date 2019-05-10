#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <stdexcept>

// SortedBagIterator constructor.
// Complexity Theta(1).
SMMIterator::SMMIterator(const SortedMultiMap& c) : c(c) {
	dllKeys = c.dllKeys;
	currentKey = c.dllKeys->head;
	if (currentKey != NULL)
		currentValue = currentKey->values->head;
}

// Method for resetting the iterator to the first element of the bag.
// Complexity Theta(1).
void SMMIterator::first() {
	currentKey = c.dllKeys->head;
	if (currentKey != NULL)
		currentValue = currentKey->values->head;
}

// Method for advancing the iterator to the next element of the bag.
// Complexity Theta(1).
void SMMIterator::next() {
	if (!valid()) {
		throw exception();
	}
	if (currentValue->next != NULL) {
		currentValue = currentValue->next;
	}
	else {
		currentKey = currentKey->next;
		if (currentKey != NULL) {
			currentValue = currentKey->values->head;
		}
	}
}

// Method for checking if the validator is valid.
// Complexity Theta(1).
bool SMMIterator::valid() const {
	return currentKey != NULL;
}

// Method for retrieving the current element from the iterator's position.
//Complexity Theta(1).
TElem SMMIterator::getCurrent() const {
	if (!valid()) {
		throw exception();
	}
	return TElem(currentKey->key, currentValue->value);
}
