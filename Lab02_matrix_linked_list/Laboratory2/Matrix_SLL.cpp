#include "Matrix_SLL.h"
#include <iostream>

Matrix_SLL::Matrix_SLL(int number_of_rows, int number_of_columns)
{
	this->number_of_rows = number_of_rows;
	this->number_of_columns = number_of_columns;
	this->elements_of_matrix = new Linked_list;
}

Matrix_SLL::~Matrix_SLL()
{
	delete[] this->elements_of_matrix;
}

void Matrix_SLL::display_matrix()
{
	this->elements_of_matrix->display();
	cout << endl;
}

int Matrix_SLL::nr_lines() const
{
	return this->number_of_rows;
}

int Matrix_SLL::nr_colums() const
{
	return this->number_of_columns;
}

int Matrix_SLL::check_validity_position(int row, int column) 
{
	if (row >= 0 && row <= this->number_of_rows && column >= 0 and column <= this->number_of_columns)
		return 1;
	return 0;
}

TElem Matrix_SLL::element(int row, int column) 
{
	if (!check_validity_position(row, column))
		throw exception();

	node_poiner current_node_pointer = new node;
	current_node_pointer = this->elements_of_matrix->get_head();

	if (current_node_pointer == nullptr)
		return NULL_TELEM;

	while(current_node_pointer->next_node != nullptr && current_node_pointer->row != row && current_node_pointer->col != column)
	{
		current_node_pointer = current_node_pointer->next_node;
	}

	return current_node_pointer->value;
}

//node_poiner Matrix_SLL::get_node(int row, int column)
//{
//	if (!check_validity_position(row, column))
//		throw exception();
//
//	node_poiner current_node_pointer = new node;
//	current_node_pointer = this->rows[row].get_head();
//
//	for (int i = 0; i < column; i++)
//	{
//		current_node_pointer = current_node_pointer->next_node;
//	}
//
//	return current_node_pointer;
//}
//
//MIterator Matrix_SLL::iterator() const
//{
//	return MIterator(*this);
//}



int Matrix_SLL::modify(int row, int column, int new_element)
{

	if (!check_validity_position(row, column))
		throw exception();
		

	node_poiner current_node_pointer = new node;
	current_node_pointer = this->elements_of_matrix->get_head();

	if (this->elements_of_matrix->is_empty())
	{
		current_node_pointer->value = new_element;
		current_node_pointer->row = row;
		current_node_pointer->col = column;
		this->elements_of_matrix->set_head(current_node_pointer);
		return NULL_TELEM;
	}
	else
	{
		while (current_node_pointer->next_node != nullptr)
		{
			current_node_pointer = current_node_pointer->next_node;
		}
	}

	return -1;
	
}