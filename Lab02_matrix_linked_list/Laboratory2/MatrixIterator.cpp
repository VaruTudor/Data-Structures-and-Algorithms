//#include "MatrixIterator.h"

//#include <stdexcept>
//
//MIterator::MIterator(const Matrix_SLL& m) : matrix(m)
//{
//	this->current_row = 0;
//	this->current_col = 0;
//}
//
//void MIterator::first()
//{
//	this->current_row = 0;
//	this->current_col = 0;
//}
//
//void MIterator::next()
//{
//	if (!valid())
//		throw runtime_error("bad");
//	if (this->current_row == matrix.nr_lines())
//	{
//		this->current_col++;
//		this->current_row = 0;
//	}
//	else
//		this->current_row++;
//}
//
//bool MIterator::valid() const
//{
//	if (this->current_row == matrix.nr_lines())
//		if (this->get_current()->next_node != nullptr)
//			return false;
//	else
//		return true;
//}
//
//node_poiner MIterator::get_current() const
//{
//	if (!valid())
//		throw runtime_error("bad");
//	
//	return this->matrix.get_node(this->current_row, this->current_col);
//}
