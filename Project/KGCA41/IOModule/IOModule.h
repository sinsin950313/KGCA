#pragma once

#include "Common.h"
#include <string>

namespace SSB
{
	class FileResource
	{
	private:
		Byte* _byte;
		unsigned long long _offset = 0;
		unsigned long long _size;

	public:
		FileResource(unsigned long long size);
		FileResource(FileResource& fr) = delete;
		FileResource(FileResource&& fr) noexcept;
		~FileResource();

	public:
		Byte* Get();
		unsigned long long GetSize();
		void Copy(Byte* byte, int size);
	};

	enum class IOState { SUCCESS, WORKING, FAILED };

	class FileResourceFactory
	{
	protected:
		std::string _path;
		FileResource* _fr = nullptr;

	public:
		void SetFilePath(std::string path);
		FileResource* GetFileResource();
		void SetFileResource(FileResource* fr);

	public:
		virtual IOState Read();
		virtual IOState Write();
	};

	class IOProgress
	{
	public:
		virtual int Get() = 0;
	};
}
