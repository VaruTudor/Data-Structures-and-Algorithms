#pragma once
#include "BST.h"

#define STACK_SIZE 50000

typedef node_pointer stack_elem;

class Stack
{
protected:
	int size_of_stack;
	stack_elem* elems;

public:
	Stack();

	bool is_empty();
	stack_elem pop();
	stack_elem top();
	int size() { return this->size_of_stack; };
	void push(stack_elem n);
};

class ListIterator{
	friend class BST;
private:
	const BST& list;
	node_pointer current_node;
	Stack stack ;
	ListIterator(const BST& list);

public:
	void first();
	void next();
	bool valid() const;
    INFO getCurrent() const;
};

//void test_stack();