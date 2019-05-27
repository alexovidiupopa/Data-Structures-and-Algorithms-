#pragma once

#include <vector>

typedef int TKey;

typedef int TValue;

#define cap 10
#define null -9999999
#define nullValue std::make_pair(-9999999,-9999999)
#include <utility>

typedef std::pair<TKey, TValue> TElem;

using namespace std;

typedef struct BSTNode {
	TElem info;
	int left, right;
	
};

typedef struct BST {
	BSTNode *nodes;
	int capacity, root, size,firstEmpty;
};

typedef bool(*Relation)(TKey, TKey);

class SMMIterator;
class SortedMultiMap
{
	friend class SMMIterator;

private: 
	Relation r;
	BST bst;
	
	void resize();

	void recomputeFirstEmpty();

	int insert_rec(int node, TElem e);

	int minimum(int node);

	int remove_rec(int node, TElem e,bool &found);


public:

	vector<TValue> removeKey(TKey key);

	SortedMultiMap(Relation r);

	void add(TKey c, TValue v);

	//returns the values belonging to a given key

	vector<TValue> search(TKey c) ;



	//removes a key value pair from the sorted multimap

	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed

	bool remove(TKey c, TValue v);



	//returns the number of key-value pairs from the sorted multimap

	int size() const;



	//verifies if the sorted multi map is empty

	bool isEmpty() const;



	// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	

	SMMIterator iterator() const;

	~SortedMultiMap();
};

