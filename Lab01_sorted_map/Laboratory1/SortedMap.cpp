#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
	relation = r;
	capacity = 10;
	nr_elem = 0;
	map = new TElem[capacity];

}

TValue SortedMap::add(TKey k, TValue v) {
	int i;
	TElem new_element;
	new_element.first = k;
	new_element.second = v;

	// check if the key already exists in the map and replace it's value
	for (i = 0; i < nr_elem; i++)
		if (map[i].first == new_element.first)
		{
			int old_value = map[i].second;
			map[i].second = new_element.second;
			return old_value;
		}

	// increase the capacity
	if (capacity == nr_elem)
	{
		TElem* new_map = new TElem[2 * capacity];
		for (i = 0; i < capacity; i++)
		{
			new_map[i] = map[i];
		}
		delete[] map;

		capacity *= 2;
		map = new_map;
	}


	i = 0;
	int found = 0, position_found = 0;
	while (i < nr_elem)
	{
		if (relation(new_element.first, map[i].first) == false)
			i++;
		else
		{
			found = 1;
			position_found = i;
			break;
		}
	}
	if (found == 1)
	{
		for (i = nr_elem; i > position_found; i--)
			map[i] = map[i - 1];
		nr_elem++;
		map[position_found] = new_element;
	}
	else
	{
		map[nr_elem] = new_element;
		nr_elem += 1;
	}

	return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
	for (int i = 0; i < nr_elem; i++)
		if (map[i].first == k)
			return map[i].second;
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
	int found = 0, value;
	for (int i = 0; i < nr_elem; i++)
	{
		if (map[i].first == k)
		{
			found = 1;
			value = map[i].second;
		}
		if (found == 1)
		{
			map[i] = map[i + 1];
		}
	}
	if (found == 1)
	{
		nr_elem--;
		return value;
	}
	return NULL_TVALUE;
}

int SortedMap::size() const {
	if (isEmpty()) return 0;
	return nr_elem;
}

bool SortedMap::isEmpty() const {
	if (nr_elem == 0) return true;
	return false;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[] map;
}

void SortedMap::printMap()
{
	cout << "capacity: " << capacity;
	cout << "nr_elem: " << nr_elem;
	cout << "the map is: ";
	for (int i = 0; i < nr_elem; i++)
	{
		cout << "Element " << i << " is  key: " << map[i].first << " value: \n" << map[i].second;
	}
}

int SortedMap::getValueRange() const
{
	if (isEmpty())
		return -1;

	for (int i = 0; i < nr_elem; i++)
	{
		cout << "Element " << i << " is  key: " << map[i].first << " value: " << map[i].second << endl;
	}
	return abs(map[nr_elem - 1].second - map[0].second);
}


/*
	function getValueRange(self) is:

	if isEmpty() then
		getValueRange <- -1
	end-if

	getValueRange <- map[nr_elem - 1].second - map[0].second

	end-function

	time complexity:
		BC/WC/AC are the same
		Theta(1)

*/