#pragma once

#include <vector>



typedef int TKey;

typedef int TValue;



#include <utility>

typedef std::pair<TKey, TValue> TElem;



using namespace std;



typedef bool(*Relation)(TKey, TKey);

#include <stdexcept>

struct ValueNode {
	ValueNode* prev;
	ValueNode* next;
	TValue value;
};

struct DLLValues {
	ValueNode* head;
	ValueNode* tail;
};

struct KeyNode {
	KeyNode* prev;
	KeyNode* next;
	TKey key;
	DLLValues* values;
};

struct DLLKeys {
	KeyNode* head;
	KeyNode* tail;
};

class SMMIterator;

class SortedMultiMap {

	friend class SMMIterator;

private:

	/* representation of the SortedMultiMap */
	DLLKeys* dllKeys;
	Relation relation;

	void deleteKeyElement(TKey key);

	bool deleteValueElement(DLLValues* dllValues, TValue value);

public:



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

	TKey difference();

	// destructor

	~SortedMultiMap();

};
