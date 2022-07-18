#pragma once

class Buffer;

class Schema
{
private:
	Buffer* _buffer;

public:
	Schema(Buffer* buffer);
	Buffer* Get();
	//Print template Version
	void Print();
};
