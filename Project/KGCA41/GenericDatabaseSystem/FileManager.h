#pragma once

#include "Buffer.h"
#include <cstdio>

class FileManager
{
private:
	FILE* _fp = nullptr;

private:
	void FileOpen(Buffer& buffer, const char* mode);

public:
	FileManager(char* path);
	~FileManager();
	void Run();
};
