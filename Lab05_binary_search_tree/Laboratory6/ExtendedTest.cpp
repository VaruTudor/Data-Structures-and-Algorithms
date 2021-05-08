#include "ExtendedTest.h"
#include <assert.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include "BST.h"
#include "ListIterator.h"

using namespace std;


//relation order - ascending
bool asc(INFO c1, INFO c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}

//relation order - descending
bool desc(INFO c1, INFO c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

void testIteratorSteps(BST& sil, Relation r) {
	ListIterator li = sil.iterator();
	INFO elem = li.getCurrent();
	int count = 0;
	if (li.valid()) {
		count++;
		li.next();
	}
	while (li.valid()) {
		INFO elem2 = li.getCurrent();
		assert(r(elem2, elem));
		elem = elem2;
		count++;
		li.next();
	}
}

void testCreate() {
	cout << "Test create" << endl;
	BST list = BST(asc);
	assert(list.size() == 0);
	assert(list.is_empty());

	ListIterator it = list.iterator();
	assert(!it.valid());
	it.first();

	for (int i = 0; i < 10; i++) {
		assert(!it.valid());
		assert(!list.search(i));
		try {
			assert(list.get_element(it));
			assert(false);
		} catch (exception&) {
			assert(true);
		}
		try {
			assert(list.remove(i) == false);
		} catch (exception&) {
			assert(true);
		}
		try {
			it.next();
			assert(false);
		} catch(exception& ex) {
			assert(true);
		}
	}
}

//generate a vector with values between cMin and cMax so that
//1) no value that is >=cMin and <=cMax which is a multiple of s is not included
//2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
//3) values >=cMin and <=cMax are in random order
vector<int> random(int cMin, int cMax, int s, int m) {
	vector<int> v;
	for (int c = cMin; c <= cMax; c++) {
		if (c % s != 0) {
			v.push_back(c);
			if (c % m == 0) {
				for (int j = 0; j < c / m; j++) {
					v.push_back(c);
				}
			}
		}
	}
	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(v[i], v[j]);
	}
	return v;
}

//generate a vector containing values >=cMin and <=cMax, each included one time, in random order
vector<int> random(int cMin, int cMax) {
	vector<int> v;
	for (int c = cMin; c <= cMax; c++) {
		v.push_back(c);
	}

	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(v[i], v[j]);
	}
	return v;
}

//populate the sorted list with values >=cMin and <=cMax a.i.:
//1) no value that is >=cMin and <=cMax which is a multiple of s is not included
//2) values v, v>=cMin and v<=cMax which are a multiple of m (but not of s) are included c/m + 1 times
//3) values >=cMin and <=cMax are in random order
int populate(BST& list, int cMin, int cMax, int s, int m) {
	vector<int> v = random(cMin, cMax, s, m);
	int n = v.size();
	for (int i = 0; i < n; i++) {
		list.add(v[i]);
	}
	return n;
}

//populate the sorted list with values >=cMin and <=cMax, each included one time, in random order
void populate(BST& list, int cMin, int cMax) {
	vector<int> v = random(cMin, cMax);
	int n = v.size();
	for (int i = 0; i < n; i++) {
		list.add(v[i]);
	}
}

void testAddAndSearch(Relation r) {
	if (r == asc)
		cout << "Test add and search for asc" << endl;
	else if (r == desc)
		cout << "Test add and search for desc" << endl;
	else
		cout << "Test add and search" << endl;
	BST list = BST(r);
	int vMin = 10;
	int vMax = 30;
	int s = 5;
	int m = 3;
	int n = populate(list, vMin, vMax, s, m);
	assert(!list.is_empty());
	assert(list.size() == n);

	//we can't find values outside the interval or on invalid positions
	int d = 30;
	for (int i = 1; i <= d; i++) {
		assert(list.search(vMin - i) == false);
		assert(list.search(vMax + i) == false);
	}

	//check the relation order
	ListIterator it = list.iterator();
	assert(it.valid());
	INFO prev = it.getCurrent();
	it.next();
	while (it.valid()) {
		INFO current = list.get_element(it);
		assert(r(current, prev));
		prev = current;
		it.next();
	}

}

void testDeleteSearch(Relation r) {
	if (r == asc)
		cout << "Test add and search for asc" << endl;
	else if (r == desc)
		cout << "Test add and search for desc" << endl;
	else
		cout << "Test add and search" << endl;
	BST list = BST(r);
	int vMin = 0;
	int vMax = 100;
	populate(list, vMin, vMax);
	testIteratorSteps(list, r);
	int d = 30;
	for (int i = 1; i <= d; i++) {
		try {
			node_pointer node = list.search_ret(vMax + 1);
			list.remove(node->inf);
			assert(true);
		} catch (exception&) {
			assert(false);
		}
		testIteratorSteps(list, r);
	}

	assert(!list.is_empty());
	assert(list.size() == (vMax - vMin) + 1);
	ListIterator it1 = list.iterator();
	assert(it1.valid());
	INFO deleted = NULL_INFO;
	try {
		INFO deleted = it1.getCurrent();
		assert( list.remove(it1.getCurrent()) == true );
		assert(list.size() == vMax - vMin);
		it1.first();
		INFO newFirst = it1.getCurrent();
		ListIterator it2 = list.iterator();
		assert(it1.getCurrent() == newFirst && it2.getCurrent() == newFirst);
	} catch (exception&) {
		assert(false);
	}

	//delete values in random order while checking the relation order
	vector<int> vs = random(vMin, vMax);
	int n = vs.size();
	for (int i = 0; i < n; i++) {
		int v = vs[i];
		try {
			INFO deleteCurrent = list.search(v);
			assert(deleteCurrent != deleted);

			if (!list.is_empty()) {
				ListIterator it2 = list.iterator();
				assert(it2.valid());
				INFO prev = it2.getCurrent();
				while (it2.valid()) {
					it2.next();
					INFO current = it2.getCurrent();
					assert(r(current, prev));
					prev = current;
				}
			}

		} catch (exception&) {
			assert(true);
		}
	}

}

void testQuantity(){
	cout << "Test quantity" << endl;
	BST list = BST(asc);

	int vMin = 300000;
	int vMax = 400000;
	vector<int> values  = random(vMin, vMax);
	int n = values.size();
    for (int i = 0; i < n; i++){
    	list.add(values[i]);
    }

    assert(list.size() == vMax - vMin + 1);

    ListIterator it  = list.iterator();
    assert(it.valid());
    INFO firstElem = it.getCurrent();
    it.first();
    assert(it.valid());
    assert(it.getCurrent() == firstElem);
    for (int i = 0; i < list.size(); i++) {
    	it.next();
    }

    it.first();
    while (it.valid()){
        INFO v  = it.getCurrent();
        assert(vMin <= v && v<=vMax);
        it.next();
    }
    assert(!it.valid());


    int d = 100;
	//consider the interval [vMin-d, vMax+d]
	for (int v = vMin-d; v <= vMax+d; v++){
		//check that only values from the interval [vMin, vMax] are included in the list
		assert(list.search(v) == (vMin <= v && v <= vMax));
    	 try{
    		 list.remove(v);
    	 } catch (exception&) {
			 assert(vMin > v || v > vMax);
		}
    }
}

void testAllExtended() {
	testCreate();
	testAddAndSearch(desc);
	testAddAndSearch(asc);
	testDeleteSearch(desc);
	testDeleteSearch(asc);
	testQuantity();
}

