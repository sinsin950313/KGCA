#define _CRT_SECURE_NO_WARNINGS

#include "IOManager.h"
#include "Buffer.h"	//Buffer

#define BUFFER_SIZE 256

IOManager* IOManager::_instance = nullptr;

IOManager& IOManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new IOManager();
	}
	return *_instance;
}

void IOManager::Write(Buffer& buffer, FILE* fp)
{
	fwrite(buffer.GetString(), 1, buffer.GetSize(), fp);
}

void IOManager::Read(Buffer& buffer)
{
	char c;
	while ((c = fgetc(stdin)) != '\n')
	{
		buffer.Push(&c, 1);
	}
}

void IOManager::Read(Buffer& buffer, FILE* fp)
{
	char c;
	while ((c = fgetc(fp)) != EOF)
	{
		buffer.Push(&c, 1);
	}
}
