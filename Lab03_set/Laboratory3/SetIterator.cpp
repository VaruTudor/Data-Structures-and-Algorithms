#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <stdexcept>

using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->current_element = set.head;
}


void SetIterator::first() {
	this->current_element = set.head;
}


void SetIterator::next() {
	if (!valid())
		throw runtime_error("bad");
	current_element = set.positions[current_element];
}


TElem SetIterator::getCurrent()
{
	if (!valid())
		throw runtime_error("bad");
	return set.set[current_element];
}

bool SetIterator::valid() const {
	if (current_element >= set.size() or set.size()==0)
		return false;
	return true;
}