#pragma once
#include <string>

namespace SSB
{
	typedef std::string BoneName;
	typedef int BoneIndex;
	typedef std::string SocketName;
	typedef int SocketIndex;

	struct Bone
	{
		BoneIndex Index;
		BoneName Name;
		BoneIndex ParentIndex;
	};
}
