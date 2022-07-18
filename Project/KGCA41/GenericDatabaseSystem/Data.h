#pragma once

#include "Common.h"
#include "Buffer.h"
#include "Schema.h"

class Data
{
private:
	Buffer _buffer;
	//Origin schema. Schema is changable during program running.
	Schema _schema;

private:
	Data(Buffer& buffer);

public:
	void Edit(Schema& schema);
	void Print(PrintType printType, Schema& schema);
	Buffer Serialize();

private:
	friend class DataFactory;
};
