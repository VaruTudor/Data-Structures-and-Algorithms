#include "Linked_list.h"
#include <iostream>

bool Linked_list::is_empty() const
{
	if (this->head == nullptr)
		return true;
	return false;
}

void Linked_list::add_element(int row, int col, int value)
{
	node_poiner temporary_node_pointer = new node;

	temporary_node_pointer->row = row;
	temporary_node_pointer->col = col;
	temporary_node_pointer->value = value;
	temporary_node_pointer->next_node = nullptr;
	
	if (this->head == nullptr)
	{
		this->head = temporary_node_pointer;
		this->tail = temporary_node_pointer;
		temporary_node_pointer = nullptr;
	}
	else
	{
		this->tail->next_node = temporary_node_pointer;
		this->tail = temporary_node_pointer;
	}
}

void Linked_list::display()
{
	if (!this->is_empty())
	{
		node_poiner temporary_node_pointer = new node;
		temporary_node_pointer = this->head;

		while (temporary_node_pointer != nullptr)
		{
			cout << temporary_node_pointer->value << " ";
			temporary_node_pointer = temporary_node_pointer->next_node;
		}
	}

}
