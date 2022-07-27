#include "MergeSort.h"

void MergeSort::Merge(int start, int end)
{
	if (!(start + 1 <= end))
	{
		return;
	}

	int middle = (start + end) / 2;
	Merge(start, middle);
	Merge(middle + 1, end);

	Array left(middle - start + 1);
	for (int i = start; i < middle + 1; ++i)
	{
		left.Push(_arr[i]);
	}

	Array right(end - middle);
	for (int i = 0; i < end - middle; ++i)
	{
		right.Push(_arr[i + middle + 1]);
	}

	int index = start;
	const int* pLeftArr = left.Get();
	int leftIndex = 0;
	const int* pRightArr = right.Get();
	int rightIndex = 0;
	while (leftIndex < middle - start + 1 && rightIndex < end - middle)
	{
		if (pLeftArr[leftIndex] < pRightArr[rightIndex])
		{
			_arr[index] = pLeftArr[leftIndex];
			++leftIndex;
		}
		else
		{
			_arr[index] = pRightArr[rightIndex];
			++rightIndex;
		}
		++index;
	}
	while (leftIndex < middle - start + 1)
	{
		_arr[index] = pLeftArr[leftIndex];
		++index;
		++leftIndex;
	}
	while (rightIndex < end - middle)
	{
		_arr[index] = pRightArr[rightIndex];
		++index;
		++rightIndex;
	}
}

void MergeSort::Sort()
{
	Merge(0, _index - 1);
}
