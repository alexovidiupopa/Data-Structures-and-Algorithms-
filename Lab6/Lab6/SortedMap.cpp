#include "SortedMap.h"
#include "SMIterator.h"
#include <iostream>
#include <cmath>

//theta(1)
int SortedMap::hCode(TKey k)
{
	return abs(int(k));
}

//theta(1)
TKey SortedMap::h1(TKey k)
{
	return hCode(k) % this->capacity;
}

//theta(1)
TKey SortedMap::h2(TKey k)
{
	return 1+(hCode(k)%(this->capacity-1));
}

//theta(1)
int SortedMap::h(TKey k, int i)
{
	return (h1(k) + i * h2(k)) % this->capacity;
}

//theta(m), where m is the expanded capacity
void SortedMap::resize()
{
	int prime = firstPrimeGreaterThan(this->capacity * 2);
	TElem *aux = new TElem[prime];
	int oldCap = this->capacity;
	this->capacity = prime;
	for (int i = 0; i < prime; i++) {
		aux[i] = this->empty;
	}
	for (int i = 0; i < oldCap; i++) {
		TElem e = this->hashTable[i];
		int j = 0;
		int pos = h(e.first, j);
		while (j < this->capacity && aux[pos] != this->empty) {
			if (aux[pos].first == e.first)
				break;
			j++;
			pos = h(e.first, j);
		}
		aux[pos] = e;
	}
	delete[]this->hashTable;
	this->hashTable = aux;
}
//theta(1)
int SortedMap::firstPrimeGreaterThan(int x)
{
	x++;
	while (!prim(x))
		x++;
	return x;
}
//O(sqrt(x))
bool SortedMap::prim(int x)
{
	if (x < 2 || x>2 && x % 2 == 0)
		return false;
	for (int d = 3; d*d <= x; d += 2)
		if (x%d == 0)
			return false;
	return true;
}
SortedMap::SortedMap(Relation r)
{
	this->r = r;
	this->capacity = max_capacity;
	this->length = 0;
	this->empty = std::make_pair(-999999, -999999);
	this->deleted = std::make_pair(-999998, -999998);
	this->hashTable = new TElem[max_capacity];
	for (int i = 0; i < max_capacity; i++) {
		this->hashTable[i] = this->empty;
	}
}

//BC=AC=Theta(1), WC=Theta(capacity) => O(capacity) overall 
TValue SortedMap::add(TKey c, TValue v)
{
	if (this->length == this->capacity) {
		resize();
	}
	int i = 0;
	int pos = h(c, i);
	while (i < this->capacity && this->hashTable[pos] != this->empty && this->hashTable[pos]!=this->deleted ) {
		if (this->hashTable[pos].first == c)
			break;
		i++;		
		pos = h(c, i);
		}
	TValue old = this->hashTable[pos].second;
	TElem newValue = std::make_pair(c, v);
	if (old == this->empty.second || old == this->deleted.second) {
		this->length++;
		this->hashTable[pos] = newValue;
		return NULL_TVALUE;
	}
	else {
		this->hashTable[pos] = newValue;
		return old;
	}
}

//BC=AC=Theta(1), WC=Theta(capacity) => O(capacity) overall 
TValue SortedMap::search(TKey c) 
{
	int i = 0;
	int pos = h(c, i);
	while(i<this->capacity && this->hashTable[pos].first!=c && this->hashTable[pos]!=this->empty){
		i++;
		pos = h(c, i);
	}
	if (i == this->capacity || this->hashTable[pos] == this->empty)
		return NULL_TVALUE;
	return this->hashTable[pos].second;
}

//BC=AC=Theta(1), WC=Theta(capacity) => O(capacity) overall 
TValue SortedMap::remove(TKey c)
{
	int i = 0;
	int pos = h(c, i);
	while (i < this->capacity && this->hashTable[pos].first != c && this->hashTable[pos] != this->empty) {
		i++;
		pos = h(c, i);
	}
	if (i == this->capacity || this->hashTable[pos]==this->empty)
		return NULL_TVALUE;
	this->length--;
	TValue toReturn = this->hashTable[pos].second;
	this->hashTable[pos] = this->deleted;
	return toReturn;
}

//theta(1)
int SortedMap::size() const
{
	return this->length;
}

//theta(1)
bool SortedMap::isEmpty() const
{
	return this->length==0;
}

//O(size^2)
SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}

//theta(1)
SortedMap::~SortedMap()
{
	delete[]this->hashTable;
}
