#include "DX2DGameProject.h"
#include "DX2DMapObject.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "TInputManager.h"

DX2DGameProject::DX2DGameProject(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow)
{
	_map = new DX2DMapObject();
	_objects.push_back();
	_player = new DX2DGameObject();
	_camera = new DX2DCamera();
}

bool DX2DGameProject::Init()
{
	DXCore::Init();

	_map->Init();
	for (auto object : _objects)
	{
		object->Init();
	}
	_player->Init();
	_camera->Init();

	return true;
}

bool DX2DGameProject::Frame()
{
	DXCore::Frame();

	GameLogic();

	_map->Frame();
	for (auto object : _objects)
	{
		object->Frame();
	}
	_player->Frame();
	_camera->Frame();

	return true;
}

bool DX2DGameProject::Release()
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

	DXCore::Release();

	return true;
}

bool DX2DGameProject::PreRender()
{
	DXCore::PreRender();

	auto objectList = _map->GetCollideObjectList(_camera);
	for (auto object : objectList)
	{
		SetDisplayPosition(object);
		AddDrawable(object->GetDXObject());
	}

	SetDisplayPosition(_player);
	AddDrawable(_player->GetDXObject());

	return true;
}

bool DX2DGameProject::MainRender()
{
	DXCore::MainRender();
	return true;
}

bool DX2DGameProject::PostRender()
{
	DXCore::PostRender();
	return true;
}

void DX2DGameProject::GameLogic()
{
	if (TInputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
	{
		
	}
	if (TInputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
	{
		
	}
	if (TInputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
	{
		
	}
	if (TInputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
	{
		
	}
}

void DX2DGameProject::SetDisplayPosition(DX2DGameObject* object)
{
	Vector2D standard = _camera->GetPhysicsObject()->GetVolume()->GetCenter();
	Vector2D objectPosition = object->GetPhysicsObject()->GetVolume()->GetCenter();
	Vector2D relative = objectPosition - standard;

	Position2D center = _camera->PhysicsToDisplay(relative);

	object->GetDXObject()->SetCenter(center);
}
