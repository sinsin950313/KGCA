#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

int Hanoi(int ringCount, char from, char to, char tmp)
{
	int moved = 0;
	if (0 < ringCount)
	{
		moved += Hanoi(ringCount - 1, from, tmp, to);
		printf("%d : [%c] -> [%c]\n", ringCount, from, to);
		++moved;
		moved += Hanoi(ringCount - 1, tmp, to, from);
	}
	return moved;
}

void main()
{
	printf("원반의 개수 : ");

	int ringCount = 0;
	scanf("%d", &ringCount);

	printf("Total Move : %d\n", Hanoi(ringCount, 'A', 'C', 'B'));
}