#include <assert.h>
#include <iostream>

#include "BST.h"
#include "ListIterator.h"

#include <exception>
#include "ShortTest.h"
using namespace std;

bool relation1(INFO e1, INFO e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
    BST list = BST(relation1);
	assert(list.size() == 0);
	assert(list.is_empty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.is_empty());
    ListIterator it = list.iterator();
    assert(it.valid());
    assert(it.getCurrent() == 1);
    it.next();
    assert(!it.valid());
    it.first();
    assert(it.valid());
}

void test_mine()
{
    cout << "my test\n";
    BST list = BST(relation1);
    assert(list.size() == 0);
    assert(list.is_empty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.is_empty());
    ListIterator it = list.iterator();
    assert(it.valid());
    assert(it.getCurrent() == 1);
    it.next();
    assert(!it.valid());
    it.first();
    assert(it.valid());
    for (int i = 3; i < 15; i++)
    {
        list.add(i);
    }
    for (int i = 3; i < 15; i++)
    {
        assert(list.search(i) == true);
    }
    for (int i = 3; i < 15; i++)
    {
        list.remove(i);
    }
    for (int i = 3; i < 15; i++)
    {
        assert(list.search(i) == false);
    }
}

void test_new_operation()
{
    cout << "Test new operation" << endl;

    BST list = BST(relation1);
    for (int i = 3; i < 8; i++)
    {
        list.add(i);
    }

    assert(list.uniqueCount() == 5);

    list.add(5);
    assert(list.uniqueCount() == 4);

    list.add(60);
    assert(list.uniqueCount() == 5);

    list.remove(5);
    assert(list.uniqueCount() == 6);
}

