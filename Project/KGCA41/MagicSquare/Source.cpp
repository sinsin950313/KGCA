#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int* access(int* const head, int col, int row, int size)
{
	return (head + (col * size)) + row;
}
bool isEmpty(int* const head, int col, int row, int size)
{
	return (*access(head, col, row, size) == 0);
}
void move(int* const head, int* col, int* row, int size)
{
	int tmpCol = *col;
	--tmpCol;
	if (tmpCol == -1)
	{
		tmpCol = size - 1;
	}

	int tmpRow = *row;
	++tmpRow;
	if (tmpRow == size)
	{
		tmpRow = 0;
	}

	if (!isEmpty(head, tmpCol, tmpRow, size))
	{
		tmpCol = *col;
		tmpRow = *row;

		++tmpCol;
		if (tmpCol == size)
		{
			tmpCol = 0;
		}
	}

	*col = tmpCol;
	*row = tmpRow;
}

void main()
{
	int size = 0;
	do
	{
		printf("홀수 마방진의 크기 : ");
		scanf("%d", &size);
	} while (size % 2 != 1);

	int* const arr = (int*)malloc(sizeof(int) * size * size);
	memset(arr, 0, sizeof(int) * size * size);

	int col = 0;
	int row = size >> 1;
	*access(arr, col, row, size) = 1;
	for (int i = 1; i < size * size; ++i)
	{
		move(arr, &col, &row, size);
		*access(arr, col, row, size) = i + 1;
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			printf("%d", *access(arr, i, j, size));
		}
		printf("\n");
	}

	free(arr);
}