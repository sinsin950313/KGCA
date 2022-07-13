#define _CRT_SECURE_NO_WARNINGS

#include "IOManager.h"
#include <malloc.h>
#include <cstdlib>
#include <utility>

#define BUFFER_SIZE 256

IOManager* IOManager::_instance = nullptr;

IOManager::IOManager()
{
}

IOManager& IOManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new IOManager();
	}
	return *_instance;
}

void IOManager::Read(FILE* fp, Buffer& buffer)
{
	char* tmp = static_cast<char*>(malloc(BUFFER_SIZE));
	if (tmp == NULL)
	{
		fprintf(stderr, "IOManager : Fail to Read");
		exit(1);
	}

	Buffer tmpBuffer;
	int totalSize = 0;
	while (fgets(tmp, BUFFER_SIZE, fp) != nullptr)
	{
		int size = 0;
		while (tmp[size] != '\n')
		{
			++size;
		}
		++size;

		tmpBuffer.Push(tmp);
	}

	buffer = std::move(tmpBuffer);
	free(tmp);
}

bool IOManager::IsQuit()
{
	return _quit;
}
