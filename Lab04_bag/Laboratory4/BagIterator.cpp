#include "BagIterator.h"
#include "Bag.h"

#include <exception>
#include <stdexcept>

#include <iostream>

#define NOT_VALID 9900990

// complexity O(capacity)
BagIterator::BagIterator(const Bag& given_bag) : bag(given_bag)
{
	this->current_element = 0;

	if ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity)
		while ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity)
		{
			this->current_element++;
		}
	if (this->current_element >= bag.capacity)
		this->current_element = NOT_VALID;
}

// complexity O(capacity)
void BagIterator::first()
{
	this->current_element = 0;

	if ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity)
		while ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity)
		{
			this->current_element++;
		}
	if (this->current_element >= bag.capacity)
		this->current_element = NOT_VALID;
}

// complexity O(capacity)
void BagIterator::next()
{
	if (!this->valid())
	{
		throw std::runtime_error("bad");
	}

	this->current_element++;
	if ( (this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity)
		while ( (this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->current_element < bag.capacity )
		{
			this->current_element++;
		}

	if (this->current_element>= bag.capacity)
		this->current_element = NOT_VALID;
}

// complexity Theta(1)
bool BagIterator::valid() const
{
	if (this->current_element != NOT_VALID)
		return true;
	return false;
}

// complexity Theta(1)
Telem BagIterator::getCurrent() const
{
	if (!this->valid())
	{
		throw std::runtime_error("bad");
	}
	return bag.elements[this->current_element];
}
