#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <iostream>
//implementation of the operations from SortedMultiMap.h

// SortedMultiMap constructor- complexity theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
	dllKeys = new DLLKeys();
	dllKeys->head = NULL;
	dllKeys->tail = NULL;
	relation = r;
}

// Method for adding a new key value pair to the sorted multi map.
// The complexity of the add method is O(n), because WC=AC=Theta(n) != BC = Theta(1).
void SortedMultiMap::add(TKey c, TValue v) {
	KeyNode* current = dllKeys->head;

	while (current != dllKeys->tail && (relation(current->key, c) && current->key != c)) {
		current = current->next;
	}
	//if no elements exist in the dll
	if (current == NULL) {
		KeyNode* newNode = new KeyNode();
		newNode->key = c;
		DLLValues* dv = new DLLValues();
		ValueNode *valuenode = new ValueNode();
		valuenode->value = v;
		dv->head = valuenode;
		dv->head->next = NULL;
		dv->head->prev = NULL;
		dv->tail = dv->head;
		newNode->values = dv;
		//newNode->next = NULL;
		//newNode->prev = dllKeys->tail;
		dllKeys->head = newNode;
		dllKeys->tail = newNode;
		
		return;
	}
	
	if (current->key == c) { // if the current key already exists, we just the passed value to the corresponding dll
		ValueNode *newNode = new ValueNode();
		newNode->value = v;
		newNode->next = NULL;
		newNode->prev = current->values->tail;
		if (current->values->head == NULL)
		{
			current->values->head = newNode;
			current->values->tail = newNode;
		}
		else
		{
			current->values->tail->next = newNode;
			current->values->tail = newNode;
		}

	}
	else {
		//create a new node
		KeyNode* newNode = new KeyNode();
		newNode->key = c;
		DLLValues* dv = new DLLValues();
		ValueNode *valuenode = new ValueNode();
		valuenode->value = v;
		dv->head = valuenode;
		dv->head->next = NULL;
		dv->head->prev = NULL;
		dv->tail = dv->head;
		newNode->values = dv;
		
		if (current == dllKeys->head && !relation(current->key, c)) {// if it needs to be inserted at the beginning
			dllKeys->head = newNode;
			newNode->prev = NULL;
			newNode->next = current;
			current->prev = newNode;
			return;
		}
		if (current == dllKeys->tail&&relation(current->key, c)) { //if it needs to be inserted at the end

			dllKeys->tail = newNode;
			newNode->next = NULL;
			newNode->prev = current;
			current->next = newNode;
			return;

		}//else insert it at its position
		newNode->prev = current->prev;
		newNode->next = current;
		current->prev = newNode;
		current->prev->next = newNode;
	}
}

void SortedMultiMap::deleteKeyElement(TKey key) { // auxiliary function used for deleting an element with a key, complexity O(n)
	KeyNode* currentNode = dllKeys->head;
	while (currentNode != dllKeys->tail && currentNode->key != key) {
		currentNode = currentNode->next;
	}
	if (currentNode != NULL) {
		if (currentNode == dllKeys->head)
			dllKeys->head = currentNode->next;
		if (currentNode == dllKeys->tail)
			dllKeys->tail = currentNode->prev;

		if (currentNode->next != NULL)
			currentNode->next->prev = currentNode->prev;
		if (currentNode->prev != NULL)
			currentNode->prev->next = currentNode->next;

		delete currentNode;
	}
}


bool SortedMultiMap::deleteValueElement(DLLValues* dllValues, TValue value) { // auxiliary function used for deleting a value associated to a key, complexity O(n)
	ValueNode* currentNode = dllValues->head;
	while (currentNode != NULL) {
		if (currentNode->value == value)
		{
			if (currentNode == dllValues->head)
			{
				dllValues->head = currentNode->next;
				
			}
			if (currentNode == dllValues->tail)
			{
				dllValues->tail = currentNode->prev;
				
			}
			if (currentNode->prev!=NULL)
				currentNode->prev->next = currentNode->next;
			if (currentNode->next != NULL)
				currentNode->next->prev = currentNode->prev;
			delete currentNode;
			return true;
		}
		currentNode = currentNode->next;
	}
	
	return false;
}

//Search method.
//BC = Theta(m), where m = number of elements associated to the key we look for 
//WC=AC= Theta(n*m)
//=> overall = O(n*m)
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> v;
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		if (keyNode->key == c) {
			ValueNode* valueNode = keyNode->values->head;
			while (valueNode != NULL) {
				v.push_back(valueNode->value);
				valueNode = valueNode->next;
			}
			return v;
		}
		keyNode = keyNode->next;
	}
	return v;
}



//removes a key value pair from the sorted multimap

//returns true if the pair was removed (it was part of the multimap), false if nothing is removed

bool SortedMultiMap::remove(TKey c, TValue v) {
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		if (keyNode->key == c) {
			bool wasRemoved = deleteValueElement(keyNode->values, v);
			if (wasRemoved)
				if (keyNode->values->head == NULL) {
					deleteKeyElement(keyNode->key);
			}
			return wasRemoved;
		}
		keyNode = keyNode->next;
	}
	return false;
}



//returns the number of key-value pairs from the sorted multimap
//Complexity = Theta(n)
int SortedMultiMap::size() const {
	int count = 0;
	KeyNode* keyNode = dllKeys->head;
	while (keyNode != NULL) {
		ValueNode* valueNode = keyNode->values->head;
		while (valueNode != NULL) {
			count++;
			valueNode = valueNode->next;
		}
		keyNode = keyNode->next;
	}
	return count;
}



//verifies if the sorted multi map is empty
//Complexity Theta(1).
bool SortedMultiMap::isEmpty() const {
	//return size()==0;
	return dllKeys->head == NULL;
}



// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

TKey SortedMultiMap::difference()
{
	TKey kmax = -10000, kmin = 10000;
	KeyNode* p = dllKeys->head;
	while (p != NULL)
	{
		if (p->key <= kmin)
			kmin = p->key;
		else if (p->key >= kmax)
			kmax = p->key;
		p = p->next;
	}
	return kmax - kmin;
}



// destructor
//Complexity Theta(n*m)
SortedMultiMap::~SortedMultiMap() {
	KeyNode* currentNode = dllKeys->head;
	while (currentNode != dllKeys->tail) {
		ValueNode *valueNode = currentNode->values->head;
		while (valueNode != currentNode->values->tail) {
			valueNode = valueNode->next;
			delete valueNode->prev;
		}
		delete valueNode;
		delete currentNode->values;
		currentNode = currentNode->next;
		delete currentNode->prev;
	}
	delete currentNode;
	delete dllKeys;
}