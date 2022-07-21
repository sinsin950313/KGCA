#define _CRT_SECURE_NO_WARNINGS

#include "Buffer.h"
#include <malloc.h>	//free, malloc
#include <stdlib.h>	//exit
#include <cstdio>	//fprintf, stderr
#include <string>	//strcpy

void Buffer::RequireMemory(int size, const char* eMessage)
{
	if (_buffer != nullptr)
	{
		free(_buffer);
	}

	_buffer = static_cast<BYTE*>(malloc(sizeof(BYTE) * size));
	if (_buffer == NULL)
	{
		fprintf(stderr, eMessage);
		exit(1);
	}

	_currSize = 0;
	_maxSize = size;
}

Buffer::Buffer()
{
	RequireMemory(DEFAULT, "Buffer create failed");
	Clear();
}

Buffer::Buffer(const BYTE* pArr, int size)
{
	RequireMemory(size, "Buffer create failed");
	Copy(pArr, size);
}

Buffer::Buffer(const Buffer& copy)
{
	RequireMemory(copy._maxSize, "Buffer create failed");
	Clear();

	memcpy(_buffer, copy._buffer, copy._currSize);
	_maxSize = copy._maxSize;
	_currSize = copy._currSize;
}

bool Buffer::IsEmpty()
{
	return _currSize == 0;
}

void Buffer::Copy(const BYTE* pArr, int size)
{
	if (_maxSize < size)
	{
		RequireMemory(size, "Copy failed");
	}
	Clear();
	memcpy(_buffer, pArr, size);
	_currSize = size;
}

const BYTE* Buffer::GetString()
{
	if (_buffer[_maxSize - 1] != 0)
	{
		BYTE* tmp = _buffer;
		_buffer = nullptr;
		RequireMemory(_maxSize + 1, "Make string failed");
		memset(_buffer, 0, _maxSize);
		Copy(tmp, _maxSize - 1);
		free(tmp);
	}
	return _buffer;
}

const BYTE* Buffer::GetBuffer() const
{
	return _buffer;
}

void Buffer::Push(const BYTE* pArr, int size)
{
	if (_maxSize < _currSize + size)
	{
		BYTE* tmp = _buffer;
		int tmpSize = _currSize;
		_buffer = nullptr;
		RequireMemory(_currSize + size, "Fail to Push memory to Buffer");
		Copy(tmp, tmpSize);
		free(tmp);
	}
	memcpy(_buffer + _currSize, pArr, size);
	_currSize += size;
}

void Buffer::Clear()
{
	memset(_buffer, 0, _maxSize);
	_currSize = 0;
}

int Buffer::GetSize() const
{
	return _currSize;
}

Buffer& Buffer::operator=(Buffer&& buffer) noexcept
{
	_maxSize = buffer._maxSize;
	BYTE* tmp = _buffer;
	_buffer = buffer._buffer;
	buffer._buffer = tmp;
	return *this;
}

Buffer::Buffer(Buffer&& move)
{
	_buffer = move._buffer;
	move._buffer = nullptr;
	_maxSize = move._maxSize;
	_currSize = move._currSize;
}

Buffer::~Buffer()
{
	free(_buffer);
}
