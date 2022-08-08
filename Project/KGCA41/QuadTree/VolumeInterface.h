#pragma once

class Rect;

class VolumeInterface
{
public:
	virtual const Rect* GetVolume() = 0;
};
