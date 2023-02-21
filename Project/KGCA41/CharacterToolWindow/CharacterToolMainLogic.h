#pragma once

#include "DXWindow.h"
#include "CharacterTool.h"
#include "Camera.h"
#include "DXObject.h"

namespace SSB
{
	class CharacterToolMainLogic : public DXWindow
	{
	private:
		CharacterTool _tool;
		Camera* _camera;
		bool _playInEditor = true;
		bool _isObjectSetting = false;
		DXObject* _object = nullptr;

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
	};
}
