#include "TInputManager.h"

TInputManager* TInputManager::_instance = nullptr;

void TInputManager::Set(HWND hWnd)
{
	_hWnd = hWnd;
}

TInputManager& TInputManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TInputManager();
	}
	return *_instance;
}

EKeyState TInputManager::GetKeyState(DWORD key)
{
	return _keyState[key];
}

bool TInputManager::Init()
{
	ZeroMemory(_keyState, sizeof(_keyState));
	return true;
}

bool TInputManager::Frame()
{
	GetCursorPos(&_mousePosition);
	ScreenToClient(_hWnd, &_mousePosition);

	// I think PRESS and RELEASE need time check, so just HOLD and FREE
	int keyCount = sizeof(_keyState) / sizeof(_keyState[0]);
	for (int iKeyIndex = 0; iKeyIndex < keyCount; ++iKeyIndex)
	{
		SHORT sKey = GetAsyncKeyState(iKeyIndex);
		if (sKey & 0x8000)
		{
			_keyState[iKeyIndex] = EKeyState::KEY_HOLD;
		}
		else
		{
			_keyState[iKeyIndex] = EKeyState::KEY_FREE;
		}
	}

	return true;
}

bool TInputManager::Render()
{
	return true;
}

bool TInputManager::Release()
{
	return true;
}
