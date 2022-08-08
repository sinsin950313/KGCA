#pragma once

#include "Object.h"

class VolumeInterface
{
public:
	virtual const Rect* GetVolume() = 0;
};
