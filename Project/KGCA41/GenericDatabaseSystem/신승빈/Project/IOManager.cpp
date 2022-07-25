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

IOManager::~IOManager()
{
	delete _instance;
}

void IOManager::Write(Buffer& buffer, FILE* fp)
{
	fwrite(buffer.GetString(), 1, buffer.GetSize(), fp);
}

void IOManager::Read(Buffer& buffer, FILE* fp, int count)
{
	char c;

	while (1)
	{
		c = fgetc(fp);
		if (c == '\n' || c == EOF)
		{
			break;
		}

		buffer.Push(&c, 1);

		if (count)
		{
			--count;
			if (count == 0)
			{
				break;
			}
		}
	}
}
