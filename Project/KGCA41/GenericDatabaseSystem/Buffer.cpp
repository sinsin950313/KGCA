#define _CRT_SECURE_NO_WARNINGS

#include "Buffer.h"
#include <malloc.h>//free, malloc
#include <stdlib.h>//exit
#include <cstdio>//fprintf, stderr
#include <string>//strcpy

void Buffer::RequireMemory(int size, const char* eMessage)
{
	_array = static_cast<BYTE*>(malloc(sizeof(BYTE) * size));
	if (_array == NULL)
	{
		fprintf(stderr, eMessage);
		exit(1);
	}
	_size = size;
}

Buffer::Buffer()
{
	SetBuffer(DEFAULT);
}

Buffer::Buffer(int size)
{
	SetBuffer(size);
}

void Buffer::SetBuffer(int size)
{
	if (_array != nullptr)
	{
		free(_array);
	}

	RequireMemory(size, "Buffer allocation failed");

	memset(_array, 0, _size);
}

int Buffer::GetSize(const BYTE* pArr)
{
	int ret = 0;
	while (pArr[ret] != 0)
	{
		++ret;
	}
	return ret + 1;
}

bool Buffer::IsEmpty()
{
	int size = GetSize(_array);
	return size == 1;
}

void Buffer::Copy(const BYTE* pArr)
{
	//효율적인 버퍼를 만드는 것이 목적이 아니므로 일단은 메모리 재할당 방향으로 사용
	SetBuffer(GetSize(pArr));
	strcpy(_array, pArr);
}

const BYTE* Buffer::GetString()
{
	return _array;
}

void Buffer::Push(const BYTE* pArr)
{
	int eof = GetSize(_array);
	if (0 < eof)
	{
		--eof;

		if (eof + GetSize(pArr) <= _size)
		{
			strcpy(_array + eof, pArr);
		}
		else
		{
			char* tmp = _array;
			RequireMemory(eof + GetSize(pArr), "Require Memory for Push fail");
			strcpy(_array, tmp);
			free(tmp);

			Push(pArr);
		}
	}
	else
	{
		Copy(pArr);
	}
}

Buffer& Buffer::operator=(Buffer&& buffer) noexcept
{
	_size = buffer._size;
	BYTE* tmp = _array;
	_array = buffer._array;
	buffer._array = tmp;
	return *this;
}

Buffer::~Buffer()
{
	free(_array);
}
