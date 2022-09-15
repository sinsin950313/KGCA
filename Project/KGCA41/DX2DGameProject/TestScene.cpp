#include "TestScene.h"
#include "DX2DMapObject.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "TInputManager.h"
#include "TDXWindow.h"
#include "DX2DGameObjectFactory.h"

extern TDXWindow* g_dxWindow;

TestScene::TestScene()
{
	_map = new DX2DMapObject(Vector2D(Vector2DData{ 0, 0 }), 300, 300);

	_factory = new DX2DGameObjectFactory;
	_factory->SetMapObject(_map);

	//_objects.push_back(_factory->CreateStaticGameObject(Position2D{ 20, 20 }, 10, 10, 1));
	//_objects.push_back(_factory->CreateDynamicGameObject(Position2D{ -20, 20 }, 10, 10, 1));

	_player = _factory->CreateDynamicGameObject(Position2D{ 0, 0, }, 10, 10, 1);

	_camera = new DX2DCamera(Vector2D(Vector2DData{ 0, 0 }), 100, 100);
}

bool TestScene::Init()
{
	_map->Init();
	for (auto object : _objects)
	{
		object->Init();
	}
	_player->Init();
	_camera->Init();

	return true;
}

bool TestScene::Frame()
{
	GameLogic();

	_map->Frame();
	_map->GetDXObject()->Scroll(_dx, _dy);

	for (auto object : _objects)
	{
		object->Frame();
	}
	_player->Frame();

	_camera->ConnectTo(_player);
	_camera->Frame();

	return true;
}

bool TestScene::Release()
{
	_map->Release();
	delete _map;
	_map = nullptr;

	for (auto object : _objects)
	{
		object->Release();
		delete object;
	}
	_objects.clear();

	_player->Release();
	delete _player;
	_player = nullptr;

	_camera->Release();
	delete _camera;
	_camera = nullptr;

	return true;
}

bool TestScene::Render()
{
	SetDisplayPosition(_map);
	g_dxWindow->AddDrawable(_map->GetDXObject());

	auto objectList = _map->GetCollideObjectList(_camera);
	for (auto object : objectList)
	{
		SetDisplayPosition(object);
		g_dxWindow->AddDrawable(object->GetDXObject());
	}

	SetDisplayPosition(_player);
	g_dxWindow->AddDrawable(_player->GetDXObject());

	return true;
}

void TestScene::GameLogic()
{
	float vel = 0.01f;
	if (TInputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
	{
		_player->Move(_player->GetCenter().Get(0), _player->GetCenter().Get(1) + vel);
		_dy -= vel * vel;
	}
	if (TInputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
	{
		_player->Move(_player->GetCenter().Get(0) - vel, _player->GetCenter().Get(1));
		_dx -= vel * vel;
	}
	if (TInputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
	{
		_player->Move(_player->GetCenter().Get(0), _player->GetCenter().Get(1) - vel);
		_dy += vel * vel;
	}
	if (TInputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
	{
		_player->Move(_player->GetCenter().Get(0) + vel, _player->GetCenter().Get(1));
		_dx += vel * vel;
	}

	if (_map->IsCollide(_player))
	{
		auto collide = _map->GetCollideObjectList(_player);
		std::string count = std::to_string(collide.size());
		std::string hit = "Hit : " + count + "\n";
		OutputDebugStringA(hit.c_str());
	}
}

void TestScene::SetDisplayPosition(DX2DGameObject* object)
{
	_camera->MontageForFilm(object);
}

void TestScene::SetDisplayPosition(DX2DMapObject* map)
{
	_camera->MontageForFilm(map);
}