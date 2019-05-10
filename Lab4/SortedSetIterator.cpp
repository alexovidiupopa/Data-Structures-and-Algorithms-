#include "SortedSetIterator.h"
#include <exception>

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& s) :s(s) {
	this->list = s.dlla;
	this->currentElement = s.dlla.head;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
void SortedSetIterator::first()
{
	this->currentElement = s.dlla.head;
}

void SortedSetIterator::previous()
{
	if (!valid()) {
		std::exception();
	}
	else {
		if (this->currentElement == s.dlla.head) {
			this->currentElement = -1;
		}
		else {
			this->currentElement = this->list.nodes[this->currentElement].prev;
		}
	}
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
void SortedSetIterator::next()
{
	if (!valid()) {
		throw std::exception();
	}
	this->currentElement = this->list.nodes[this->currentElement].next;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
bool SortedSetIterator::valid() const
{
	return this->currentElement != -1;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
TElem SortedSetIterator::getCurrent() const
{
	if (!valid()) {
		throw std::exception();
	}
	return this->list.nodes[this->currentElement].info;
}
