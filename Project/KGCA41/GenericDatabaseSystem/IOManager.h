#pragma once

#include <cstdio>//FILE
#include "Buffer.h"

class IOManager
{
private:
	IOManager();
	static IOManager* _instance;

private:
	bool _quit = false;

public:
	static IOManager& GetInstance();
	void Read(FILE* fp, Buffer& buffer);
	bool IsQuit();
};
