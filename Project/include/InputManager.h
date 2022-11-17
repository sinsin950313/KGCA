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
		static InputManager _instance;
		EKeyState _keyState[256];
		POINT _mousePosition;
		POINT _mousePrePosition;
		POINT _delta;
		HWND _hWnd;

	private:
		InputManager() { Init(); }
		~InputManager();

	public:
		void Set(HWND hWnd);
		static InputManager& GetInstance();
		EKeyState GetKeyState(DWORD key);
		POINT GetMousePosition() { return _mousePosition; }
		POINT GetDeltaPosition() { return _delta; }

	private:
		bool Init() override;
		bool Release() override;

	public:
		bool Frame() override;
		bool Render() override;
	};
}
