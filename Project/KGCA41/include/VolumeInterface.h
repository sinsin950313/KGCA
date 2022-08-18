#pragma once

class Volume;

class VolumeInterface
{
public:
	virtual const Volume* GetVolume() = 0;
};
