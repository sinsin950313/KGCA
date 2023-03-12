#pragma once

#include <fbxsdk.h>
#include "Bone.h"

namespace SSB
{
	typedef FbxNode* FBXBoneKey;

	struct FBXBoneData
	{
		int FBXBoneIndex;
		Bone BoneData;
	};
}
