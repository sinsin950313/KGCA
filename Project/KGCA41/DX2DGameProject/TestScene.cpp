#include "TestScene.h"
#include "DX2DMapObject.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "InputManager.h"
#include "DXWindow.h"
#include "DX2DGameObjectFactory.h"
#include "TextureManager.h"
#include "DXStateManager.h"
#include "TextManager.h"
#include "DXCore.h"
#include "ShaderManager.h"
#include "SoundManager.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;
	DX2DCamera* g_Camera;
	extern DXCore* g_DXCore;

	TestScene::TestScene()
	{
		_map = new DX2DMapObject(Vector2D(Vector2DData{ 0, 0 }), 300, 300);

		_factory = new DX2DGameObjectFactory;
		_factory->SetMapObject(_map);

		//_objects.push_back(_factory->CreateStaticGameObject(Position2D{ 20, 20 }, 10, 10, 1));
		//_objects.push_back(_factory->CreateDynamicGameObject(Position2D{ -20, 20 }, 10, 10, 1));

		_playerObject = _factory->CreateDynamicGameObject(Position2D{ 0, 0, }, 10, 10, 1);
		_playerController = new PlayerController(_playerObject);

		_enemyObject = _factory->CreateDynamicGameObject(Position2D{ 0, 50, }, 10, 10, 2);
		_enemyController = new EnemyController(_enemyObject);
		_enemyController->SetEnemy(_playerObject);

		_camera = new DX2DCamera(Vector2D(Vector2DData{ 0, 0 }), 100, 100);
		g_Camera = _camera;

		_pool.SetCamera(_camera);

		_cloudManager = new CloudManager;
	}

	bool TestScene::Init()
	{
		_camera->Init();

		_map->Init();

		//for (auto object : _objects)
		//{
		//	object->Init();
		//	//object->GetDXObject()->SetRect("Enemy", {46, 62, 68, 79});
		//}

		//SpriteLoader::GetInstance().RegisterSpriteFromFile(L"bitmap1.bmp", L"bitmap1");
		//_playerObject->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"Player", DXStateManager::kDefaultWrapSample));
		_playerObject->Init();

		//_enemyObject->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"Enemy1", DXStateManager::kDefaultWrapSample));
		_enemyObject->Init();

		_map->SetPlayer(_playerObject);

		_pool.Init();

        _text = new Text(L"", { 0, 0, 100, 50 });
        _text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
        _text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        _text->Init();

		_cloudManager->Init();

		return true;
	}

	bool TestScene::Frame()
	{
		_map->Frame();

		//for (auto object : _objects)
		//{
		//	object->Frame();
		//}

		const float kDefaultSpeed = 0.5f;
		_playerObject->Move(_playerObject->GetCenter().Get(0), _playerObject->GetCenter().Get(1) + kDefaultSpeed);
		_enemyObject->Move(_enemyObject->GetCenter().Get(0), _enemyObject->GetCenter().Get(1) + kDefaultSpeed);

		_playerController->Frame();
		//_playerObject->Frame();
		//_enemyrObject->Move(_playerObject->GetCenter().Get(0), _playerObject->GetCenter().Get(1) + 20);
		_enemyController->Frame();

		_camera->ConnectTo(_playerObject);
		_camera->Frame();

		_pool.Frame();

		//collide check
		if (_map->IsHit(_playerObject, _enemyObject))
		{
			_enemyObject->Targeted();
			if (_enemyObject->IsHit())
			{
				++_hitCount;
				_pool.RunEffect(_enemyObject->GetCenter());
			}
		}
		else
		{
			_enemyObject->UnTargeted();
		}
		
		if (_map->IsHit(_enemyObject, _playerObject))
		{
			_playerObject->Targeted();
			if (_playerObject->IsHit())
			{
				++_hittedCount;
				_pool.RunEffect(_playerObject->GetCenter());
			}
		}
		else
		{
			_playerObject->UnTargeted();
		}

		//static DWORD timeStamp = g_DXCore->GetGlobalTime();
		//if (1000 < g_DXCore->GetGlobalTime() - timeStamp)
		//{
		//	OutputDebugString((std::to_wstring(_hitCount) + L", " + std::to_wstring(_hittedCount) + L"\n").c_str());
		//	timeStamp = g_DXCore->GetGlobalTime();
		//}

		_text->SetString(std::to_wstring(_enemyObject->GetCurrentMapLayer()));
		_text->Frame();

		_cloudManager->Frame();

		return true;
	}

	bool TestScene::Release()
	{
		_map->Release();
		delete _map;
		_map = nullptr;

		//for (auto object : _objects)
		//{
		//	object->Release();
		//	delete object;
		//}
		//_objects.clear();

		_playerObject->Release();
		delete _playerObject;
		_playerObject = nullptr;

		_enemyObject->Release();
		delete _enemyObject;
		_enemyObject = nullptr;

		_camera->Release();
		delete _camera;
		_camera = nullptr;

		_pool.Release();

		_text->Release();

		_cloudManager->Release();

		return true;
	}

	bool TestScene::Render()
	{
		//SetDisplayPosition(_map);
		_map->Render();

		_cloudManager->Render();

		auto objectList = _map->GetCollideObjectList(_camera);
		for (auto object : objectList)
		{
			SetDisplayPosition(object);
			object->Render();
		}

		//SetDisplayPosition(_playerObject);
		//g_dxWindow->AddDrawable(_playerObject->GetDXObject());

		//SetDisplayPosition(_enemyrObject);
		//g_dxWindow->AddDrawable(_enemyrObject->GetDXObject());

		_pool.Render();

		//g_dxWindow->AddTextable(_text);
		_text->Render();

		return true;
	}

	void TestScene::SetDisplayPosition(DX2DGameObject* object)
	{
		_camera->MontageForFilm(object);
	}

	//void TestScene::SetDisplayPosition(DX2DMapObject* map)
	//{
	//	_camera->MontageForFilm(map);
	//}

	TestScene::HitEffectMemoryPool::HitEffectMemoryPool()
	{
	}

	TestScene::HitEffectMemoryPool::~HitEffectMemoryPool()
	{
		Release();
	}

	void TestScene::HitEffectMemoryPool::RequireMemory(int newCount)
	{
		_effectList.resize(newCount);

		for (int i = _effectCount; i < newCount; ++i)
		{
			DX2DGameObject* effect = new DX2DGameObject({ 0, 0 }, 5, 5, 0);
			effect->GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
			effect->GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));

			SpriteLoader::GetInstance().RegisterSpriteFromFile(L"Effect.bmp", L"Effect");
			SpriteAction* action = SpriteActionLoader::GetInstance().Load(L"Effect.bmp", L"Bomb", DXStateManager::kDefaultWrapSample);
			action->SetInterval(300);
			action->SetLoop(false);
			action->Off();
			effect->GetDXObject()->SetSprite(action);
			effect->Init();

			_effectList[i] = effect;
		}
		_effectCount = newCount;
	}

	void TestScene::HitEffectMemoryPool::SetCamera(DX2DCamera* camera)
	{
		_camera = camera;
	}

	void TestScene::HitEffectMemoryPool::RunEffect(Vector2D pos)
	{
		for (auto effect : _effectList)
		{
			SpriteAction* action = (SpriteAction*)effect->GetDXObject()->GetSprite();
			if (action->IsFinished())
			{
				effect->GetPhysicsObject()->GetVolume()->Reposition(pos);
				action->ResetAction();
				SoundManager::GetInstance().PlayInstanceSound(L"20mm effect.mp3");
				return;
			}
		}
		RequireMemory(_effectCount + 10);
		RunEffect(pos);
	}

	bool TestScene::HitEffectMemoryPool::Init()
	{
		RequireMemory(_initialEffectCount);

		return true;
	}

	bool TestScene::HitEffectMemoryPool::Frame()
	{
		for (auto effect : _effectList)
		{
			_camera->MontageForFilm(effect);
			effect->Frame();
		}
		return true;
	}

	bool TestScene::HitEffectMemoryPool::Render()
	{
		for (auto effect : _effectList)
		{
			SpriteAction* action = (SpriteAction*)effect->GetDXObject()->GetSprite();
			if (!action->IsFinished())
			{
				effect->Render();
			}
		}
		return true;
	}

	bool TestScene::HitEffectMemoryPool::Release()
	{
		for (auto effect : _effectList)
		{
			effect->Release();
			delete effect;
		}
		_effectList.clear();

		_camera = nullptr;

		return true;
	}

	DX2DGameObject* TestScene::CloudManager::GetCloud()
	{
		for (auto cloud : _clouds)
		{
			if (cloud->GetCenter().Get(1) < g_Camera->GetCenter().Get(1) - 100)
			{
				return cloud;
			}
		}
		return nullptr;
	}

	bool TestScene::CloudManager::Init()
	{
		_lastTime = g_DXCore->GetGlobalTime();

		_clouds.resize(5);
		for (int i = 0; i < 5; ++i)
		{
			DX2DGameObject* cloud = new DX2DGameObject({ 0, -500 }, rand() % 20 + 10, rand() % 20 + 10, 0);
			cloud->GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
			cloud->GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"CloudPixelShader.hlsl", "Main", "ps_5_0"));

			SpriteLoader::GetInstance().RegisterSpriteFromFile(L"cloud.bmp", L"cloud");
			Sprite* sprite = SpriteLoader::GetInstance().Load(L"cloud.bmp", L"cloud1", DXStateManager::kDefaultWrapSample);
			cloud->GetDXObject()->SetSprite(sprite);
			cloud->Init();

			_clouds[i] = cloud;
		}
		return true;
	}

	bool TestScene::CloudManager::Frame()
	{
		if (_lastTime + _interval < g_DXCore->GetGlobalTime())
		{
			if (rand() % 3 == 0)
			{
				auto cloud = GetCloud();
				if (cloud != nullptr)
				{
					std::wstring cloudName = L"cloud" + std::to_wstring(rand() % 3 + 1);
					cloud->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"cloud.bmp", cloudName, DXStateManager::kDefaultWrapSample));
					cloud->Move(g_Camera->GetCenter().Get(0) + (rand() % 100 - 50), g_Camera->GetCenter().Get(1) + 100);
				}
			}
			_lastTime = g_DXCore->GetGlobalTime();
		}

		for (auto cloud : _clouds)
		{
			g_Camera->MontageForFilm(cloud);
			cloud->Frame();
		}
		return true;
	}

	bool TestScene::CloudManager::Render()
	{
		for (auto cloud : _clouds)
		{
			cloud->Render();
		}

		return true;
	}

	bool TestScene::CloudManager::Release()
	{
		for (auto cloud : _clouds)
		{
			cloud->Release();
		}

		return true;
	}
}
