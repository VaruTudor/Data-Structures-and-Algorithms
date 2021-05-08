#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <iostream>

using namespace std;


void testAll() {
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.add(1) == false);
	assert(s.add(10) == false);
	assert(s.add(-3) == true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);

}

void test_new_op()
{
	Set new_set;
	Set new_set_to_be_changed;
	new_set.add(5);
	new_set.add(1);
	new_set.add(3);
	new_set_to_be_changed._union(new_set);
	assert(new_set_to_be_changed.search(5) == true);
	assert(new_set_to_be_changed.search(1) == true);
	assert(new_set_to_be_changed.search(3) == true);
	
	assert(new_set.add(3) == false);
	assert(new_set.add(4) == true);
	new_set_to_be_changed._union(new_set);
	assert(new_set_to_be_changed.search(5) == true);
	assert(new_set_to_be_changed.search(1) == true);
	assert(new_set_to_be_changed.search(3) == true);
	assert(new_set_to_be_changed.search(4) == true);
	

}

