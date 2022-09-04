#include "DXUtilityTestWindow.h"
#include "TText.h"

bool DXUtilityTestWindow::Init()
{
    TDXWindow::Init();

    TCore::GetInstance().Set(GetWindowHandle(), GetSwapChain());
    TCore::GetInstance().Init();

    _test = new TText(L"abc", RECT{ 0, 0, 100, 100 });
    TTextManager::GetInstance().AddText(_test);

    return true;
}

bool DXUtilityTestWindow::Frame()
{
    TDXWindow::Frame();

    TCore::GetInstance().Frame();
    _test->SetString(std::to_wstring(TCore::GetInstance().GetTimer().GetElapseTime()));

    return true;
}

bool DXUtilityTestWindow::Render()
{
    TDXWindow::Render();
    return true;
}

bool DXUtilityTestWindow::Release()
{
    TDXWindow::Release();

    TCore::GetInstance().Release();

    return true;
}

bool DXUtilityTestWindow::PreRender()
{
    TDXWindow::PreRender();
    return true;
}

bool DXUtilityTestWindow::MainRender()
{
    TDXWindow::MainRender();

    TCore::GetInstance().Render();

    return true;
}

bool DXUtilityTestWindow::PostRender()
{
    TDXWindow::PostRender();
    return true;
}
