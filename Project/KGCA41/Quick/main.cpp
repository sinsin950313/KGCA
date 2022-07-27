#include "QuickSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	cout << "Quick Sort" << endl;
	QuickSort quick(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		quick.Push(rand() % 101);
	}

	quick.Sort();

	const int* pArr = quick.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}
