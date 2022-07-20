#include "CustomLinkedList.h"

int main()
{
	Custom::LinkedList<int> ll;
	ll.PushBack(1);
	ll.PushBack(2);
	ll.PushBack(3);
	ll.PushFront(4);
	ll.PushFront(5);

	Custom::LinkedList<int> copy(ll);
	copy.EraseBack();
	copy.EraseFront();

	ll.Clear();

	auto iter = copy.Begin();
	while (iter != copy.End())
	{
		cout << iter.Get() << ", ";
		++iter;
	}
}