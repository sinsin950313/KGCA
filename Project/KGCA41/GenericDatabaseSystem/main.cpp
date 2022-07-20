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
	Buffer empty;
	empty.Push("Empty", 5);;
	cout << empty.GetString() << " : " << empty.GetSize() << endl;
	Buffer test("start", 5);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Push("Push", 4);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Copy("Copy", 4);
	cout << test.GetString() << " : " << test.GetSize() << endl;
	test.Clear();

	Buffer ioTest;
	IOManager::GetInstance().Read(ioTest);
	cout << ioTest.GetString() << endl;
	FILE* fp = fopen("Test.txt", "w+");
	IOManager::GetInstance().Write(ioTest, fp);
	fclose(fp);
	ioTest.Clear();
	fp = fopen("Test.txt", "r");
	IOManager::GetInstance().Read(ioTest, fp);
	cout << ioTest.GetString() << endl;
	fclose(fp);

	Buffer fmTest;
	FileManager::GetInstance().Open(nullptr);
	FileManager::GetInstance().Close();
	FileManager::GetInstance().Open("abc.txt");
	fmTest.Clear();
	fmTest.Push("abc", 3);
	FileManager::GetInstance().Write(fmTest);
	FileManager::GetInstance().Close();
	FileManager::GetInstance().Open("abc.txt");
	fmTest.Clear();
	FileManager::GetInstance().Read(fmTest);
	cout << fmTest.GetString() << endl;

	Schema schema;
	char schemaArr[20] = { 0, };
	strcpy(schemaArr, "kor");
	schema.Add('s', schemaArr);
	strcpy(schemaArr, "math");
	schema.Add('s', schemaArr);
	strcpy(schemaArr, "eng");
	schema.Add('s', schemaArr);
	for (auto iter = schema.CreateIterator(); iter != schema.End(); ++iter)
	{
		cout << iter.Get().GetType() << ", " << iter.Get().GetName() << endl;
	}
	auto schemaIter = schema.CreateIterator();
	schema.Erase(schemaIter);
	for (auto schemaIter = schema.CreateIterator(); schemaIter != schema.End(); ++schemaIter)
	{
		if (schemaIter.Get().IsAlive())
		{
			cout << schemaIter.Get().GetType() << ", " << schemaIter.Get().GetName() << endl;
		}
	}
	Buffer schemaTest = schema.GetSchema();
	const char* schemaStr = schemaTest.GetString();
	for (int i = 0; i < schemaTest.GetSize(); ++i)
	{
		if (schemaStr[i] == 0)
		{
			cout << '0';
		}
		else
		{
			cout << schemaStr[i];
		}
	}
}

#endif