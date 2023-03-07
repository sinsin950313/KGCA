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
	private:
		FBXLoader* _loader = nullptr;

		std::string _objectFileName;
		std::string _scriptFileName;
		std::string _actionFileName;

		DXObject* _object;
		Model* _model;
		std::map<MaterialIndex, Material*> _materials;
		std::map<MeshIndex, MeshInterface*> _meshes;
		std::map<AnimationName, Animation*> _animations;

		Animation* _currentAnimation;

	public:
		const std::string kNewActionName = "NewAction";

	public:
		void Export();
		void Import();

	public:
		void RegisterObjectFileName(std::string fileName);
		void RegisterScriptFileName(std::string fileName);
		void RegisterActionFileName(std::string fileName);
		void AddAction(std::string actionFileName);
		void RemoveAction(std::string actionName);
		void SelectCurrentAction(std::string actionName);
		void CutAnimataion(std::string actionName, unsigned int lastFrame);
		void ChangeSelectedActionData(std::string actionName, unsigned int lastFrame);
		std::vector<ActionData> GetActionList();
		DXObject* GetTargetObject();

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
