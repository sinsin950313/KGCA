#pragma once

#include "DXObject.h"
#include "FBXLoader.h"
#include "Common.h"
#include "Model.h"
#include "Bone.h"

namespace SSB
{
	struct ActionData
	{
		Animation* AnimationPointer;
		std::string AnimationName;
		FrameIndex EndFrame;
	};
	class CharacterTool : public Common
	{
	public:
		const static int kEmptyFrame = -1;

	private:
		std::string _objectFileName;
		std::string _scriptFileName;

		std::map<MaterialIndex, Material*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;
		std::map<AnimationName, Animation*> _animations;
		Skeleton* _skeleton;

		ActionData _selectedAnimation;

		PixelShader* _ps;

	public:
		const std::string kNewActionName = "NewAction";

	public:
		void Export();
		void Import();
		void ExportSkeleton();
		void ImportSkeleton();

	private:
		void ClearAnimationSelection();
		bool IsSelected();

	public:
		void RegisterObjectFileName(std::string fileName);
		void RegisterScriptFileName(std::string fileName);
		void AddAction(std::string actionFileName);
		void RemoveAction(std::string actionName);
		void SelectCurrentAction(std::string actionName);
		void CutSelectedAnimataion(std::string newActionName, unsigned int lastFrame = -1);
		void ChangeSelectedAnimationData(std::string actionName, unsigned int frameSize);
		void AddSocket(std::string socketName, BoneIndex parentIndex, HMatrix44 matrix);

	public:
		std::map<MaterialIndex, Material*> GetMaterials();
		std::map<MeshIndex, MeshInterface*> GetMeshes();
		std::map<AnimationName, Animation*> GetActions();
		std::map<BoneName, Bone> GetBones();
		PixelShader* GetPixelShader();
		std::vector<ActionData> GetActionList();
		DXObject* GetPreviewObject();
		HMatrix44 GetBoneMatrix(BoneIndex index);

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
