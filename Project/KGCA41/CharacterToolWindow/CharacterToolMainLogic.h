#pragma once

#include "DXWindow.h"
#include "CharacterTool.h"
#include "Camera.h"
#include "DXObject.h"
#include "Map.h"

namespace SSB
{
	class CharacterToolMainLogic : public DXWindow
	{
	private:
		CharacterTool _tool;
		DebugCamera* _toolCamera;
		//ModelViewCamera* _pieCamera;
		//bool _playInEditor = false;
		//bool _isPIEChanged = false;
		DXObject* _object = nullptr;
		//std::string _currentActionName;
		//std::string _hopeActionName = "Idle";

	public:
		CharacterToolMainLogic(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
		CharacterToolMainLogic(HWND hwnd);

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;

	private:
		void GetPreview();

	public:
		void Import(std::string fileName);
		void Export(std::string fileName);
		void AddAnimation(std::string animationFileName);
		void RemoveAnimation(std::string actionName);
		void CutAnimation(std::string newActionName, FrameIndex pivotFrame);
		void ChangeAnimationData(std::string newActionName, FrameIndex pivotFrame);
		std::vector<SSB::ActionData> GetActionList();
		void SetCurrentAnimation(AnimationName name);
	};
}
