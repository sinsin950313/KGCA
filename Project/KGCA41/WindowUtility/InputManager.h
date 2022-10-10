#pragma once

#include "Common.h"
#include <Windows.h>

namespace SSB
{
	enum class EKeyState
	{
		KEY_FREE,
		KEY_PRESSED,
		KEY_HOLD,
		KEY_RELEASE,
	};

	class InputManager : public Common
	{
	private:
		static InputManager* _instance;
		EKeyState _keyState[256];
		POINT _mousePosition;
		HWND _hWnd;

	private:
		InputManager() { }
		~InputManager();

	public:
		void Set(HWND hWnd);
		static InputManager& GetInstance();
		EKeyState GetKeyState(DWORD key);
		POINT GetMousePosition() { return _mousePosition; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
