#pragma once
#include "Bag.h"

class BagIterator
{
	friend class Bag;
private:
	const Bag& bag;
	BagIterator(const Bag& given_bag);

	int current_element;
public:
	void first();
	void next();
	bool valid() const;
	Telem getCurrent() const;
};

