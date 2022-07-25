#pragma once

#include "Common.h"

#define	DEFAULT 256

class Buffer
{
private:
	CUSTOM_BYTE* _buffer = nullptr;
	int _maxSize = 0;
	int _currSize = 0;

private:
	void RequireMemory(int size, const char* eMessage);
	//void MemoryCopy(char* dest, const char* source, int count);

public:
	Buffer();
	Buffer(const CUSTOM_BYTE* pArr, int size);
	Buffer(const Buffer& copy);
	Buffer(Buffer&& move);
	~Buffer();

public:
	bool IsEmpty();
	void Copy(const CUSTOM_BYTE* pArr, int size);
	const char* GetString();
	const CUSTOM_BYTE* GetBuffer() const;
	/// <param name="size">If pArr is string, size only count characters</param>
	void Push(const CUSTOM_BYTE* pArr, int size);
	void Clear();
	int GetSize() const;

public:
	Buffer& operator=(Buffer&& buffer) noexcept;
};
