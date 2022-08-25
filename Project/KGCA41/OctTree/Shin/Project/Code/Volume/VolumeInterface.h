#pragma once

#include "Volume.h"

template<int dimension>
class VolumeInterface
{
public:
	virtual const Volume<dimension>* GetVolume() = 0;
};
