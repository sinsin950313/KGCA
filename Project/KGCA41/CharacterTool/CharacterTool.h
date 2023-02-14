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
		int EndFrame;
	};

	class CharacterTool : public Common
	{
	private:
		FBXLoader* _loader;

		std::string _objectFileName;
		std::string _scriptFileName;
		std::string _actionFileName;

		DXObject* _object;
		std::vector<ActionData> _actionList;
		std::vector<ActionData>::iterator _selectedActionDataPointer;

	public:
		const std::string kNewActionName = "NewAction";

	private:
		std::vector<ActionData>::iterator GetIterator(std::string actionName);

	public:
		void Export();
		void Import();

	public:
		void RegisterObjectFileName(std::string fileName);
		void RegisterScriptFileName(std::string fileName);
		void RegisterActionFileName(std::string fileName);
		void ChangeActionName(std::string actionName);
		void ChangeEndFrame(int frame);
		std::vector<ActionData> GetActionList();
		void SelectCurrentAction(std::string actionName);
		void CutAnimataion();

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
