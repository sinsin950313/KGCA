#include "ShellSort.h"

int ShellSort::GetGap(int val)
{
	return val >> 1;
}

void ShellSort::Sort()
{
	int gap = _size;
	while ((gap = GetGap(gap)))
	{
		for (int i = 0; i < gap; ++i)
		{
			int tmp = _arr[i];
			int index = i + gap;
			for (index; index < _size; index = index + gap)
			{
				if (tmp < _arr[index])
				{
					_arr[index - gap] = _arr[index];
				}
			}
			_arr[index] = tmp;
		}
	}
}
