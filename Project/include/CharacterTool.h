#pragma once

#include "DXObject.h"
#include "FBXLoader.h"
#include "Common.h"

namespace SSB
{
	struct ActionData
	{
		std::string ActionFileName;
		std::string ActionName;
		unsigned int EndFrame = 0;
	};

	class CharacterTool : public Common
	{
	private:
		FBXLoader* _loader = nullptr;

		std::string _objectFileName;
		std::string _scriptFileName;
		std::string _actionFileName;

		DXObject* _object = nullptr;
		std::vector<ActionData> _actionList;
		std::vector<ActionData>::iterator _selectedActionDataPointer;

		std::string _actionName;
		unsigned int _lastFrame;

	public:
		const std::string kNewActionName = "NewAction";

	private:
		std::vector<ActionData>::iterator GetIterator(std::string actionName);
		void Reload();

	public:
		void Export();
		void Import();

	public:
		void RegisterObjectFileName(std::string fileName);
		void RegisterScriptFileName(std::string fileName);
		void RegisterActionFileName(std::string fileName);
		void RegisterActionName(std::string actionName);
		void RegisterEndFrame(unsigned int frame);
		void AddAction(std::string actionFileName);
		void RemoveAction(std::string actionName);
		void SelectCurrentAction(std::string actionName);
		void CutAnimataion(std::string actionName, unsigned int lastFrame);
		void ChangeSelectedActionData(std::string actionName, unsigned int lastFrame);
		std::vector<ActionData> GetActionList();
		//void ChangeActionName(std::string actionName);
		//void ChangeEndFrame(int frame);

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
