#pragma once

using namespace std;

typedef struct node {
	int row;
	int col;
	int value;
	node* next_node;
}* node_poiner;

class Linked_list
{
private:
	node_poiner head, tail;
	

public:
	// constructor for a linked list
	Linked_list() { head = nullptr; tail = nullptr; }

	void set_head(node_poiner new_head) { this->head = new_head; }
	void set_tail(node_poiner new_tail) { this->tail = new_tail; }

	node_poiner get_head() { return this->head; }
	node_poiner get_tail() { return this->tail; }

	bool is_empty() const;

	// adds an element to the end of the list
	void add_element(int row, int col, int value);

	// display the linked list
	void display();
};

