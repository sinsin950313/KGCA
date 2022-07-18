#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.h"
#include "IOManager.h"	//IOManager
#include <fstream>		//exit
#include "Buffer.h"		//Buffer

void FileManager::FileOpen(Buffer& buffer)
{
	_fp = fopen(buffer.GetString(), "r+");
	if (_fp == NULL)
	{
		_fp = fopen(buffer.GetString(), "w+");
		if (_fp == NULL)
		{
			fprintf(stderr, "File %s open failed", buffer.GetString());
			exit(1);
		}
	}
}

FileManager::FileManager(const char* path)
{
	Buffer buffer;
	if (path != nullptr)
	{
		int size = 0;
		while (path[size] != '0')
		{
			++size;
		}
		buffer.Copy(path, size);
	}
	else
	{
		printf("읽을 파일명 : ");
		IOManager::GetInstance().Read(buffer);
	}

	FileOpen(buffer);
}

FileManager::~FileManager()
{
	fclose(_fp);
}

void FileManager::Run()
{
}
