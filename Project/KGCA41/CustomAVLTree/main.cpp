#include "CustomAVLTree.h"

int main()
{
	AVL avl;
	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);
	avl.insert(7);
	avl.insert(8);
	avl.insert(9);

	avl.Erase(avl.Find(4));
	avl.Erase(avl.Find(5));
	avl.Erase(avl.Find(6));
	avl.Erase(avl.Find(7));
}