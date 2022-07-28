#include "CustomTree.h"
#include <iostream>

using namespace std;

int main()
{
	Custom::Tree tree(2);
	for (int i = 0; i < 10; ++i)
	{
		tree.Add(i * 5);
	}

	cout << tree.Get(5) << endl;
}