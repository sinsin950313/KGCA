#include "DXBasicTest.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "TextureManager.h"
#include "InputManager.h"

namespace SSB
{
    bool SSB::DXBasicTest::Init()
    {
        DXWindow::Init();
        ShaderManager::GetInstance().Init();
        DXStateManager::GetInstance().Init();
        TextureResourceManager::GetInstance().Init();
        SpriteLoader::GetInstance().Init();
        InputManager::GetInstance().Set(g_dxWindow->GetWindowHandle());
        InputManager::GetInstance().Init();

		_timer = new Timer();
		_timer->Init();
		_timer->Start();
		_beforeTime = _timer->GetElapseTime();
		_frames = 0;
		_fps = 0.0f;
        
        _object = new DXObject();
        _object->SetModel(new Box);
        _object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
        _object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "Main", "ps_5_0"));
        _object->Init();
        _object->Move({ 0, 10, 0 });

        _terrain = new DXObject();
        Terrain* terrain = new Terrain;
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"KGCABK.bmp", L"Background", { 0, 0, 1024, 768 });
        terrain->SetSprite(SpriteLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
        _terrain->SetModel(terrain);
        _terrain->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
        _terrain->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader.hlsl", "Main", "ps_5_0"));
        _terrain->Init();

        _dCamera = new DebugCamera();
        _mCamera = new ModelViewCamera();
        _mCamera->SetTarget(_object);
        ChangeMainCamera(_mCamera);
        GetMainCamera()->Move({ 0, 5, -5 });

        return false;
    }

    bool SSB::DXBasicTest::Frame()
    {
        DXWindow::Frame();
        InputManager::GetInstance().Frame();
        //GetMainCamera()->Frame();

		_timer->Frame();
		++_frames;
		if (1000.0f < _timer->GetElapseTime() - _beforeTime)
		{
			_fps = _frames * 1000.0f / (_timer->GetElapseTime() - _beforeTime);
			_frames = 0;
			_beforeTime = _timer->GetElapseTime();
		//OutputDebugString((L"Time : " + std::to_wstring(_timer->GetElapseTime() / 1000.0f) + L" FPS : " + std::to_wstring(_fps) + L"\n").c_str());
		}
        //_object->Rotate(0, 0.001f);
        _object->Frame();
        _terrain->Frame();

        return false;
    }

    bool SSB::DXBasicTest::Release()
    {
        DXWindow::Release();
        return false;
    }

    bool SSB::DXBasicTest::PreRender()
    {
        DXWindow::PreRender();
        _object->Render();
        _terrain->Render();
        return true;
    }
}
