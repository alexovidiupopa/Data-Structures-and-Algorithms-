#pragma once
#define cap 10
typedef int TElem;

typedef TElem TComp;

struct node {
	TElem info;
	int next, prev;
};

struct DLLA {
	node* nodes;
	int capacity, head, tail, firstEmpty,size;
};

typedef bool(*Relation)(TComp, TComp);

class SortedSetIterator;

class SortedSet {
	friend class SortedSetIterator;
private:

	/*Representation of the SortedSet*/
	DLLA dlla;
	Relation relation;

	void insertPosition(TComp e, int pos);

	void resize();

	int allocate();
	
	void free(int poz);


public:

	//constructor

	SortedSet(Relation r);



	//adds an element to the sorted set

	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 

	//it returns false

	bool add(TComp e);





	//removes an element from the sorted set

	//if the element was removed, it returns true, otherwise false

	bool remove(TComp e);



	//checks if an element is in the sorted set

	bool search(TElem elem) const;





	//returns the number of elements from the sorted set

	int size() const;



	//checks if the sorted set is empty

	bool isEmpty() const;



	//returns an iterator for the sorted set

	SortedSetIterator iterator() const;



	// destructor

	~SortedSet();


};