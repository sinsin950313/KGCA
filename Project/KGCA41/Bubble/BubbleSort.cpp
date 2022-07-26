#include "BubbleSort.h"

void BubbleSort::Sort()
{
	for (int i = 1; i < _index; ++i)
	{
		for (int j = 0; j < _index - i; ++j)
		{
			if (_arr[j + 1] < _arr[j])
			{
				int tmp = _arr[j];
				_arr[j] = _arr[j + 1];
				_arr[j + 1] = tmp;
			}
		}
	}
}
