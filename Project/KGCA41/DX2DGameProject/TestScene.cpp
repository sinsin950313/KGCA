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
	}

	bool TestScene::Init()
	{
		SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"KGCABK.bmp", L"Background", {0, 0, 1024, 768});
		_map->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"KGCABK.bmp", L"Background", DXStateManager::kDefaultWrapSample));
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

		_camera->Init();

		_map->SetPlayer(_playerObject);

        _text = new Text(L"", { 0, 0, 100, 50 });
        _text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"����", L"ko-kr", 30));
        _text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
        _text->Init();

		return true;
	}

	bool TestScene::Frame()
	{
		_map->Frame();

		//for (auto object : _objects)
		//{
		//	object->Frame();
		//}

		_playerController->Frame();
		//_playerObject->Frame();
		//_enemyrObject->Move(_playerObject->GetCenter().Get(0), _playerObject->GetCenter().Get(1) + 20);
		_enemyController->Frame();

		_camera->ConnectTo(_playerObject);
		_camera->Frame();

		//collide check
		if (_map->IsHit(_playerObject, _enemyObject))
		{
			_enemyObject->Targeted();
			if (_enemyObject->IsHit())
			{
				++_hitCount;
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

		_text->Release();

		return true;
	}

	bool TestScene::Render()
	{
		SetDisplayPosition(_map);
		_map->Render();

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

		g_dxWindow->AddTextable(_text);

		return true;
	}

	void TestScene::SetDisplayPosition(DX2DInGameObject* object)
	{
		_camera->MontageForFilm(object);
	}

	void TestScene::SetDisplayPosition(DX2DMapObject* map)
	{
		_camera->MontageForFilm(map);
	}
}
