#pragma once

#include "CommonClass.h"
#include <Windows.h>

enum class EKeyState
{
	KEY_FREE,
	KEY_PRESSED,
	KEY_HOLD,
	KEY_RELEASE,
};

class TInputManager : public Common
{
private:
	static TInputManager* _instance;
	EKeyState _keyState[256];
	POINT _mousePosition;
	HWND _hWnd;

private:
	TInputManager() { }

public:
	void Set(HWND hWnd);
	static TInputManager& GetInstance();
	EKeyState GetKeyState(DWORD key);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
