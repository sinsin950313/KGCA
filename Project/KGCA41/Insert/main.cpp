#include "InsertSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	InsertSort insert(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		insert.Push(rand() % 101);
	}

	insert.Sort();

	const int* pArr = insert.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}
