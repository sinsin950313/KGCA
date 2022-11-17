#include "InputManager.h"
#include <string>

namespace SSB
{
	InputManager InputManager::_instance;

	InputManager::~InputManager()
	{
		Release();
	}

	void InputManager::Set(HWND hWnd)
	{
		_hWnd = hWnd;
	}

	InputManager& InputManager::GetInstance()
	{
		return _instance;
	}

	EKeyState InputManager::GetKeyState(DWORD key)
	{
		return _keyState[key];
	}

	bool InputManager::Init()
	{
		ZeroMemory(_keyState, sizeof(_keyState));

		GetCursorPos(&_mousePosition);
		ScreenToClient(_hWnd, &_mousePosition);
		_mousePrePosition = _mousePosition;

		return true;
	}

	bool InputManager::Frame()
	{
		GetCursorPos(&_mousePosition);
		ScreenToClient(_hWnd, &_mousePosition);
		_delta.x = _mousePosition.x - _mousePrePosition.x;
		_delta.y = _mousePosition.y - _mousePrePosition.y;
		//if(_delta.x != 0 || _delta.y != 0)
		//OutputDebugString((std::to_wstring(_delta.x) + L", " + std::to_wstring(_delta.y) + L"\n").c_str());

		// I think PRESS and RELEASE need time check, so just HOLD and FREE
		int keyCount = sizeof(_keyState) / sizeof(_keyState[0]);
		for (int iKeyIndex = 0; iKeyIndex < keyCount; ++iKeyIndex)
		{
			SHORT sKey = GetAsyncKeyState(iKeyIndex);
			if (sKey & 0x8000)
			{
				if (_keyState[iKeyIndex] == EKeyState::KEY_PRESSED || _keyState[iKeyIndex] == EKeyState::KEY_HOLD)
				{
					_keyState[iKeyIndex] = EKeyState::KEY_HOLD;
				}
				else
				{
					_keyState[iKeyIndex] = EKeyState::KEY_PRESSED;
				}
			}
			else
			{
				if (_keyState[iKeyIndex] == EKeyState::KEY_PRESSED || _keyState[iKeyIndex] == EKeyState::KEY_HOLD)
				{
					_keyState[iKeyIndex] = EKeyState::KEY_RELEASE;
				}
				else
				{
					_keyState[iKeyIndex] = EKeyState::KEY_FREE;
				}
			}
		}
		_mousePrePosition = _mousePosition;

		return true;
	}

	bool InputManager::Render()
	{
		return true;
	}

	bool InputManager::Release()
	{
		return true;
	}
}
