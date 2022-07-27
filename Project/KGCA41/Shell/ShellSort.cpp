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
		for (int repeat = 0; repeat < gap; ++repeat)
		{
			for (int i = gap + repeat; i < _size; i += gap)
			{
				int tmp = _arr[i];
				int compIndex = i - gap;
				for (compIndex; 0 <= compIndex; compIndex -= gap)
				{
					if (tmp < _arr[compIndex])
					{
						_arr[compIndex + gap] = _arr[compIndex];
					}
					else
					{
						break;
					}
				}
				_arr[compIndex + gap] = tmp;
			}
		}
	}
}
