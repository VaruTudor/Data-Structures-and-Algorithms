#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <stdexcept>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m) {
	current_element = 0;
}

void SMIterator::first() {
	current_element = 0;
}

void SMIterator::next() {

	if (!valid())
		throw runtime_error("bad");
	current_element++;
}

bool SMIterator::valid() const {
	if (current_element < map.nr_elem)
		return true;
	return false;
}

TElem SMIterator::getCurrent() const {

	if (!valid())
		throw runtime_error("bad");

	return map.map[current_element];
}


