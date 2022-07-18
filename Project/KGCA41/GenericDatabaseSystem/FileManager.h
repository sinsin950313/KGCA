#pragma once

#include <cstdio>	//FILE

class Buffer;

class FileManager
{
private:
	FILE* _fp = nullptr;

private:
	void FileOpen(Buffer& buffer);

public:
	FileManager(const char* path);
	~FileManager();
	void Run();
};
