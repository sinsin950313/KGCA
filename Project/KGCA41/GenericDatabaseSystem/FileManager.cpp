#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.h"
#include "IOManager.h"	//IOManager
#include <fstream>		//exit
#include "Buffer.h"		//Buffer
#include "Common.h"

FileManager* FileManager::_instance = nullptr;

void FileManager::Open(Buffer& buffer)
{
	Close();

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

void FileManager::Open(const char* path)
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

	Open(buffer);
}

void FileManager::Close()
{
	if (_fp != nullptr)
	{
		fclose(_fp);
		_fp = nullptr;
	}
}

FileManager& FileManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new FileManager;
	}
	return *_instance;
}

FileManager::~FileManager()
{
	delete _instance;
	Close();
}

bool FileManager::Read(Buffer& buffer)
{
	IOManager::GetInstance().Read(buffer, _fp);
	return feof(_fp) == 0;
}

void FileManager::Write(Buffer& buffer)
{
	IOManager::GetInstance().Write(buffer, _fp);
}

FILE* FileManager::Get()
{
	return _fp;
}
