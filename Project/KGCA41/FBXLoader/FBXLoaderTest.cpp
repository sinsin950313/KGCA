#include "FBXLoaderTest.h"
#include "InputManager.h"

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
	_loader->SetFileName("../../Resource/FBX/Man.FBX");
	_loader->Init();

	_loader1 = new FBXLoader();
	_loader1->SetFileName("../../Resource/FBX/Turret_Deploy1.FBX");
	_loader1->Init();

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
	_loader->Frame();
	_loader1->Frame();
	return false;
}

bool SSB::FBXLoaderTest::Release()
{
	DXWindow::Release();
	_loader->Release();
	_loader1->Release();
	return false;
}

bool SSB::FBXLoaderTest::PreRender()
{
	DXWindow::PreRender();
	_loader->Render();
	_loader1->Render();
	return true;
}
