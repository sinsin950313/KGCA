#pragma once

class Rectangle;

class VolumeInterface
{
public:
	virtual const Rectangle* GetVolume() = 0;
};
