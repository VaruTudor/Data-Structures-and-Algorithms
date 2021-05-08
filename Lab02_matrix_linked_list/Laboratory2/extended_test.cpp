#include "Matrix_SLL.h"
#include <assert.h>
#include "extended_test.h"
#include <iostream>
#include <exception>

using namespace std;

void test_create()
{
	cout << "Testing create..." << endl;

	Matrix_SLL matrix(10, 10);
	assert(matrix.nr_colums() == 10);
	assert(matrix.nr_lines() == 10);
	for (int i = 0; i < matrix.nr_lines(); i++)
		for (int j = 0; j < matrix.nr_colums(); j++)
			assert( matrix.element(i, j) == 0);
}

void test_modify() {
	cout << "Testing modify..." << endl;

	Matrix_SLL matrix{ 10,10 };
	for (int j = 0; j < matrix.nr_colums(); j++)
		matrix.modify(4, j, 3);
	for (int i = 0; i < matrix.nr_lines(); i++)
		for (int j = 0; j < matrix.nr_colums(); j++)
			if (i == 4)
				assert(matrix.element(i, j) == 3);
			else
				assert(matrix.element(i, j) == 0);
}

void test_quantity()
{
	cout << "Testing quantity..." << endl;

	Matrix_SLL matrix{ 200,300 };

	for (int i = matrix.nr_lines()/2; i < matrix.nr_lines(); i++)
	{
		for (int j = 0; j < matrix.nr_colums()/2; j++)
		{
			int v1 = j;
			int v2 = matrix.nr_colums() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				matrix.modify(i, v1, i * v1);
			else if (v1 % 3 == 0)
				matrix.modify(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				matrix.modify(i, v2, i * v2);
			else if (v2 % 3 == 0)
				matrix.modify(i, v2, i + v2);
		}
	}

	for (int i = 0; i < matrix.nr_lines()/2; i++)
	{
		for (int j = 0; j < matrix.nr_colums()/2; j++)
		{
			int v1 = j;
			int v2 = matrix.nr_colums() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				matrix.modify(i, v1, i * v1);
			else if (v1 % 3 == 0)
				matrix.modify(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				matrix.modify(i, v2, i * v2);
			else if (v2 % 3 == 0)
				matrix.modify(i, v2, i + v2);
		}
	}

	for (int i = 0; i < matrix.nr_lines(); i++)
		for (int j = 0; j < matrix.nr_colums(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				assert(matrix.element(i, j) == i * j);
			else
				if (j % 3 == 0)
					assert(matrix.element(i, j) == i + j);
				else assert(matrix.element(i, j) == 0);
}

void test_exceptions() {
	cout << "Testing exceptions..." << endl;

	Matrix_SLL matrix(10, 10);
	try {
		matrix.element(-10, 0);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		matrix.modify(12, 0, 1);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		assert(matrix.nr_lines());
	}
	catch (exception&) {
		assert(false);
	}
}

void test_mix() {
	cout << "Testing mix..." << endl;

	int size = 200;
	Matrix_SLL m(size / 2, size);
	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				m.modify(i, j, 11);
			}
			else if (i == 100 * j) {
				m.modify(i, j, 111);
			}
			else if ((i + j) % 1111 == 0) {
				m.modify(i, j, 1111);
			}
		}
	}

	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				m.modify(i, j, 0);
			}
			else if (i == 100 * j) {
				m.modify(i, j, -111);
			}
			else if ((i + j) % 1111 == 3) {
				m.modify(i, j, 1);
			}
		}
	}
	
	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size; j++) {
			int e = m.element(i, j);
			if (i == j) {
				assert(e == 0);
			}
			else if (i == 100 * j) {
				assert(e == -111);
			}
			else if ((i + j) % 1111 == 3) {
				assert(e == 1);
			}
			else if ((i + j) % 1111 == 0) {
				assert(e == 1111);
			}
			else {
				assert(e == 0);
			}
		}
	}
}

void test_all_extended() {

	test_create();
	test_modify();
	test_quantity();
	test_exceptions();
	test_mix();
}