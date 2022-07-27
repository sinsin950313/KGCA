#include "HeapSort.h"

void HeapSort::Push(int val)
{
	Array::Push(val);

	int currIndex = _index - 1;
	while (0 < currIndex)
	{
		int parentIndex = (currIndex - 1) / 2;
		if (0 <= parentIndex && _arr[parentIndex] < _arr[currIndex])
		{
			int tmp = _arr[parentIndex];
			_arr[parentIndex] = _arr[currIndex];
			_arr[currIndex] = _arr[parentIndex];
			currIndex = parentIndex;
		}
		else
		{
			break;
		}
	}
}

void HeapSort::Sort()
{
	int lastIndex = _index - 1;
	while (0 < lastIndex)
	{
		int tmp = _arr[lastIndex];
		_arr[lastIndex] = _arr[0];
		_arr[0] = tmp;
		--lastIndex;

		int parentIndex = 0;
		while (parentIndex <= lastIndex)
		{
			int childIndex = 2 * parentIndex + 1;
			if (lastIndex < childIndex)
			{
				break;
			}

			if (childIndex + 1 <= lastIndex && _arr[childIndex] < _arr[childIndex + 1])
			{
				++childIndex;
			}

			if (_arr[parentIndex] < _arr[childIndex])
			{
				int tmp = _arr[parentIndex];
				_arr[parentIndex] = _arr[childIndex];
				_arr[childIndex] = tmp;
				parentIndex = childIndex;
			}
			else
			{
				break;
			}
		}
	}
}
