#include "Array.h"

using namespace Custom;

Array::Array(int length) : _size(length)
{
	_arr = new int[_size];
}

Array::~Array()
{
	delete _arr;
}

void Array::Push(int val)
{
	if (_index < _size)
	{
		_arr[_index] = val;
		++_index;
	}
}

const int* Array::Get()
{
	return _arr;
}
