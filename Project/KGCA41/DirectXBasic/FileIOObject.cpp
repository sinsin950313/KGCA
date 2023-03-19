#define _CRT_SECURE_NO_WARNINGS

#include "FileIOObject.h"
#include "CommonPath.h"
#include "Common.h"
#include "CommonUtility.h"

namespace SSB
{
	static const std::string ext = ".Script";
	std::string ObjectScriptIO::Read(std::string fileName)
	{
		std::string ret;

		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + ext;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "r");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		char* buf = (char*)malloc(sizeof(char) * (fileSize + 1));
		rewind(fp);

		int readCount = fread(buf, sizeof(char), fileSize, fp);
		buf[fileSize] = 0;
		ret = std::string(buf);

		free(buf);
		fclose(fp);

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
	std::string ObjectScriptIO::ReadSkeleton(std::string fileName)
	{
		std::string ret;

		auto path = SplitPath(mtw(fileName));
		fileName = wtm(path[2]) + skeletonExt;
		FILE* fp = fopen((wtm(kObjectScriptPath) + fileName).c_str(), "r");

		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		char* buf = (char*)malloc(sizeof(char) * (fileSize + 1));
		rewind(fp);

		int readCount = fread(buf, sizeof(char), fileSize, fp);
		buf[fileSize] = 0;
		ret = std::string(buf);

		free(buf);
		fclose(fp);

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
}
