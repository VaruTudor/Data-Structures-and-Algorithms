#include "ListIterator.h"
#include "BST.h"
#include <exception>
#include <stdexcept>
using namespace std;

// complexity O(size)
ListIterator::ListIterator(const BST& list) : list(list){
	node_pointer n = this->list.root;

	while (n != nullptr)
	{
		this->stack.push(n);
		n = n->left_child;
	}
	if (!this->stack.is_empty())
		this->current_node = this->stack.top();
	else
		this->current_node = nullptr;
}

// complexity O(size)
void ListIterator::first()
{
	node_pointer n = this->list.root;

	while (n != nullptr)
	{
		this->stack.push(n);
		n = n->left_child;
	}

	if (!this->stack.is_empty())
		this->current_node = this->stack.top();
	else
		this->current_node = nullptr;
}

// complexity O(size-2)
void ListIterator::next(){
	if (this->stack.is_empty())
		throw runtime_error("bad");

	node_pointer node = this->stack.pop();

	if (node->right_child != nullptr)
	{
		node = node->right_child;
		while (node != nullptr)
		{
			this->stack.push(node);
			node = node->left_child;
		}
	}

	if (!this->stack.is_empty())
		this->current_node = this->stack.top();
	else
		this->current_node = nullptr;
}

// complexity Theta(1)
bool ListIterator::valid() const{
	if (this->current_node == nullptr)
		return false;
	return true;
}

// complexity Theta(1)
INFO ListIterator::getCurrent() const{
	if (!valid())
		throw runtime_error("bad");
	return this->current_node->inf;
}

// STACK

Stack::Stack()
{
	this->size_of_stack = 0;
	this->elems = new stack_elem[STACK_SIZE];
}

bool Stack::is_empty()
{
	if (this->size_of_stack == 0)
		return true;
	return false;
}

stack_elem Stack::pop()
{
	this->size_of_stack--;
	return this->elems[this->size_of_stack];
}

stack_elem Stack::top()
{
	return this->elems[this->size_of_stack - 1];
}

void Stack::push(stack_elem n)
{
	this->elems[this->size_of_stack] = n;
	this->size_of_stack++;
}

//#include <assert.h>
//void test_stack()
//{
//	Stack st;
//	assert(st.is_empty() == true);
//	st.push(5);
//	st.push(3);
//	st.push(2);
//	st.push(1);
//	assert(st.top() == 1);
//	assert(st.size() == 4);
//
//	assert(st.pop() == 1);
//	assert(st.size() == 3);
//	
//	assert(st.pop() == 2);
//	assert(st.pop() == 3);
//	assert(st.pop() == 5);
//	assert(st.size() == 0);
//}
