#include "SMIterator.h"
#include <exception>
#include <algorithm>

//O(size^2)
SMIterator::SMIterator(const SortedMap &_sm):sm(_sm){
	this->index = 0;
	this->length = _sm.length;
	this->array = new TElem[this->length];
	this->k = 0;
	for (int i = 0; i < _sm.capacity; i++) {
		if (_sm.hashTable[i] != _sm.deleted && _sm.hashTable[i] != _sm.empty) {
			this->array[this->k++] = _sm.hashTable[i];
		}
	}
	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (!_sm.r(this->array[i].first, this->array[j].first)) {
				TElem aux;
				aux = this->array[i];
				this->array[i] = this->array[j];
				this->array[j] = aux;
			}
		}
	}
	
}

//theta(1)
void SMIterator::first()
{
	this->index = 0;
}

//theta(1)
void SMIterator::next()
{
	if (!valid())
		throw std::exception();
	this->index++;
}

//theta(1)
bool SMIterator::valid() const
{
	return this->index < this->length;
}

//theta(1)
TElem SMIterator::getCurrent() const
{
	if (!valid())
		throw std::exception();
	return this->array[this->index];
}
