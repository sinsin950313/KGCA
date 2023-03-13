#pragma once

#include <string>
#include "Common.h"
#include "Serializeable.h"
#include "SerializeableDataType.h"
#include <map>
#include <d3d11.h>

namespace SSB
{
	typedef std::string BoneName;
	typedef int BoneIndex;
	typedef std::string SocketName;
	typedef int SocketIndex;

	struct Bone
	{
		BoneName Name;
		BoneIndex ParentIndex;
		HMatrix44 Matrix;
	};

	class Skeleton : public Common, public Serializeable
	{
	private:
		struct FrameInfo
		{
			HMatrix44 BoneAnimationUnit[kAnimationUnitMaxIndex];
		};

	private:
		std::map<BoneIndex, Bone> _bones;
		FrameInfo _info;
		ID3D11Buffer* _buffer;

	private:
		void SetBoneInfo();
		bool CreateBuffer();

	public:
		void Initialize_SetBoneData(std::map<BoneIndex, Bone> bones);
		HMatrix44 GetWorldMatrix(BoneIndex index);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;	//Replace Animation setting
		bool Release() override;
		std::string Serialize(int tabCount) override;
		void Deserialize(std::string& serialedString) override;
	};
}
