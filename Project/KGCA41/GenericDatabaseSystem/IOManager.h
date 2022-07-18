#pragma once

#include <cstdio>	//FILE

class Buffer;

class IOManager
{
private:
	IOManager() = default;
	static IOManager* _instance;

public:
	static IOManager& GetInstance();
	//Read for stdin
	void Read(Buffer& buffer, FILE* fp = stdin, int count = 0);
	void Write(Buffer& buffer, FILE* fp);
};
