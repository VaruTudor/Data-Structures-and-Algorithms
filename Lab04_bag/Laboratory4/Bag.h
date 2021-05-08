#pragma once

typedef int Telem;

#define EMPTY_POSITION -999999
#define DELETED_POSITION 888999

class BagIterator;

class Bag
{
	friend class BagIterator;
protected:
	int size_of_bag; 
	int capacity;
	Telem* elements;

public:
	Bag();
	~Bag();

	Telem at(int positon);

	int size() { return this->size_of_bag; }


	bool isEmpty();

	/*
		finds the position where the element should be added
		returns:
			the position - if there is a free position
			-1 - if there is no free position
	*/
	int main_hash_function(Telem element);

	int first_hash_function(Telem element);
	int second_hash_function(Telem element);

	/*
		adds an element to the bag by computing where in the hash table
		return:
			true - the element has been added
			false = the element has not been added
	*/
	bool add(Telem element);

	void resize();

	bool search(Telem element);

	int nrOccurrences(Telem element);

	bool remove(Telem element);

	void print();

	//counts and returns the number of unique elements in the Bag
	int uniqueCount() const;

	int uniqueCount2() const;

	BagIterator iterator() const;
};

void test_prime();

void test_next_prime();