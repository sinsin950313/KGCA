#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "DirectXTK.lib")

#include "GETestWindow.h"
#include "TTextManager.h"
#include "TTextureManager.h"
#include "TShaderManager.h"
#include "TBasicWindow.h"

extern TBasicWindow* g_Window;

bool GETestWindow::Init()
{
    TDXWindow::Init();

    _text = new TText(L"aaa", { 0, 0, 100, 50 });
    _text->SetTextFormat(TTextManager::GetInstance().LoadTextFormat(L"���", L"ko-kr", 30));
    _text->SetBrush(TTextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));

    _object = new TDX2DObject({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) }, g_Window->GetClientWidth(), g_Window->GetClientHeight());
    _object->SetTexture(TTextureManager::GetInstance().Load(L"KGCABK.bmp"));
    _object->SetVertexShader(TShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
    _object->SetPixelShader(TShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "main", "ps_5_0"));
    _object->Init();

    return true;
}

bool GETestWindow::Frame()
{
    TDXWindow::Frame();

    _object->Frame();
    _text->Frame();

    return true;
}

bool GETestWindow::Release()
{
    TDXWindow::Release();

    _object->Release();
    _text->Release();

    TTextManager::GetInstance().Release();
    TShaderManager::GetInstance().Release();
    TTextureManager::GetInstance().Release();

    return true;
}

bool GETestWindow::PreRender()
{
    TDXWindow::PreRender();

    TDXWindow::AddDrawable(_object);
    TDXWindow::AddTextable(_text);

    return true;
}

bool GETestWindow::MainRender()
{
    TDXWindow::MainRender();

    return true;
}

bool GETestWindow::PostRender()
{
    TDXWindow::PostRender();
    return true;
}
