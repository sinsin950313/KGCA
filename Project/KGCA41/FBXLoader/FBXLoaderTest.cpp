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
	_loader = new FBXLoader();
	//_loader->SetFileName("../../Resource/FBX/box.FBX");
	//_loader->SetFileName("../../Resource/FBX/MultiCameras.FBX");
	//_loader->SetFileName("../../Resource/FBX/ship.FBX");
	//_loader->SetFileName("../../Resource/FBX/Turret_Deploy1.FBX");
	_loader->SetFileName("../../Resource/FBX/Man.FBX");
	_loader->Init();

	ModelViewCamera* camera = new ModelViewCamera();
	camera->SetTarget(_loader->_rootObject);
	//DebugCamera* camera = new DebugCamera();
	ChangeMainCamera(camera);
	GetMainCamera()->Move({0, 0, -4});

	return false;
}

bool SSB::FBXLoaderTest::Frame()
{
	InputManager::GetInstance().Frame();

	DXWindow::Frame();
	_loader->Frame();
	return false;
}

bool SSB::FBXLoaderTest::Release()
{
	DXWindow::Release();
	_loader->Release();
	return false;
}

bool SSB::FBXLoaderTest::PreRender()
{
	DXWindow::PreRender();
	_loader->Render();
	return true;
}
