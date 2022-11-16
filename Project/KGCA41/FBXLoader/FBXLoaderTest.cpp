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
	InputManager::GetInstance().Init();

	DXWindow::Init();

	//_loader->SetFileName("../../Resource/FBX/box.FBX");
	//_loader->SetFileName("../../Resource/FBX/MultiCameras.FBX");
	//_loader->SetFileName("../../Resource/FBX/ship.FBX");

	_loader = new FBXLoader();

	//_loader->Init();
	//DXObject* man = _loader->Load("../../Resource/FBX/Man.FBX");

	//man->Init();

	//// Easy for Test
	//man->UpdateCurrentAnimation("Take 001");

	//_objectList.push_back(man);

	//_loader->Init();
	//DXObject* turret = _loader->Load("../../Resource/FBX/Turret_Deploy1.FBX");

	//turret->Init();

	//// Easy for Test
	//turret->UpdateCurrentAnimation("Take 001");

	//_objectList.push_back(turret);

	_loader->Init();
	DXObject* swat = _loader->Load("../../Resource/FBX/Swat.FBX", std::vector<std::string>{ "../../Resource/FBX/Swat@walking_backwards.fbx", "../../Resource/FBX/Swat@strafe_2.fbx", "../../Resource/FBX/Swat@strafe.fbx" });
	swat->Init();
	swat->UpdateCurrentAnimation("mixamo.com");
	_objectList.push_back(swat);

	//ModelViewCamera* camera = new ModelViewCamera();
	//camera->SetTarget(_loader->_rootObject);
	DebugCamera* camera = new DebugCamera();
	ChangeMainCamera(camera);
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
	DXWindow::Release();

	for (auto object : _objectList)
	{
		object->Release();
	}

	_loader->Release();

	TextureResourceManager::GetInstance().Release();
	DXStateManager::GetInstance().Release();
	ShaderManager::GetInstance().Release();

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
