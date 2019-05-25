#include "SMMIterator.h"

//O(n)
SMMIterator::SMMIterator(const SortedMultiMap & smm) :smm(smm)
{
	int node = smm.bst.root;
	while (node != null) {
		this->stack.push(node);
		node = smm.bst.nodes[node].left;
	}
	if (!this->stack.empty()) {
		this->currentNode = stack.top();
	}
	else {
		this->currentNode = null;
	}
	
}

//O(n)
void SMMIterator::first()
{
	while (!this->stack.empty())
		this->stack.pop();
	int node = smm.bst.root;
	while (node != null) {
		this->stack.push(node);
		node = smm.bst.nodes[node].left;
	}
	if (!this->stack.empty()) {
		this->currentNode = this->stack.top();
	}
	else {
		this->currentNode = null;
	}
}

//O(n)
void SMMIterator::next()
{
	if (!valid())
		throw std::exception();
	int node = this->stack.top();
	this->stack.pop();
	if (smm.bst.nodes[node].right != null) {
		node = smm.bst.nodes[node].right;
		while (node != null) {
			this->stack.push(node);
			node = smm.bst.nodes[node].left;
		}
	}
	if (!this->stack.empty()) {
		this->currentNode = this->stack.top();
	}
	else {
		this->currentNode = null;
	}
}

//theta(1)
TElem SMMIterator::getCurrent() const
{
	if (!valid())
		throw std::exception();
	return smm.bst.nodes[this->currentNode].info;
}

//theta(1)
bool SMMIterator::valid() const
{
	if (smm.isEmpty())
		return false;
	return this->currentNode != null;
}


