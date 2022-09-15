#include "UtilityTestWindow.h"
#include "TInputManager.h"
#include <string>
#include "SoundManager.h"
#include "Sound.h"

bool UtilityTestWindow::Init()
{
    TBasicWindow::Init();

    _timer.Init();
    TInputManager::GetInstance().Init();
    SoundManager::GetInstance().Init();
    _sound = SoundManager::GetInstance().Load(L"MyLove.mp3");
    _sound->Init();

    return true;
}

bool UtilityTestWindow::Frame()
{
    TBasicWindow::Frame();

    static bool check = false;

    _timer.Frame();
    TInputManager::GetInstance().Frame();
    SoundManager::GetInstance().Frame();
    if (TInputManager::GetInstance().GetKeyState(VK_F1) == EKeyState::KEY_HOLD)
    {
        //_sound1->PlayInstance();
        if (!check)
        {
            SoundManager::GetInstance().PlayInstanceSound(L"GunShot.mp3");
            check = true;
        }
    }
    if (TInputManager::GetInstance().GetKeyState(VK_F2) == EKeyState::KEY_HOLD)
    {
        _sound->Play(false);
    }
    if (TInputManager::GetInstance().GetKeyState(VK_F3) == EKeyState::KEY_HOLD)
    {
        _sound->Stop();
    }
    if (TInputManager::GetInstance().GetKeyState(VK_F4) == EKeyState::KEY_HOLD)
    {
        _sound->Pause();
    }
    if (TInputManager::GetInstance().GetKeyState(VK_F5) == EKeyState::KEY_HOLD)
    {
        _sound->Continue();
    }
    if (TInputManager::GetInstance().GetKeyState(VK_F6) == EKeyState::KEY_HOLD)
    {
        check = false;
    }
    _sound->Frame();

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

    TInputManager::GetInstance().Render();

    SoundManager::GetInstance().Render();
    _sound->Render();

    return true;
}

bool UtilityTestWindow::Release()
{
    TBasicWindow::Release();

    _timer.Release();

    TInputManager::GetInstance().Release();

    SoundManager::GetInstance().Release();
    _sound->Release();

    return true;
}
