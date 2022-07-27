#include "MergeSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	cout << "Merge Sort" << endl;
	MergeSort merge(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		merge.Push(rand() % 101);
	}

	merge.Sort();

	const int* pArr = merge.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}
