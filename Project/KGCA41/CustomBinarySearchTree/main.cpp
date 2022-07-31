#include "CustomBST.h"

int main()
{
	BST bst;
	bst.insert(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(3);
	bst.insert(7);
	bst.insert(12);

	bst.Erase(bst.Find(10));
	bst.Erase(bst.Find(12));

	bst.insert(12);
}