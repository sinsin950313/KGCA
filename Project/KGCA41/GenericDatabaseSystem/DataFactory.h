#pragma once

#include "Data.h"

class Schema;

class DataFactory
{
private:
	DataFactory();
	static DataFactory* _instance;

public:
	static DataFactory& GetInstance();
	Data* CreateData(Schema* schema);
};
