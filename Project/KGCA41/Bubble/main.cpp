#include "BubbleSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	cout << "Bubble Sort" << endl;
	BubbleSort bubble(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		bubble.Push(rand() % 101);
	}

	bubble.Sort();

	const int* pArr = bubble.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}