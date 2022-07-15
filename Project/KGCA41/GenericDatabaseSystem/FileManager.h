#pragma once

#include <cstdio>	//FILE

class Buffer;

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
