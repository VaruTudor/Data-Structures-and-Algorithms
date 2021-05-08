#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool my_relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testMine() {
    SortedMap sm(my_relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1, 2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    //assert(sm.search(1) != NULL_TVALUE);
    //TValue v = sm.add(1, 3);
    //assert(v == 2);
    //assert(sm.search(1) == 3);

}
//assert(sm.remove(1) == 3);
//assert(sm.isEmpty());

