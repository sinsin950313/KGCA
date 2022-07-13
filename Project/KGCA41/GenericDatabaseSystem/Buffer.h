#pragma once

#define	DEFAULT 256
#define BYTE char

//Buffer class control C String
class Buffer
{
private:
	BYTE* _array = nullptr;
	int _size = 0;

private:
	void RequireMemory(int size, const char* eMessage);
	//pArr should be C string
	int GetSize(const BYTE* pArr);

public:
	Buffer();
	Buffer(int size);
	Buffer(Buffer& buffer) = delete;
	Buffer(const Buffer* buffer) = delete;
	Buffer(Buffer&& buffer) = delete;
	~Buffer();

public:
	//Clear and Reset size
	void SetBuffer(int size);
	bool IsEmpty();
	//pArr should be C string
	void Copy(const BYTE* pArr);
	const BYTE* GetString();
	//pArr should be C string
	void Push(const BYTE* pArr);
	Buffer& operator=(Buffer&& buffer) noexcept;
};
