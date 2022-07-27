#include "HeapSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	cout << "Heap Sort" << endl;
	HeapSort heap(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		heap.Push(rand() % 101);
	}

	heap.Sort();

	const int* pArr = heap.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}
