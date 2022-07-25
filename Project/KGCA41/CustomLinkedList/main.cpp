#include "CustomLinkedList.h"

int main()
{
	Custom::LinkedList<int> ll;
	ll.PushBack(1);
	ll.PushBack(2);
	ll.PushBack(3);
	ll.PushFront(4);
	ll.PushFront(5);

	auto llIter = ll.Begin();
	while (llIter != ll.End())
	{
		cout << llIter.Get() << ", ";
		++llIter;
	}
	cout << endl;

	Custom::LinkedList<int> copy(ll);

	auto copyIter = copy.Begin();
	while (copyIter != copy.End())
	{
		cout << copyIter.Get() << ", ";
		++copyIter;
	}
	cout << endl;

	ll.Clear();

	auto llClearIter = ll.Begin();
	while (llClearIter != ll.End())
	{
		cout << llClearIter.Get() << ", ";
		++llClearIter;
	}
	cout << endl;

	copy.EraseBack();
	copy.EraseFront();
	auto copyEraseIter = copy.Begin();
	while (copyEraseIter != copy.End())
	{
		cout << copyEraseIter.Get() << ", ";
		++copyEraseIter;
	}
}