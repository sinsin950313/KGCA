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
		std::string _actionName;
		int _endFrame;

		std::vector<ActionData> _actionList;
		DXObject* _object;

	private:
		std::vector<ActionData>::iterator GetIterator(std::string actionName);

	public:
		void Export();
		void Import();

	public:
		void RegisterObjectFileName(std::string fileName);
		void RegisterScriptFileName(std::string fileName);
		void RegisterActionFileName(std::string fileName);
		void RegisterActionName(std::string actionName);
		void RegisterCurrentAction(std::string actionName);
		void RegisterEndFrame(int frame);
		void GenerateAction();
		std::vector<ActionData> GetActionList();

	public:
		bool Init() override;
		bool Render() override;
		bool Frame() override;
		bool Release() override;
	};
}
