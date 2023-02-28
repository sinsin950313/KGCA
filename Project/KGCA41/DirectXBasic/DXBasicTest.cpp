#include "DXBasicTest.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "InputManager.h"
#include "Map.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

    DXBasicTest::~DXBasicTest()
    {
        Release();
    }
    bool DXBasicTest::Init()
    {
        DXWindow::Init();
        InputManager::GetInstance().Set(g_dxWindow->GetWindowHandle());

		_timer = new Timer();
		_timer->Init();
		_timer->Start();
		_beforeTime = _timer->GetElapseTime();
		_frames = 0;
		_fps = 0.0f;

        {
            MeshInterface* box = new Box;
            box->Init();

            Model* model = new Model;
            model->Initialize_RegisterMesh(0, box);
            model->Init();
            model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"BoxMeshShader.hlsl", "VSMain", "vs_5_0"));
            model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"BoxMeshShader.hlsl", "PSMain", "ps_5_0"));

            _object = new DXObject();
            _object->Init();
            _object->SetModel(model);
            _object->Move({ 0, 5, 0 });
        }

        //{
        //    _objectBack = new DXObject();
        //    Model* model = new Model;
        //    model->RegisterMesh(0, new Box);
        //    model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
        //    model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "FormedMain", "ps_5_0"));
        //    _objectBack->SetModel(model);
        //    _objectBack->Init();
        //    _objectBack->Move({ 0, 0, 5 });
        //}

        //{
        //    _terrain = new Map();
        //    SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"KGCABK.bmp", L"Background", { 0, 0, 1024, 768 });
        //    _terrain->SetSprite(SpriteLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
        //    _terrain->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
        //    _terrain->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader.hlsl", "Main", "ps_5_0"));
        //    //_terrain->SetHeightMap(L"heightMap513.bmp");
        //    _terrain->SetSize(257, 257);
        //    _terrain->SetMaxLayerLevel(1);
        //    _terrain->Init();
        //    _terrain->SetPosition({ 0, 0, 0 });
        //}

        _dCamera = new DebugCamera();
        _dCamera->Init();

        //_mCamera = new ModelViewCamera();
        //_mCamera->Init();
        //_mCamera->SetTarget(_object);
        ChangeMainCamera(_dCamera);
        
        //HVector4 pos = _object->GetPosition();
        //_object->SetPosition({ pos.GetX(), _terrain->GetHeight(pos.GetX(), pos.GetZ()), pos.GetZ() });
        //GetMainCamera()->Move(_object->GetPosition());

        return false;
    }

    bool SSB::DXBasicTest::Frame()
    {
        DXWindow::Frame();
        InputManager::GetInstance().Frame();

        //_mCamera->Frame();

		_timer->Frame();
		++_frames;
		if (1000.0f < _timer->GetElapseTime() - _beforeTime)
		{
			_fps = _frames * 1000.0f / (_timer->GetElapseTime() - _beforeTime);
			_frames = 0;
			_beforeTime = _timer->GetElapseTime();
		OutputDebugString((L"Time : " + std::to_wstring(_timer->GetElapseTime() / 1000.0f) + L" FPS : " + std::to_wstring(_fps) + L"\n").c_str());
		}
        _object->Frame();
        //_terrain->Frame();
        //_objectBack->Rotate(0.001f, 0, 0);
        //_objectBack->Frame();

        return false;
    }

    bool SSB::DXBasicTest::Release()
    {
        if (_object)
        {
            _object->Release();
            delete _object;
            _object = nullptr;
        }
        //if (_objectBack)
        //{
        //    _objectBack->Release();
        //    delete _objectBack;
        //    _objectBack = nullptr;
        //}
        //if (_terrain)
        //{
        //    _terrain->Release();
        //    delete _terrain;
        //    _terrain = nullptr;
        ////}
        if(_dCamera)
        {
            _dCamera->Release();
            delete _dCamera;
            _dCamera = nullptr;
        }
        //if (_mCamera)
        //{
        //    _mCamera->Release();
        //    delete _mCamera;
        //    _mCamera = nullptr;
        //}
        if (_timer)
        {
            _timer->Release();
            delete _timer;
            _timer = nullptr;
        }

        DXWindow::Release();

        return true;
    }

    bool SSB::DXBasicTest::PreRender()
    {
        DXWindow::PreRender();
        //_mCamera->Render();
        _object->Render();
        //_terrain->Render();
        //_objectBack->Render();
        return true;
    }
}
