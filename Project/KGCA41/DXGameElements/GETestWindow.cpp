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
        TextureLoader::GetInstance().RegisterTexturePartWithCoordinateValue(L"KGCABK.bmp", L"Background", {0, 0, 1024, 768});
        _background->SetTexture(TextureLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
        _background->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
        _background->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withoutMask", "ps_5_0"));
        _background->Init();

        _object = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) }, 400, 300);
        TextureLoader::GetInstance().RegisterTexturePartWithRelativeValue(L"bitmap1.bmp", L"Player", {91, 2, 39, 59});
        _object->SetTexture(TextureLoader::GetInstance().Load(L"bitmap1.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        TextureLoader::GetInstance().RegisterTexturePartWithRelativeValue(L"bitmap2.bmp", L"Player", {91, 2, 39, 59});
        _object->SetMaskTexture(TextureLoader::GetInstance().Load(L"bitmap2.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        _object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
        _object->Init();

        _spriteObject = new DX2DObject({100, 200}, 30, 30);
        std::vector<TexturePartRelative> sequence;
        sequence.push_back(TexturePartRelative{ 1, 142, 41, 41 });
        sequence.push_back(TexturePartRelative{ 43, 142, 38, 43 });
        sequence.push_back(TexturePartRelative{ 82, 142, 36, 43 });
        sequence.push_back(TexturePartRelative{ 119, 142, 35, 45 });
        sequence.push_back(TexturePartRelative{ 155, 142, 34, 46 });
        sequence.push_back(TexturePartRelative{ 190, 142, 34, 41 });
        sequence.push_back(TexturePartRelative{ 225, 142, 33, 38 });
        sequence.push_back(TexturePartRelative{ 259, 142, 31, 36 });
        sequence.push_back(TexturePartRelative{ 291, 142, 29, 32 });
        sequence.push_back(TexturePartRelative{ 321, 142, 27, 26 });
        sequence.push_back(TexturePartRelative{ 349, 142, 24, 24 });
        sequence.push_back(TexturePartRelative{ 374, 142, 22, 18 });
        SpriteLoader::GetInstance().RegisterSpriteWithRelativeValue(L"bitmap1.bmp", L"Explosion", sequence);
        _spriteObject->SetTexture(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"Explosion", DXStateManager::kDefaultWrapSample));
        _spriteObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
        _spriteObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
        _spriteObject->Init();

        return true;
    }

    bool GETestWindow::Frame()
    {
        DXWindow::Frame();

        _background->Frame();
        _object->Frame();
        _spriteObject->Frame();
        _text->Frame();

        return true;
    }

    bool GETestWindow::Release()
    {
        DXWindow::Release();

        _background->Release();
        _object->Release();
        _spriteObject->Release();
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
        DXWindow::AddDrawable(_spriteObject);
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
