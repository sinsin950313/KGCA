#pragma once

#include <cstdio>	//FILE

class Buffer;

class FileManager
{
private:
	FILE* _fp = nullptr;
	static FileManager* _instance;

private:
	void Open(Buffer& buffer);
	FileManager() = default;

public:
	static FileManager& GetInstance();
	void Open(const char* path);
	void Close();
	~FileManager();
	//return file reading finish
	bool Read(Buffer& buffer);
	void Write(Buffer& buffer);
	const FILE* Get();
};
