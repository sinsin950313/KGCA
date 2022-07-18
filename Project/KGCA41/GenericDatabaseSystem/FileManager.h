#pragma once

#include <cstdio>	//FILE

class Buffer;

class FileManager
{
private:
	FILE* _fp = nullptr;
	static FileManager* _instance;

private:
	void FileOpen(Buffer& buffer);
	FileManager();

public:
	static FileManager& GetInstance();
	void Open(const char* path);
	~FileManager();
	void Read(Buffer& buffer);
	void Write(Buffer& buffer);
	const FILE* Get();
};
