#pragma once

#include <cstdio>	//FILE
#include "Buffer.h"

class Buffer;

class FileManager
{
private:
	FILE* _fp = nullptr;
	static FileManager* _instance;
	Buffer _path;

private:
	void Open(Buffer& buffer);
	FileManager() = default;

public:
	static FileManager& GetInstance();
	void Reopen();
	void Open(const char* path);
	void Close();
	~FileManager();
	/// <returns>Check file reading finish</returns>
	bool Read(Buffer& buffer);
	void Write(Buffer& buffer);
	FILE* Get();
};
