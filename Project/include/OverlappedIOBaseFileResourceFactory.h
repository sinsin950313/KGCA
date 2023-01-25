#pragma once

#include "IOModule.h"

namespace SSB
{
	class OverlappedIOBaseFileResourceFactory : public FileResourceFactory
	{
	private:
		HANDLE _fileHandle;
		LARGE_INTEGER _fileSize;
		DWORD _bufferSize;
		OVERLAPPED _ov;
		bool _writing = false;;

	public:
		IOState Read() override;
		IOState Write() override;
	};

	//class OverlappedIOBaseFileResourceFactoryWithProgress : public FileResourceFactory, public IOProgress
	//{
	//public:
	//	IOState Read() override;
	//	IOState Write() override;
	//	int Get() override;
	//};
}
