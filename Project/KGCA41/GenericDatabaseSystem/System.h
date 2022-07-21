#pragma once

#include "CustomLinkedList.h"
#include "Data.h"
#include "Schema.h"

class System
{
private:
	Schema _schema;
	LinkedList<Data> _datas;

private:
	/// <summary>
	/// Parse Schema and Datas
	/// </summary>
	void Parse(FILE* fp);
	void Create();
	void Read();
	void Update();
	void Delete();

public:
	System();
	void Transaction(char order);
};
