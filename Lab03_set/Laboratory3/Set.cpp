#include "Set.h"
#include "SetITerator.h"
#include <iostream>

using namespace std;

Set::Set() {
	this->capacity = 10;
	this->set = new TElem[capacity];
	this->positions = new int[capacity];
	this->head = -1;
	this->size_of_set = 0;

	// initialising every element of the set with NULL_TELEM
	for (int i = 0; i < this->capacity-1; i++)
	{
		this->set[i] = NULL_TELEM;
		this->positions[i] = i + 1;
	}
	this->positions[this->capacity - 1] = -1;
	this->next_free_position = 0;
}

bool Set::add(TElem elem) {

	if (this->size() != 0)
	{
		// in case set has elements we check for duplication
		int current_node = this->head;
		while (current_node != -1 and this->set[current_node] != elem)
		{
			current_node = this->positions[current_node];
		}
		if (current_node != -1)
		{
			return false;
		}
	}

	if (this->next_free_position == -1)
	{
		// resize
		// in case the capacity is reached we double the capacity
		TElem* new_set = new TElem[2 * this->capacity];
		int* new_positions = new int[2 * this->capacity];

		for (int i = 0; i < capacity; i++)
		{
			new_set[i] = this->set[i];
			new_positions[i] = this->positions[i];
		}
		for (int i = capacity-1; i < 2 * capacity - 1; i++)
		{
			new_positions[i] = i + 1;
		}
		new_positions[2 * capacity - 1] = -1;

		// we deallocate the previously used memory
		delete[] this->set;
		delete[] this->positions;

		this->set = new_set;
		this->positions = new_positions;
		this->next_free_position = capacity;
		this->capacity *= 2;
	}
	if (this->size() == 0)
	{
		this->set[this->next_free_position] = elem;
		this->head = this->next_free_position;
		this->next_free_position = this->positions[this->next_free_position];
	}
	else
	{
		int new_element_pos = this->next_free_position;
		this->next_free_position = this->positions[this->next_free_position];
		this->set[new_element_pos] = elem;
		this->positions[new_element_pos] = this->next_free_position;
	}
	this->size_of_set++;
	return true;
}


bool Set::remove(TElem elem) {
	int current_node = this->head, previous_node = -1;

	while (current_node != -1 and this->set[current_node] != elem)
	{
		previous_node = current_node;
		current_node = this->positions[current_node];
	}
	if (current_node != -1)
	{
		if (current_node == this->head)
			this->head = this->positions[this->head];
		else
		{
			this->positions[previous_node] = this->positions[current_node];
			this->positions[current_node] = this->next_free_position;
			this->next_free_position = current_node;
		}
		this->size_of_set--;	
		return true;
	}

	return false;
}

bool Set::search(TElem elem) const {
	int i = this->head;

	while (i != -1 && this->set[i]!= elem)
	{
		i = this->positions[i];
	}
	if (i == -1)
		return false;
	else
		return true;
}


int Set::size() const {
	return this->size_of_set;
}


bool Set::isEmpty() const {
	if (this->size_of_set == 0)
		return true;
	return false;
}

void Set::_union(const Set& s)
{
	//if (this->size() < s.size())
	//{
	//	// resize
	//	// in case the capacity is reached we double the capacity
	//	TElem* new_set = new TElem[this->capacity];
	//	int* new_positions = new int[this->capacity];

	//	for (int i = 0; i < s.capacity; i++)
	//	{
	//		new_set[i] = s.set[i];
	//		new_positions[i] = s.positions[i];
	//	}
	//	for (int i = s.capacity - 1; i < 2 * s.capacity - 1; i++)
	//	{
	//		new_positions[i] = i + 1;
	//	}
	//	new_positions[2 * s.capacity - 1] = -1;

	//	delete[] this->set;
	//	delete[] this->positions;

	//	this->set= new_set;
	//	this->positions = new_positions;
	//	this->next_free_position = s.capacity;
	//	this->capacity *= 2;
	//}
	//else
	//{
	//	for (int i = 0; i < s.capacity; i++)
	//	{
	//		this->set[i] = s.set[i];
	//		this->set[i] = s.positions[i];
	//	}
	//	for (int i = s.capacity - 1; i < 2 * s.capacity - 1; i++)
	//	{
	//		this->positions[i] = i + 1;
	//	}
	//	this->positions[2 * s.capacity - 1] = -1;

	//	this->next_free_position = capacity;
	//}

	int i = s.head;

	while (i != -1)
	{
		this->add(s.set[i]);
		i = this->positions[i];
	}

}

/*
	subalgorithm _union(old_set, new_set) is:

		i <- new_set.head
	
		while i != -1 do
			old_set.add(new_set.set[i])
			i<-new_set.positions[i]
		end-while
	
	end-subalgorithm


	complexity:
	BC Theta(old_set.size)
	AG O(old_set.size) amortized //(or Theta(old_set.size))
	WC O(old_set.size)
*/


Set::~Set() {
	delete[] this->set;
	delete[] this->positions;
}

void Set::print_set()
{
	int current_node = this->head;
	while (current_node != -1 )
	{
		cout << this->set[current_node] << ",";
		current_node = this->positions[current_node];
	}
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


