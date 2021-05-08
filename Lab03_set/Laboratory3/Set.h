#pragma once

#define NULL_TELEM -11111
typedef int TElem;
class SetIterator;

class Set {
    friend class SetIterator;

protected:
    TElem* set;
    int* positions;
    int capacity;
    int head;
    int next_free_position;
    int size_of_set;

public:
    //implicit constructor
    Set();

    //adds an element to the set
    //returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
    bool add(TElem e);

    //removes an element from the set
    //returns true if e was removed, false otherwise
    bool remove(TElem e);

    //checks whether an element belongs to the set or not
    bool search(TElem elem) const;

    //returns the number of elements;
    int size() const;

    //check whether the set is empty or not;
    bool isEmpty() const;

    //adds all elements of s into this set
    void _union(const Set& s);

    //return an iterator for the set
    SetIterator iterator() const;

    // destructor
    ~Set();

    void print_set();

};