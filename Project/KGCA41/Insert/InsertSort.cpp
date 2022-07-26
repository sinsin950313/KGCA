#include "InsertSort.h"

void InsertSort::Sort()
{
	for (int i = 1; i < _size; ++i)
	{
		int tmp = _arr[i];
		int index = i;
		for (; 0 < index; --index)
		{
			if (tmp < _arr[index - 1])
			{
				_arr[index] = _arr[index - 1];
			}
			else
			{
				break;
			}
		}
		_arr[index] = tmp;
	}
}
