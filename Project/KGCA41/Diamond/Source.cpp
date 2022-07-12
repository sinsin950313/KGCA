#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

bool isDiamond(int col, int row, int size)
{
	--size;
	int interval = col - size;
	if (interval < 0)
	{
		interval = ~interval + 1;
	}

	++size;
	if (interval <= row && row < size * 2 - 1 - interval)
		return true;
	return false;
}

int main()
{
	printf("크기 입력\n");

	int size;
	scanf("%d", &size);

	for (int i = 0; i < size * 2 - 1; ++i)
	{
		for (int j = 0; j < size * 2 - 1; ++j)
		{
			if (isDiamond(i, j, size))
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
