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
		static DXObject DefaultObject;

	private:
		CharacterTool _tool;
		DebugCamera* _toolCamera;
		ModelViewCamera* _pieCamera;
		bool _playInEditor = true;
		bool _isPIEChanged = true;
		DXObject* _object = nullptr;
		Map* _terrain;

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
		void ChangePIEState();
	};
}
