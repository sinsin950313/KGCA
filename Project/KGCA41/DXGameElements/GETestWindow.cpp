#include "GETestWindow.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BasicWindow.h"
#include "DXStateManager.h"
#include "Shader.h"

namespace SSB
{
    extern BasicWindow* g_Window;

    bool GETestWindow::Init()
    {
        DXWindow::Init();

        DXStateManager::GetInstance().Init();

        _text = new Text(L"aaa", { 0, 0, 100, 50 });
        _text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        _text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        _text->Init();

        _background = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) }, g_Window->GetClientWidth(), g_Window->GetClientHeight());
        _background->SetTexture(TextureResourceManager::GetInstance().Load(L"KGCABK.bmp", DXStateManager::kDefaultWrapSample));
        _background->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
        _background->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withoutMask", "ps_5_0"));
        _background->GetTexture()->RegisterTexturePartWithCoordinateValue("Background", { 0, 0, 1024, 768 });
        _background->GetTexture()->SetCurrentTexturePart("Background");
        _background->Init();

        _object = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) }, 400, 300);
        _object->SetTexture(TextureResourceManager::GetInstance().Load(L"bitmap1.bmp", DXStateManager::kDefaultWrapSample));
        _object->SetMaskTexture(TextureResourceManager::GetInstance().Load(L"bitmap2.bmp", DXStateManager::kDefaultWrapSample));
        _object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
        _object->GetTexture()->RegisterTexturePartWithRelativeValue("Player", { 91, 2, 39, 59 });
        _object->GetTexture()->SetCurrentTexturePart("Player");
        _object->Init();

        return true;
    }

    bool GETestWindow::Frame()
    {
        DXWindow::Frame();

        _background->Frame();
        _object->Frame();
        _text->Frame();

        return true;
    }

    bool GETestWindow::Release()
    {
        DXWindow::Release();

        _background->Release();
        _object->Release();
        _text->Release();

        TextManager::GetInstance().Release();
        ShaderManager::GetInstance().Release();
        TextureResourceManager::GetInstance().Release();
        DXStateManager::GetInstance().Release();

        return true;
    }

    bool GETestWindow::PreRender()
    {
        DXWindow::PreRender();

        DXWindow::AddDrawable(_background);
        DXWindow::AddDrawable(_object);
        DXWindow::AddTextable(_text);

        return true;
    }

    bool GETestWindow::MainRender()
    {
        GetDeviceContext()->RSSetState(DXStateManager::GetInstance().GetRasterizerState(DXStateManager::kDefaultSolidRasterizer));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
        DXWindow::MainRender();

        GetDeviceContext()->RSSetState(DXStateManager::GetInstance().GetRasterizerState(DXStateManager::kDefaultWireFrameRasterizer));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WireFrame", "ps_5_0"));
        DXWindow::MainRender();

        return true;
    }

    bool GETestWindow::PostRender()
    {
        DXWindow::PostRender();
        return true;
    }
}
