#pragma once

#include "DXObject.h"
#include "FBXLoader.h"
#include "Common.h"
#include "Model.h"

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

		ActionData _selectedAnimation;

		PixelShader* _ps;

	public:
		const std::string kNewActionName = "NewAction";

	public:
		void Export();
		void Import();

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

	public:
		std::map<MaterialIndex, Material*> GetMaterials();
		std::map<MeshIndex, MeshInterface*> GetMeshes();
		std::map<AnimationName, Animation*> GetActions();
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
