#pragma once

#include "DXObject.h"
#include "FBXLoader.h"
#include "Common.h"
#include "Material.h"
#include "Bone.h"
#include "Model.h"

namespace SSB
{
	struct ActionData
	{
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

		std::map<MaterialIndex, EditableMaterialObject*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;
		std::map<AnimationName, EditableAnimationObject*> _animations;

		struct SocketInfo
		{
			BoneIndex Index;
			BoneIndex ParentIndex;
			HMatrix44 LocalMatrix;
		};
		std::map<SocketName, SocketInfo> _sockets;
		EditableSkeletonObject* _skeleton;

		ActionData _selectedAnimation;

		std::string _pixelShaderFileName;

	public:
		const std::string kNewActionName = "NewAction";

	public:
		void Export();
		void Import();
		//void ExportSkeleton();
		//void ImportSkeleton();

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
		void AddSocket(SocketName socketName, BoneIndex parentIndex, HMatrix44 localMatrix);

	public:
		std::map<MaterialIndex, Material*> GetMaterials();
		std::map<MeshIndex, MeshInterface*> GetMeshes();
		std::map<AnimationName, Animation*> GetActions();
		Skeleton* GetSkeleton();
		PixelShader* GetPixelShader();
		std::vector<ActionData> GetActionList();
		DXObject* GetPreviewObject();

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
