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
	while (fgets(tmp, BUFFER_SIZE, fp) != NULL)
	{
		int i = 0;
		while (i < BUFFER_SIZE)
		{
			if (tmp[i] == '\n')
			{
				tmp[i] = 0;
				break;
			}
			++i;
		}

		tmpBuffer.Push(tmp);

		if (i < BUFFER_SIZE - 1 && tmp[i] == 0)
		{
			break;
		}
	}

	buffer = std::move(tmpBuffer);
	free(tmp);
}

bool IOManager::IsQuit()
{
	return _quit;
}
