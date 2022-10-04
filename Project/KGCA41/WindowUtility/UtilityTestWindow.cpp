#include "UtilityTestWindow.h"
#include "InputManager.h"
#include <string>
#include "SoundManager.h"
#include "Sound.h"

namespace SSB
{
    bool UtilityTestWindow::Init()
    {
        BasicWindow::Init();

        _timer.Init();
        InputManager::GetInstance().Init();
        SoundManager::GetInstance().Init();
        _sound = SoundManager::GetInstance().Load(L"MyLove.mp3");
        _sound->Init();

        return true;
    }

    bool UtilityTestWindow::Frame()
    {
        BasicWindow::Frame();

        static bool check = false;

        _timer.Frame();
        InputManager::GetInstance().Frame();
        SoundManager::GetInstance().Frame();
        if (InputManager::GetInstance().GetKeyState(VK_F1) == EKeyState::KEY_HOLD)
        {
            //_sound1->PlayInstance();
            if (!check)
            {
                SoundManager::GetInstance().PlayInstanceSound(L"GunShot.mp3");
                check = true;
            }
        }
        if (InputManager::GetInstance().GetKeyState(VK_F2) == EKeyState::KEY_HOLD)
        {
            _sound->Play(false);
        }
        if (InputManager::GetInstance().GetKeyState(VK_F3) == EKeyState::KEY_HOLD)
        {
            _sound->Stop();
        }
        if (InputManager::GetInstance().GetKeyState(VK_F4) == EKeyState::KEY_HOLD)
        {
            _sound->Pause();
        }
        if (InputManager::GetInstance().GetKeyState(VK_F5) == EKeyState::KEY_HOLD)
        {
            _sound->Continue();
        }
        if (InputManager::GetInstance().GetKeyState(VK_F6) == EKeyState::KEY_HOLD)
        {
            check = false;
        }
        _sound->Frame();

        return true;
    }

    bool UtilityTestWindow::Render()
    {
        BasicWindow::Render();

        std::wstring str = std::to_wstring(_timer.GetElapseTime() / 1000.0f).c_str();
        str += L"\n";
        OutputDebugString(str.c_str());

        if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
        {
            OutputDebugString(L"W Key Hold");
        }
        if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
        {
            OutputDebugString(L"A Key Hold");
        }
        if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
        {
            OutputDebugString(L"S Key Hold");
        }
        if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
        {
            OutputDebugString(L"D Key Hold");
        }

        InputManager::GetInstance().Render();

        SoundManager::GetInstance().Render();
        _sound->Render();

        return true;
    }

    bool UtilityTestWindow::Release()
    {
        BasicWindow::Release();

        _timer.Release();

        InputManager::GetInstance().Release();

        if (_sound != nullptr)
        {
            _sound->Release();
        }
        SoundManager::GetInstance().Release();

        return true;
    }
}
