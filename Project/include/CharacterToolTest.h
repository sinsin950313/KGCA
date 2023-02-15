#pragma once

#include "DXWindow.h"
#include "CharacterTool.h"
#include "Camera.h"

namespace SSB
{
    class CharacterToolTest : public DXWindow
    {
	private:
		CharacterTool _tool;
		Camera* _camera;

	public:
		CharacterToolTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
		CharacterToolTest(HWND hwnd);

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
    };
}
