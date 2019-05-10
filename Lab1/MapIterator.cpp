#include "MapIterator.h"
#include <exception>

MapIterator::MapIterator(const Map &map) : map(map) { //Complexity theta(1)
	currentIndex = 0;
}
TElem MapIterator::getCurrent() const //Complexity theta(1)
{
	if (valid()) {
		return map.mapArray[currentIndex];
	}
	else {
		throw std::exception(); 
	}
	
}

bool MapIterator::valid() const //Complexity theta(1)
{
	return currentIndex < map.length;
}

void MapIterator::next() //Complexity theta(1)
{
	if (valid()) {
		currentIndex++;
	}
	else {
		throw std::exception();
	}
}

void MapIterator::first() //Complexity theta(1)
{
	currentIndex = 0;
}
