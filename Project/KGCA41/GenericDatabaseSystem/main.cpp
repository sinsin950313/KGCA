#define TEST_MODULE

#ifndef TEST_MODULE

#include "IOManager.h"
#include "FileManager.h"
#include "Buffer.h"
#include "System.h"

using namespace std;

int main(int argc, char* argv[])
{
	char* path = nullptr;
	if(argc != 1)
	{
		path = argv[1];
	}

	FileManager::GetInstance().FileOpen(path);
	System sys;

	Buffer buffer;
	while (1)
	{
		IOManager::GetInstance().Read(buffer, stdin, 1);
		char order = *buffer.GetString();

		sys.Transaction(order);

		buffer.Clear();
	}
}

#else
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Buffer.h"
#include "FileManager.h"
#include "IOManager.h"

#include "CustomLinkedList.h"
#include "Schema.h"

using namespace std;

int main()
{
	//Buffer empty;
	//empty.Push("Empty", 5);;
	//cout << empty.GetString() << " : " << empty.GetSize() << endl;
	Buffer test("start", 5);
	//cout << test.GetString() << " : " << test.GetSize() << endl;
	//test.Push("Push", 4);
	//cout << test.GetString() << " : " << test.GetSize() << endl;
	//test.Copy("Copy", 4);
	//cout << test.GetString() << " : " << test.GetSize() << endl;
	//test.Clear();

	//IOManager::GetInstance().Read(test);
	//cout << test.GetString() << endl;
	//FILE* fp = fopen("Test.txt", "w+");
	//IOManager::GetInstance().Write(test, fp);
	//fclose(fp);
	//test.Clear();
	//fp = fopen("Test.txt", "r");
	//IOManager::GetInstance().Read(test, fp);
	//cout << test.GetString() << endl;
	//fclose(fp);

	//FileManager::GetInstance().Open(nullptr);
	//FileManager::GetInstance().Close();
	//FileManager::GetInstance().Open("abc.txt");
	//test.Clear();
	//test.Push("abc", 3);
	//FileManager::GetInstance().Write(test);
	//FileManager::GetInstance().Close();
	//FileManager::GetInstance().Open("abc.txt");
	//test.Clear();
	//FileManager::GetInstance().Read(test);
	//cout << test.GetString() << endl;

	Schema schema;
	schema.Add('s', "kor");
	schema.Add('s', "math");
	schema.Add('s', "eng");
	for (auto iter = schema.CreateIterator(); iter != schema.End(); ++iter)
	{
		cout << iter.Get().GetType() << ", " << iter.Get().GetName() << endl;
	}
	auto iter = schema.CreateIterator();
	schema.Erase(iter);
	for (auto iter = schema.CreateIterator(); iter != schema.End(); ++iter)
	{
		if (iter.Get().IsAlive())
		{
			cout << iter.Get().GetType() << ", " << iter.Get().GetName() << endl;
		}
	}
	Buffer buffer = schema.GetSchema();
	cout << buffer.GetString();
}

#endif