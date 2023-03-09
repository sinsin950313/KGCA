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

		Model* _model = nullptr;

	public:
		CharacterToolMainLogic(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
		CharacterToolMainLogic(HWND hwnd);

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;

	public:
		CharacterTool* GetTool();
		//void ChangePIEState();
		void SetCurrentAnimation(AnimationName name);
		void ClearModel();
		void UpdateAnimation();
	};
}
