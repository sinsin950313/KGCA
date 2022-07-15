#pragma once

#define	DEFAULT 256
#define BYTE char

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
	Buffer(const Buffer& buffer) = delete;
	Buffer(Buffer&& buffer) = delete;
	~Buffer();

public:
	bool IsEmpty();
	void Copy(const BYTE* pArr, int size);
	const char* GetString();
	const BYTE* GetBuffer();
	void Push(const BYTE* pArr, int size);
	void Clear();
	int GetSize();

public:
	Buffer& operator=(Buffer&& buffer) noexcept;
};
