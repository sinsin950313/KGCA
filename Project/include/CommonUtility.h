#pragma once

#include <string>
#include <codecvt>
#include <vector>
#include <io.h>

static std::wstring mtw(std::string str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.from_bytes(str);
}

static std::string wtm(std::wstring str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(str);
}

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
				GetFilesUnderDirectory(path + fd.name[0] + L"/");
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
				GetFilesUnderDirectory(path + fd.name[0] + "/");
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
