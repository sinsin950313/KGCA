#define TEST_MODULE

#ifndef TEST_MODULE

#include "IOManager.h"
#include "FileManager.h"

using namespace std;

//int main(int argc, char* argv[])
//{
//	char* path = nullptr;
//	if(argc != 1)
//	{
//		path = argv[1];
//	}
//
//	FileManager fm(path);
//	while (IOManager::GetInstance().IsQuit())
//	{
//		fm.Run();
//	}
//}

#else
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Buffer.h"
#include "FileManager.h"
#include "IOManager.h"

#include "CustomLinkedList.h"

using namespace std;

int main()
{
	Custom::LinkedList<int> ll;
	ll.PushBack(1);
	ll.PushBack(2);
	ll.PushFront(2);
	ll.EraseBack();
	ll.EraseFront();

	Buffer test;
	test.SetBuffer(4);
	test.Copy("abc");
	cout << test.GetString() << endl;
	test.Push("abc");
	cout << test.GetString() << endl;

	FileManager fm(nullptr);
	char path[] = "abc";
	FileManager fm1(path);

	IOManager::GetInstance().Read(stdin, test);
	cout << test.GetString() << endl;
}

#endif