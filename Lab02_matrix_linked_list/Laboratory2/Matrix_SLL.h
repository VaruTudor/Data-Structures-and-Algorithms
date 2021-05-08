#pragma once
#include "Linked_list.h"
//#include "MatrixIterator.h"

typedef int TElem;
#define NULL_TELEM -11111;

class Matrix_SLL
{
private:
	Linked_list* elements_of_matrix;
	int number_of_rows;
	int number_of_columns;

public:
	// constructor for the matrix
	Matrix_SLL(int number_of_rows, int number_of_columns);

	// destructor
	~Matrix_SLL();

	// display the matrix
	void display_matrix();

	// returns the number of lines
	int nr_lines() const;

	// returns the number of colums
	int nr_colums() const;

	// returns 1 if position is valid
	// returns 0 if position is invalid
	int check_validity_position(int row, int column);

	// returns the element on position
	// raise exception if position invalid
	TElem element(int row, int column);

	// modies the element found on position if valid
	// returns the previous element on position
	// raise exception if position invalid
	int modify(int row, int column, int new_element);
};

