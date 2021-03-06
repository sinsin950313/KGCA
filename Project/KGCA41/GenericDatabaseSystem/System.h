#pragma once

#include "CustomLinkedList.h"
#include "Data.h"
#include "Schema.h"

class System
{
private:
	Schema _schema;
	int _deletedSchema = 0;
	int _schemaCount = 0;
	int _schemaIndex = 0;

	LinkedList<Data*> _datas;
	int _dataCount;
	int _dataIndex = 0;

public:
	System(const char* path);
	void Run();

private:
	void PrintSchema();
	void PrintData();
	void Print();
	void Transaction(char order);
	/// <summary>
	/// Parse Schema and Datas
	/// </summary>
	void Read();

private:
	void MoveCarret();
	void Up();
	void Down();
	void Left();
	void Right();

private:
	void CreateData();
	void CreateField();
	void Update();
	void DeleteData();
	void DeleteField();
	void Save();
	//void Sort();
	//void Find();

private:
	void InstructionManual();
	void Quit();
};
