#pragma once

using namespace std;

typedef int INFO;
#define NULL_INFO -999999
class ListIterator;
typedef bool (*Relation)(INFO, INFO);

typedef struct node {
	INFO inf;
	node* left_child;
	node* right_child;
	int nr_elems_left = 0;
}*node_pointer;

class BST
{
	friend class ListIterator;
protected:
	node_pointer root;
	int size_of_list;
	Relation rel;

public:
	BST(Relation r) { this->root = nullptr, this->size_of_list = 0, this->rel = r; };

	node_pointer init_node(INFO elem_info);

	bool search(INFO elem_information);
	bool search_rec(node_pointer node, INFO elem_information);
	node_pointer search_ret(INFO elem_information);
	node_pointer search_rec_ret(node_pointer node, INFO elem_information);

	INFO get_element(ListIterator it);

	bool add(INFO elem_information);
	node_pointer add_element_rec(node_pointer node, INFO elem_information);
	
	node_pointer search_remove(node_pointer node, node_pointer parent, INFO elem_information);
	bool remove(INFO elem_information);

	ListIterator iterator() const;

	bool is_empty();
	int size() { return this->size_of_list; };


	int uniqueCount() const;
};

