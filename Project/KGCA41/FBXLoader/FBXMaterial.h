#pragma once

#include "Material.h"

namespace SSB
{
	typedef std::string FBXMaterialKey;

	struct FBXMaterialData
	{
		MaterialIndex Index;
		Material* MeshMaterial;
	};
}
