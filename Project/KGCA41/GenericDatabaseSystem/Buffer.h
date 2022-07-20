#pragma once

#include "Common.h"

#define	DEFAULT 256

class Buffer
{
private:
	BYTE* _buffer = nullptr;
	int _maxSize = 0;
	int _currSize = 0;

private:
	void RequireMemory(int size, const char* eMessage);

public:
	Buffer();
	Buffer(const BYTE* pArr, int size);
	Buffer(const Buffer& copy) = delete;
	Buffer(Buffer&& move);
	~Buffer();

public:
	bool IsEmpty();
	void Copy(const BYTE* pArr, int size);
	const char* GetString();
	const BYTE* GetBuffer();
	//size : if string, size only characters
	void Push(const BYTE* pArr, int size);
	void Clear();
	int GetSize();

public:
	Buffer& operator=(Buffer&& buffer) noexcept;
};
