#include "DXUtilityTestWindow.h"

bool DXUtilityTestWindow::Init()
{
    TDXWindow::Init();

    TCore::GetInstance().Set(GetWindowHandle(), GetSwapChain());
    TCore::GetInstance().Init();

    return true;
}

bool DXUtilityTestWindow::Frame()
{
    TDXWindow::Frame();

    TCore::GetInstance().Frame();

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
