#include "MyShortTest.h"
#include "Bag.h"

#include <assert.h>

void my_short_test()
{
	Bag bag;
	
	assert(bag.add(75) == true);
	assert(bag.at(7) == 75);

	assert(bag.add(12) == true);
	assert(bag.at(12) == 12);

	assert(bag.add(109) == true);
	assert(bag.at(4) == 109);
	
	assert(bag.add(43) == true);
	assert(bag.at(9) == 43);
	
	assert(bag.add(22) == true);
	assert(bag.at(5) == 22);
	
	assert(bag.add(18) == true);
	assert(bag.at(1) == 18);
}
