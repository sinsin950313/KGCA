#include "GETestWindow.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "BasicWindow.h"
#include "DXStateManager.h"
#include "Shader.h"
#include "DX2DAnimation.h"

namespace SSB
{
    extern BasicWindow* g_Window;

    bool GETestWindow::Init()
    {
        DXWindow::Init();

        DXStateManager::GetInstance().Init();
		InputManager::GetInstance().Set(GetWindowHandle());
        InputManager::GetInstance().Init();

        _text = new Text(L"Text Test", { 0, 0, 100, 30 });
        _text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        _text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        _text->Init();

        _background = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) }, g_Window->GetClientWidth(), g_Window->GetClientHeight());
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"KGCABK.bmp", L"Background", {0, 0, 1024, 768});
        _background->SetSprite(SpriteLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
        _background->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _background->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithoutMask", "ps_5_0"));
        _background->Init();

        _object = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2 - 100), (float)(g_Window->GetClientHeight() / 2 + 100) }, 100, 100);
        SpriteLoader::GetInstance().RegisterSpriteWithRelativeValue(L"bitmap1.bmp", L"Player", {91, 2, 39, 59});
        _object->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        //SpriteLoader::GetInstance().RegisterSpriteWithRelativeValue(L"bitmap1Mask.bmp", L"Player", {91, 2, 39, 59});
        //_object->SetMaskSprite(SpriteLoader::GetInstance().Load(L"bitmap1Mask.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        _object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
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
        SpriteActionLoader::GetInstance().RegisterSpriteActionWithRelativeValue(L"bitmap1.bmp", L"Explosion", sequence);
        _spriteObject->SetSprite(SpriteActionLoader::GetInstance().Load(L"bitmap1.bmp", L"Explosion", DXStateManager::kDefaultWrapSample));
        //SpriteActionLoader::GetInstance().RegisterSpriteActionWithRelativeValue(L"bitmap1Mask.bmp", L"Explosion", sequence);
        //_spriteObject->SetMaskSprite(SpriteActionLoader::GetInstance().Load(L"bitmap1Mask.bmp", L"Explosion", DXStateManager::kDefaultWrapSample));
        _spriteObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _spriteObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
        _spriteObject->Init();

        _objectWithFile = new DX2DObject({ (float)(g_Window->GetClientWidth() / 2 + 100), (float)(g_Window->GetClientHeight() / 2 + 100) }, 100, 100);
        SpriteLoader::GetInstance().RegisterSpriteFromFile(L"bitmap1.bmp", L"bitmap1");
        _objectWithFile->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        //SpriteLoader::GetInstance().RegisterSpriteWithRelativeValue(L"bitmap1Mask.bmp", L"Player", {91, 2, 39, 59});
        //_objectWithFile->SetMaskSprite(SpriteLoader::GetInstance().Load(L"bitmap1Mask.bmp", L"Player", DXStateManager::kDefaultWrapSample));
        _objectWithFile->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _objectWithFile->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
        _objectWithFile->Init();

        _spriteObjectWithFile = new DX2DObject({200, 300}, 30, 30);
        SpriteActionLoader::GetInstance().RegisterSpriteActionFromFile(L"bitmap1.bmp", L"bitmap1");
        SpriteActionLoader::GetInstance().RegisterSpriteActionFromFile(L"bitmap1.bmp", L"bitmap1");
        _spriteObjectWithFile->SetSprite(SpriteActionLoader::GetInstance().Load(L"bitmap1.bmp", L"rtExplosion", DXStateManager::kDefaultWrapSample));
        _spriteObjectWithFile->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _spriteObjectWithFile->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
        _spriteObjectWithFile->Init();

        _animationObject = new DX2DObject({ 300, 300 }, 30, 30);
        DX2DAnimation* animation = new DX2DAnimation(TextureResourceManager::GetInstance().Load(L"FA-18 Super Hornet.bmp"));
        SpriteAction* sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"Straight", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(true);
        animation->RegisterState("Straight", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"PostStall", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(500);
        animation->RegisterState("PostStall", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"Left", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(true);
        ((SpriteAction*)sprite)->SetInterval(100);
        animation->RegisterState("Left", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"Right", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(true);
        ((SpriteAction*)sprite)->SetInterval(100);
        animation->RegisterState("Right", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"TopRight", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(100);
        animation->RegisterState("TopRight", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"TopLeft", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(100);
        animation->RegisterState("TopLeft", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"BottomLeft", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(1000);
        animation->RegisterState("BottomLeft", sprite);
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"BottomRight", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(1000);
        animation->RegisterState("BottomRight", sprite);
        animation->SetCurrentState("PostStall");
        _animationObject->SetSprite(animation);
        _animationObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _animationObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FA-18 Super Hornet PixelShader.hlsl", "Main", "ps_5_0"));
        _animationObject->Init();

        _textUI = new TextUI(L"Font.png");
        _textUI->SetCenter({ 400, 50 });
        _textUI->SetText("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:");
        //_textUI->Init();

        _dialog = new DX2DObject({ 400, 300 }, 200, 300);
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"Dialog.png", L"Dialog", { 0, 0, 2419, 3000 });
        _dialog->SetSprite(SpriteLoader::GetInstance().Load(L"Dialog.png", L"Dialog", DXStateManager::kDefaultWrapSample));
        _dialog->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _dialog->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithoutMask", "ps_5_0"));
        class TestButtonFunctor : public ButtonFunctor
        {
        public:
            void operator()() override
            {
                OutputDebugString(L"Button Action!");
            }
        };
        _button = new Button(new TestButtonFunctor, { 0, 130 }, 50, 30);
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonNormal.png", L"Normal", { 0, 0, 306, 196 });
        _button->RegisterButton("Normal", SpriteLoader::GetInstance().Load(L"DefaultButtonNormal.png", L"Normal", DXStateManager::kDefaultWrapSample));
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonHover.png", L"Hover", { 0, 0, 306, 196 });
        _button->RegisterButton("Hover", SpriteLoader::GetInstance().Load(L"DefaultButtonHover.png", L"Hover", DXStateManager::kDefaultWrapSample));
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonPush.png", L"Push", { 0, 0, 306, 196 });
        _button->RegisterButton("Push", SpriteLoader::GetInstance().Load(L"DefaultButtonPush.png", L"Push", DXStateManager::kDefaultWrapSample));
        _button->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _button->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithoutMask", "ps_5_0"));
        _dialog->AddChild(_button);

        _dialog->AddChild(_textUI);
        _dialog->Init();

        return true;
    }

    bool GETestWindow::Frame()
    {
        DXWindow::Frame();
        InputManager::GetInstance().Frame();

        _background->Frame();
        _object->Frame();
        _spriteObject->Frame();
        _objectWithFile->Frame();
        _spriteObjectWithFile->Frame();
        _animationObject->Frame();
        //_button->Frame();
        _textUI->Frame();
        _text->Frame();
        _dialog->Move({ _dialog->GetCenter().x + 0.01f, _dialog->GetCenter().y + 0.01f });
        _dialog->RotateDegree(0.1f);
        _dialog->Frame();

        return true;
    }

    bool GETestWindow::Release()
    {
        DXWindow::Release();
        InputManager::GetInstance().Release();

        _background->Release();
        _object->Release();
        _spriteObject->Release();
        _objectWithFile->Release();
        _spriteObjectWithFile->Release();
        _animationObject->Release();
        //_button->Release();
        _textUI->Release();
        _text->Release();
        _dialog->Release();

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
        DXWindow::AddDrawable(_objectWithFile);
        DXWindow::AddDrawable(_spriteObjectWithFile);
        DXWindow::AddDrawable(_animationObject);
        //DXWindow::AddDrawable(_button);
        DXWindow::AddDrawable(_textUI);
        DXWindow::AddTextable(_text);
        _dialog->Render();

        return true;
    }

    bool GETestWindow::MainRender()
    {
        GetDeviceContext()->RSSetState(DXStateManager::GetInstance().GetRasterizerState(DXStateManager::kDefaultSolidRasterizer));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
        _objectWithFile->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
        DXWindow::MainRender();

        GetDeviceContext()->RSSetState(DXStateManager::GetInstance().GetRasterizerState(DXStateManager::kDefaultWireFrameRasterizer));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WireFrame", "ps_5_0"));
        _objectWithFile->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WireFrame", "ps_5_0"));
        DXWindow::MainRender();

        return true;
    }

    bool GETestWindow::PostRender()
    {
        DXWindow::PostRender();
        return true;
    }
}
