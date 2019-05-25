#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <iostream>

//theta(2*capacity)<==>theta(capacity)
void SortedMultiMap::resize()
{
	BSTNode *aux = new BSTNode[this->bst.capacity * 2];
	for (int i = 0; i < this->bst.capacity; i++) {
		aux[i] = this->bst.nodes[i];
	}
	for (int i = this->bst.capacity; i < this->bst.capacity * 2; i++) {
		aux[i].info = nullValue;
		aux[i].left = null;
		aux[i].right = null;
	}
	recomputeFirstEmpty();
	this->bst.capacity *= 2;
	delete[]this->bst.nodes;
	this->bst.nodes = aux;
}

//theta(1)
void SortedMultiMap::recomputeFirstEmpty()
{
	while (this->bst.nodes[this->bst.firstEmpty].info != nullValue) {
		this->bst.firstEmpty++;
	}
}


int SortedMultiMap::insert_rec(int node, TElem e)
{
	if (node == null)
	{
		this->bst.nodes[this->bst.firstEmpty].info = e;
		int old = this->bst.firstEmpty;
		recomputeFirstEmpty();
		return old;
	}
	else if (!this->r(this->bst.nodes[node].info.first, e.first)) {
		this->bst.nodes[node].left = insert_rec(this->bst.nodes[node].left, e);
		return node;
	}
	else {
		this->bst.nodes[node].right = insert_rec(this->bst.nodes[node].right, e);
		return node;
	}
}

//O(height_of_subtree) <==>O(n)
int SortedMultiMap::minimum(int node)
{
	int current = node;
	while (this->bst.nodes[current].left != null)
		current = this->bst.nodes[current].left;
	return current;
}

int SortedMultiMap::remove_rec(int node, TElem e, bool &found)
{
	if (node == null)
		return null;
	if (this->bst.nodes[node].info == e) {
		found = true;
		if (this->bst.nodes[node].left == null && this->bst.nodes[node].right == null) {
			return null;
		}
		else if (this->bst.nodes[node].left == null) {
			return this->bst.nodes[node].right;
		}
		else if (this->bst.nodes[node].right == null) {
			return this->bst.nodes[node].left;
		}
		else {
			int min = minimum(this->bst.nodes[node].right);
			this->bst.nodes[node].info = this->bst.nodes[min].info;
			this->bst.nodes[node].right = remove_rec(this->bst.nodes[node].right, this->bst.nodes[min].info, found);
			return node;
		}
	}
	else if (!r(this->bst.nodes[node].info.first, e.first)) {
		this->bst.nodes[node].left = remove_rec(this->bst.nodes[node].left, e, found);
		return node;
	}
	else {
		this->bst.nodes[node].right = remove_rec(this->bst.nodes[node].right, e, found);
		return node;
	}
}

//theta(cap)
SortedMultiMap::SortedMultiMap(Relation r) : r(r)
{
	this->bst.capacity = cap;
	this->bst.nodes = new BSTNode[this->bst.capacity];
	this->bst.size = 0;
	this->bst.root = 0;
	this->bst.firstEmpty = 0;
	for (int i = 0; i < cap; i++) {
		this->bst.nodes[i].info = nullValue;
		this->bst.nodes[i].left = null;
		this->bst.nodes[i].right = null;
	}
}

//O(height) <==>O(n)
void SortedMultiMap::add(TKey c, TValue v)
{
	if (isEmpty()) {
		this->bst.nodes[0].info = std::make_pair(c, v);
		this->bst.firstEmpty = 1;
		this->bst.size++;
		return;
	}
	if (this->bst.size == this->bst.capacity - 1)
		resize();
	this->insert_rec(this->bst.root, std::make_pair(c, v));
	this->bst.size++;
}

//O(height) <==>O(n)
vector<TValue> SortedMultiMap::search(TKey c)
{
	vector<TValue> values;
	int current = this->bst.root;
	while (current != null) {
		if (this->r(this->bst.nodes[current].info.first, c)) {
			if (c == this->bst.nodes[current].info.first)
				values.push_back(this->bst.nodes[current].info.second);
			current = this->bst.nodes[current].right;
		}
		else {
			current = this->bst.nodes[current].left;
		}
	}
	return values;
}

//O(height) <==>O(n)
bool SortedMultiMap::remove(TKey c, TValue v)
{
	bool found = false;
	remove_rec(this->bst.root, std::make_pair(c, v), found);
	if (!found)
		return false;
	this->bst.size--;
	return true;
}

//theta(1)
int SortedMultiMap::size() const
{
	return this->bst.size;
}

//theta(1)
bool SortedMultiMap::isEmpty() const
{
	return this->bst.size == 0;
}

//O(n)
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

//theta(1)
SortedMultiMap::~SortedMultiMap()
{
	delete[] this->bst.nodes;
}
