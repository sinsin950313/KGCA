#include "QuickSort.h"
#include <iostream>
using namespace std;

void QuickSort::Quick(int start, int end)
{
	if (end - start < 2)
	{
		if (start < end && _arr[end] < _arr[start])
		{
			int tmp = _arr[end];
			_arr[end] = _arr[start];
			_arr[start] = tmp;
		}
		return;
	}

	int pivotIndex = start;
	int startIndex = start + 1;
	int endIndex = end;

	while (1)
	{
		while (startIndex < endIndex && _arr[startIndex] <= _arr[pivotIndex])
		{
			++startIndex;
		}
		while (startIndex < endIndex && _arr[pivotIndex] <= _arr[endIndex])
		{
			--endIndex;
		}

		if (_arr[endIndex] < _arr[startIndex])
		{
			int tmp = _arr[startIndex];
			_arr[startIndex] = _arr[endIndex];
			_arr[endIndex] = tmp;
		}
		else
		{
			if (_arr[pivotIndex] < _arr[startIndex])
			{
				--startIndex;
			}
			break;
		}
	}

	int tmp = _arr[pivotIndex];
	_arr[pivotIndex] = _arr[startIndex];
	_arr[startIndex] = tmp;

	int middle = startIndex;
	Quick(start, middle - 1);
	Quick(middle + 1, end);
}

void QuickSort::Sort()
{
	Quick(0, _index - 1);
}
