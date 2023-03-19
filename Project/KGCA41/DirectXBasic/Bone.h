#pragma once

#include <string>
#include "Common.h"
#include "Serializeable.h"
#include "SerializeableDataType.h"
#include <map>
#include <d3d11.h>
#include "EditableInterface.h"

namespace SSB
{
	typedef std::string BoneName;
	typedef int BoneIndex;
	typedef std::string SocketName;
	typedef int SocketIndex;

	struct BoneInfo
	{
		BoneName Name;
		BoneIndex ParentIndex;
		HMatrix44 LocalMatrix;
	};

	class Skeleton : public Common, public Serializeable, public EditableInterface<Skeleton>
	{
	private:
		class Bone : public Serializeable
		{
		private:
			Bone* _parentBone = nullptr;
			BoneIndex _parentIndex;
			BoneName _name;
			HMatrix44 _localMatrix;

		public:
			void SetInfo(BoneInfo info);
			void SetParent(BoneIndex parentIndex, Bone* parentBone);

		public:
			BoneName GetName();
			HMatrix44 GetLocalMatrix();
			BoneIndex GetParentIndex();

		public:
			HMatrix44 GetWorldMatrix();

		public:
			std::string Serialize(int tabCount) override;
			void Deserialize(std::string& serialedString) override;
		};

	private:
		std::map<BoneIndex, Bone*> _bones;

		struct BoneSet
		{
			HMatrix44 _boneUnits[kAnimationUnitMaxIndex];
			HMatrix44 _MeshUnitsForDummy[kAnimationUnitMaxIndex];
		};
		BoneSet* _boneSet = nullptr;
		ID3D11Buffer* _buffer;

	public:
		Skeleton();
		~Skeleton();

	private:
		bool CreateBuffer();
		void AddBone(BoneIndex index, BoneInfo info);

	public:
		void Initialize_SetBoneData(std::map<BoneIndex, BoneInfo> bones);
		HMatrix44 GetWorldMatrix(BoneIndex index);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;	//Replace Animation setting
		bool Release() override;
		EditableObject<Skeleton>* GetEditableObject() override;
		std::string Serialize(int tabCount) override;
		void Deserialize(std::string& serialedString) override;
	};

	struct EditableSkeletonData
	{
		std::map<BoneIndex, BoneInfo> Bones;
	};
	class EditableSkeletonObject : public EditableObject<Skeleton>
	{
	private:
		std::map<BoneIndex, BoneInfo> _bones;

	public:
		EditableSkeletonObject(EditableSkeletonData data);

	public:
		BoneIndex AddSocket(BoneInfo info);

	public:
		std::map<BoneIndex, BoneInfo> GetBones();

	public:
		Skeleton* GetResult() override;
	};
}
