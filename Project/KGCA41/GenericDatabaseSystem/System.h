#pragma once

#include "CustomLinkedList.h"
#include "Data.h"

class Schema;

class System
{
private:
	Schema* _schema;
	LinkedList<Data> _datas;

private:
	//Parse Schema and Datas
	void Parse(FILE* fp);
	void Create();
	void Read();
	void Update();
	void Delete();

public:
	System();
	void Transaction(char order);
};
