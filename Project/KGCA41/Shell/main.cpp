#include "ShellSort.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int LENGTH = 100;

int main()
{
	ShellSort shell(LENGTH);
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < LENGTH; ++i)
	{
		shell.Push(rand() % 101);
	}

	shell.Sort();

	const int* pArr = shell.Get();
	for (int i = 0; i < LENGTH; ++i)
	{
		cout << pArr[i] << ", ";
	}
}
