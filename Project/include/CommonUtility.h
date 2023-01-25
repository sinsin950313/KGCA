#pragma once
#pragma warning(disable : 4996)

#include <string>
#include <codecvt>
#include <vector>
#include <io.h>
#include <tchar.h>
#include "Common.h"

namespace SSB
{
	static std::vector<std::wstring> GetFilesUnderDirectory(std::wstring path)
	{
		std::wstring dirPath = path + L"*.*";
		intptr_t handle;
		struct _wfinddata_t fd;
		handle = _wfindfirst(dirPath.c_str(), &fd);

		std::vector<std::wstring> list;
		if (handle != -1L)
		{
			do
			{
				if ((fd.attrib & _A_SUBDIR) && (fd.name[0] != '.'))
				{
					auto tmp = GetFilesUnderDirectory(path + fd.name + L"/");
					list.insert(list.end(), tmp.begin(), tmp.end());
				}
				else if (fd.name[0] != '.')
				{
					list.push_back(path + fd.name);
				}
			} while (_wfindnext(handle, &fd) == 0);
			_findclose(handle);
		}
		return list;
	}

	static std::vector<std::string> GetFilesUnderDirectory(std::string path)
	{
		std::string dirPath = path + "*.*";
		intptr_t handle;
		struct _finddata_t fd;
		handle = _findfirst(dirPath.c_str(), &fd);

		std::vector<std::string> list;
		if (handle != -1L)
		{
			do
			{
				if ((fd.attrib & _A_SUBDIR) && (fd.name[0] != '.'))
				{
					auto tmp = GetFilesUnderDirectory(path + fd.name + "/");
					list.insert(list.end(), tmp.begin(), tmp.end());
				}
				else if (fd.name[0] != '.')
				{
					list.push_back(path + fd.name);
				}
			} while (_findnext(handle, &fd) == 0);
			_findclose(handle);
		}
		return list;
	}

	static std::vector<std::wstring> SplitPath(std::wstring fullPath)
	{
		std::vector<std::wstring> ret;

		const UINT maxLength = 1024;
		TCHAR drive[maxLength]{ 0, };
		TCHAR dir[maxLength]{ 0, };
		TCHAR fileName[maxLength]{ 0, };
		TCHAR ext[maxLength]{ 0, };

		_tsplitpath_s(fullPath.c_str(), drive, dir, fileName, ext);

		ret.push_back(std::wstring(drive));
		ret.push_back(std::wstring(dir));
		ret.push_back(std::wstring(fileName));
		ret.push_back(std::wstring(ext));

		return ret;
	}
}
