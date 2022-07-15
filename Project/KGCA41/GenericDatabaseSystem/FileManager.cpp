#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.h"
#include "IOManager.h"	//IOManager
#include <fstream>		//exit
#include "Buffer.h"		//Buffer

void FileManager::FileOpen(Buffer& buffer, const char* mode)
{
	_fp = fopen(buffer.GetString(), mode);
	if (_fp == NULL)
	{
		fprintf(stderr, "File %s open failed", buffer.GetString());
		exit(1);
	}
}

FileManager::FileManager(char* path)
{
	//Buffer buffer;
	//if (path != nullptr)
	//{
	//	int size = 0;
	//	while (path[size] != '\n')
	//	{
	//		++size;
	//	}
	//	buffer.Copy(path);
	//}
	//else
	//{
	//	printf("읽을 파일명 : ");
	//	IOManager::GetInstance().Read(stdin, buffer);
	//}

	//FileOpen(buffer, "r+");
}

FileManager::~FileManager()
{
	fclose(_fp);
}

void FileManager::Run()
{
}
