#include "TCore.h"
#include "TInputManager.h"
#include <string>
#include "TTextManager.h"

TCore* TCore::_instance = nullptr;

TCore& TCore::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new TCore();
    }
    return *_instance;
}

void TCore::Set(HWND hWnd, IDXGISwapChain* swapChain)
{
    _hWnd = hWnd;
    _swapChain = swapChain;
}

bool TCore::Init()
{
    TInputManager::GetInstance().Set(_hWnd);
    TInputManager::GetInstance().Init();
    TTextManager::GetInstance().Set(_swapChain);
    TTextManager::GetInstance().Init();

    _timer.Init();

    return true;
}

bool TCore::Frame()
{
    TInputManager::GetInstance().Frame();
    _timer.Frame();

    return true;
}

bool TCore::Render()
{
    TTextManager::GetInstance().Render();

    return true;
}

bool TCore::Release()
{
    return true;
}
