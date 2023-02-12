#include "FBXLoaderTest.h"
#include "InputManager.h"
#include "DXStateManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

SSB::FBXLoaderTest::~FBXLoaderTest()
{
	Release();
}

bool SSB::FBXLoaderTest::Init()
{
	DXWindow::Init();

	_loader = new FBXLoader();

	_loader->Init();
	DXObject* box = _loader->Load("box.FBX");
	box->Init();
	_objectList.push_back(box);

	_loader->Init();
	DXObject* multiCameras = _loader->Load("MultiCameras.FBX");
	multiCameras->Init();
	_objectList.push_back(multiCameras);

	_loader->Init();
	DXObject* ship = _loader->Load("ship.FBX");
	ship->Init();
	_objectList.push_back(ship);

	_loader->Init();
	DXObject* man1 = _loader->Load("Man.FBX");
	man1->Init();
	man1->UpdateCurrentAnimation("Take 001");
	_objectList.push_back(man1);

	_loader->Init();
	DXObject* man = _loader->Load("Man.FBX", "Man.FBXScript");
	man->Init();
	man->UpdateCurrentAnimation("Walk");
	_objectList.push_back(man);

	_loader->Init();
	DXObject* turret = _loader->Load("Turret_Deploy1.FBX");
	turret->Init();
	turret->UpdateCurrentAnimation("Take 001");
	_objectList.push_back(turret);

	_loader->Init();
	DXObject* swat1 = _loader->Load("Swat.FBX", std::vector<std::string>{ "Swat@walking_backwards.fbx", "Swat@strafe_2.fbx", "Swat@strafe.fbx" });
	swat1->Init();
	swat1->UpdateCurrentAnimation("mixamo.com");
	_objectList.push_back(swat1);

	_loader->Init();
	DXObject* swat = _loader->Load("Swat.FBX", std::vector<std::string>{ "Swat@walking_backwards.fbx", "Swat@strafe_2.fbx", "Swat@strafe.fbx"}, "Swat.FBXScript");
	swat->Init();
	swat->UpdateCurrentAnimation("strafe_2");
	_objectList.push_back(swat);

	_camera = new ModelViewCamera();
	//_camera->SetTarget(_loader->_rootObject);
	_camera = new DebugCamera();
	ChangeMainCamera(_camera);
	GetMainCamera()->Move({0, 0, -10});

	return false;
}

bool SSB::FBXLoaderTest::Frame()
{
	InputManager::GetInstance().Frame();

	DXWindow::Frame();

	for (auto object : _objectList)
	{
		object->Frame();
	}

	return false;
}

bool SSB::FBXLoaderTest::Release()
{
	for (auto object : _objectList)
	{
		object->Release();
		delete object;
	}
	_objectList.clear();

	if (_camera)
	{
		_camera->Release();
		delete _camera;
		_camera = nullptr;
	}

	if (_loader)
	{
		_loader->Release();
		delete _loader;
		_loader = nullptr;
	}

	DXWindow::Release();

	return true;
}

bool SSB::FBXLoaderTest::PreRender()
{
	DXWindow::PreRender();

	for (auto object : _objectList)
	{
		object->Render();
	}

	return true;
}
