#define _CRT_SECURE_NO_WARNINGS

#include "IOModule.h"

namespace SSB
{
	void FileResourceFactory::SetFilePath(std::string path)
	{
		_path = path;
	}
	FileResource* FileResourceFactory::GetFileResource()
	{
		FileResource* ret = _fr;
		_fr = nullptr;
		return ret;
	}
	void FileResourceFactory::SetFileResource(FileResource* fr)
	{
		if (_fr != nullptr)
		{
			delete _fr;
		}
		_fr = fr;
	}
	IOState FileResourceFactory::Read()
	{
		FILE* fp;
		fp = fopen(_path.c_str(), "rb");

		if (fp == NULL)
		{
			return IOState::FAILED;
		}

		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);

		FileResource* fr = new FileResource(size);

		fseek(fp, 0, SEEK_SET);

		int count = 0;
		while (count != size)
		{
			char buf[256]{ 0, };
			int ret = fread(buf, sizeof(buf[0]), 256, fp);
			fr->Copy(buf, ret);

			count += ret;
		}

		fclose(fp);

		SetFileResource(fr);

		return IOState::SUCCESS;
	}
	IOState FileResourceFactory::Write()
	{
		FILE* fp;
		fp = fopen(_path.c_str(), "wb");

		if (fp == NULL)
		{
			return IOState::FAILED;
		}

		Byte* bytes = _fr->Get();
		int size = _fr->GetSize();

		int count = 0;
		while (count != size)
		{
			char buf[256]{ 0, };
			int block = min(256, size - count);
			memcpy(buf, bytes + count, block);
			int ret = fwrite(buf, sizeof(buf[0]), block, fp);
			count += ret;
		}

		fclose(fp);
		return IOState::SUCCESS;
	}
	FileResource::FileResource(unsigned long long size) : _size(size)
	{
		_byte = new Byte[_size];
	}
	FileResource::FileResource(FileResource&& fr) noexcept
	{
		_byte = fr._byte;
		fr._byte = nullptr;
		_offset = fr._offset;
		_size = fr._size;
	}
	FileResource::~FileResource()
	{
		delete[] _byte;
	}
	Byte* FileResource::Get()
	{
		return _byte;
	}
	unsigned long long FileResource::GetSize()
	{
		return _size;
	}
	void FileResource::Copy(Byte* byte, int size)
	{
		memcpy(_byte + _offset, byte, size);
		_offset += size;
	}
}
