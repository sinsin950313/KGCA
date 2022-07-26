#include "SelectionSort.h"

void SelectionSort::Sort()
{
	for (int i = 0; i < _size; ++i)
	{
		int tmp = _arr[i];
		for (int j = i + 1; j < _size; ++j)
		{
			if (_arr[j] < tmp)
			{
				int temp = tmp;
				tmp = _arr[j];
				_arr[j] = temp;
			}
		}
		_arr[i] = tmp;
	}
}
