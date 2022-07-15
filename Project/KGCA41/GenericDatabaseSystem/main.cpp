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

	Buffer test("start", 5);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Push("Push", 4);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Copy("Copy", 4);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Clear();

	IOManager::GetInstance().Read(test);
	cout << test.GetString() << endl;
	FILE* fp = fopen("Test.txt", "w+");
	IOManager::GetInstance().Write(test, fp);
	fclose(fp);
	test.Clear();
	fp = fopen("Test.txt", "r");
	IOManager::GetInstance().Read(test, fp);
	cout << test.GetString() << endl;
	fclose(fp);

	//FileManager fm(nullptr);
	//char path[] = "abc";
	//FileManager fm1(path);
}

#endif