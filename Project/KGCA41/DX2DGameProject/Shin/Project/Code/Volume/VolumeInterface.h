#pragma once

#include "Volume.h"

namespace SSB
{
	template<int dimension>
	class VolumeInterface
	{
	public:
		virtual const Volume<dimension>* GetVolume() = 0;
	};
}
