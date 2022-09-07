#pragma once

#include <Unknwnbase.h>

class Common
{
public:
	bool Release(IUnknown* ptr) { if (ptr) ptr->Release(); return true; }

public:
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
};
