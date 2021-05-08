#include <assert.h>
#include "Matrix_SLL.h"
//#include "MatrixIterator.h"
#include <iostream>
#include "short_test.h"

using namespace std;

void test_all()
{
	Matrix_SLL matrix{ 4,4 };

	assert(matrix.nr_colums() == 4);
	assert(matrix.nr_lines() == 4);

	matrix.modify(1, 1, 5);
	//assert(matrix.element(1, 1) == 5);

	matrix.modify(1, 1, 6);
	//assert(matrix.element(1, 2) == 0);

	matrix.display_matrix();
}
//
//void test_iterator()
//{
//	cout << "TESTING ITERATOR";
//	Matrix_SLL matrix{ 4,4 };
//
//	MIterator it = matrix.iterator();
//	it.first();
//	while (it.valid())
//	{
//		node_poiner n = it.get_current();
//		cout << n->value;
//		it.next();
//	}
//}
