#pragma once

#include "Common.h"

class Buffer;
class Schema;

class Data
{
private:
	Buffer* _buffer;

private:
	Data(Buffer& buffer);
	friend class DataFactory;

public:
	void Edit(Schema& schema);
	void print(PrintType printType, Schema& schema);
	Buffer Serialize();
};
