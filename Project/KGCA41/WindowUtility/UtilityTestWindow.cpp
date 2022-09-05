#include "UtilityTestWindow.h"
#include "TInputManager.h"
#include <string>

bool UtilityTestWindow::Init()
{
    TBasicWindow::Init();

    _timer.Init();
    TInputManager::GetInstance().Init();

    return true;
}

bool UtilityTestWindow::Frame()
{
    TBasicWindow::Frame();

    _timer.Frame();
    TInputManager::GetInstance().Frame();

    return true;
}

bool UtilityTestWindow::Render()
{
    TBasicWindow::Render();

    std::wstring str = std::to_wstring(_timer.GetElapseTime() / 1000.0f).c_str();
    str += L"\n";
    OutputDebugString(str.c_str());

    if (TInputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
    {
		OutputDebugString(L"W Key Hold");
    }
    if (TInputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
    {
		OutputDebugString(L"A Key Hold");
    }
    if (TInputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
    {
		OutputDebugString(L"S Key Hold");
    }
    if (TInputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
    {
		OutputDebugString(L"D Key Hold");
    }

    return true;
}

bool UtilityTestWindow::Release()
{
    TBasicWindow::Release();

    _timer.Release();

    return true;
}
