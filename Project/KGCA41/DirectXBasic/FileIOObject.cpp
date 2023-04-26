#define _CRT_SECURE_NO_WARNINGS

#include "FileIOObject.h"
#include "CommonPath.h"
#include "Common.h"
#include "CommonUtility.h"

namespace SSB
{
	ObjectScriptIO::~ObjectScriptIO()
	{
		if (_str != nullptr)
		{
			delete _str;
			_str = nullptr;
		}
	}
	void ObjectScriptIO::NewBuffer(int size)
	{
		if (_str != nullptr)
		{
			delete _str;
			_str = nullptr;
		}
		_str = new char[size];
	}
	static const std::string ext = ".Script";
	ReadScriptInfo ObjectScriptIO::Read(std::string fileName)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + ext;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "r");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		NewBuffer(fileSize + 1);
		rewind(fp);

		int readCount = fread(_str, sizeof(char), fileSize, fp);
		_str[fileSize] = 0;

		fclose(fp);

		ReadScriptInfo ret;
		ret.BufferSize = fileSize + 1;
		ret.Pointer = _str;
		return ret;
	}
	void ObjectScriptIO::Write(std::string fileName, std::string str)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + ext;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "w");

		int writeCount = fwrite(str.c_str(), sizeof(char), str.size(), fp);

		fclose(fp);
	}

	static const std::string skeletonExt = ".SkeletonScript";
	ReadScriptInfo ObjectScriptIO::ReadSkeleton(std::string fileName)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + skeletonExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "r");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		NewBuffer(fileSize + 1);
		rewind(fp);

		int readCount = fread(_str, sizeof(char), fileSize, fp);
		_str[fileSize] = 0;

		fclose(fp);

		ReadScriptInfo ret;
		ret.BufferSize = fileSize + 1;
		ret.Pointer = _str;
		return ret;
	}
	void ObjectScriptIO::WriteSkeleton(std::string fileName, std::string str)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + skeletonExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "w");

		int writeCount = fwrite(str.c_str(), sizeof(char), str.size(), fp);

		fclose(fp);
	}

	static const std::string binaryExt = ".BinaryScript";
	ReadScriptInfo ObjectScriptIO::ReadBinary(std::string fileName)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + binaryExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "rb");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		NewBuffer(fileSize + 1);
		rewind(fp);

		int readCount = fread(_str, sizeof(char), fileSize, fp);
		_str[fileSize] = 0;

		fclose(fp);

		ReadScriptInfo ret;
		ret.BufferSize = fileSize + 1;
		ret.Pointer = _str;
		return ret;
	}
	void ObjectScriptIO::WriteBinary(std::string fileName, std::string str)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + binaryExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "wb");

		int writeCount = fwrite(str.c_str(), sizeof(char), str.size(), fp);

		fclose(fp);
	}

	static const std::string skeletonBinaryExt = ".SkeletonBinaryScript";
	ReadScriptInfo ObjectScriptIO::ReadSkeletonBinary(std::string fileName)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + skeletonBinaryExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "r");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		NewBuffer(fileSize + 1);
		rewind(fp);

		int readCount = fread(_str, sizeof(char), fileSize, fp);
		_str[fileSize] = 0;

		fclose(fp);

		ReadScriptInfo ret;
		ret.BufferSize = fileSize + 1;
		ret.Pointer = _str;
		return ret;
	}
	void ObjectScriptIO::WriteSkeletonBinary(std::string fileName, std::string str)
	{
		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + skeletonBinaryExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "w");

		int writeCount = fwrite(str.c_str(), sizeof(char), str.size(), fp);

		fclose(fp);
	}
}
