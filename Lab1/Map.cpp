#include "Map.h"
#include "MapIterator.h"
//throughout the comments, n is represented by the total number of pairs found in the dynamic array.
Map::Map() //Complexity theta(1)
{
	length = 0;
	maxCapacity = 1;
	mapArray = new TElem[1];
}

void Map::fixDimension() //Complexity theta(n)
{
	maxCapacity *= 2;
	TElem *temporaryMapArray = new TElem[maxCapacity];
	for (int i = 0; i < length; i++) {
		temporaryMapArray[i] = mapArray[i];
	}
	delete[]mapArray;
	mapArray = temporaryMapArray;
}
TValue Map::add(TKey c, TValue v) //Worst case = Theta(n) , Best Case = Theta(1) , Average = Theta(n) ==> complexity = O(n)
{
	if (maxCapacity == length) {
		fixDimension();
	}
	for (int i = 0; i < length; i++) {
		if (mapArray[i].first == c) {
			TValue oldValue = mapArray[i].second;
			mapArray[i].second = v;
			return oldValue;
		}
	}
	TElem newPair;
	newPair.first = c;
	newPair.second = v;
	mapArray[length++] = newPair;
	return NULL_TVALUE;
}

TValue Map::search(TKey c) const    //Worst case = Theta(n) , Best case = Theta(1), Average = Theta(n) ==> complexity = O(n)
{
	for (int i = 0; i < length; i++) {
		if (mapArray[i].first == c) {
			return mapArray[i].second;
		}
	}
	return NULL_TVALUE;
}

TValue Map::remove(TKey c)   //Worst case = Theta(n), Best Case = Theta(1), Average = Theta(n) ==> complexity = O(n)
{
	TValue oldValue = NULL_TVALUE;
	int i = 0;
	while (i < length && mapArray[i].first != c) {
		i++;
	}
	if (i<length){
		oldValue = mapArray[i].second;
		length--;
		for (int j = i ; j < length ; j++)
			mapArray[j] = mapArray[j + 1];
		
	}
	return oldValue;
}

int Map::size() const //Complexity theta(1)
{
	return length;
}

bool Map::isEmpty() const //Complexity theta(1)
{
	return length==0;
}

MapIterator Map::iterator() const //Complexity theta(1)
{
	return MapIterator(*this);
}

Map::~Map()		//Complexity theta(1)
{
	delete[] mapArray;
}
