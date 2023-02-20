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

	// Mesh Loading Test
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("box.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	_objectList.push_back(object);
	//}

	// Multi Material = Multi Texture Test
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("MultiCameras.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	_objectList.push_back(object);
	//}

	// Multi Material = Multi Texture Test
	{
		_loader->Init();
		auto meshData = _loader->LoadMesh("Ship.FBX");
		Model* model = new Model;
		for (auto mesh : meshData)
		{
			model->RegisterMesh(mesh.first, mesh.second);
		}
		model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
		model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
		DXObject* object = new DXObject;
		object->SetModel(model);
		object->Init();
		_objectList.push_back(object);
	}

	// Object Animation Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Turret_Deploy1.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	//DXObject* turret = _loader->Load("Man.FBX", "Man.FBXScript");
	//	//turret->Init();
	//	//turret->UpdateCurrentAnimation("Take 001");
	//	_objectList.push_back(object);
	//}

	// Multi Layer Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Man.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	_objectList.push_back(object);
	//}

	// Skinning Animation Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Man.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	model->SetCurrentAnimation("Take 001");
	//	_objectList.push_back(object);
	//}

	// Script Animation with Single FBX Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Man.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//	//DXObject* man = _loader->Load("Man.FBX", "Man.FBXScript");
	//	//man->Init();
	//	//man->UpdateCurrentAnimation("Walk");
	//	_objectList.push_back(object);
	//}

	// Animation with Multi FBX File Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Man.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	//////DXObject* swat1 = _loader->Load("Swat.FBX", std::vector<std::string>{ "Swat@walking_backwards.fbx", "Swat@strafe_2.fbx", "Swat@strafe.fbx" });
	////swat1->Init();
	//////swat1->UpdateCurrentAnimation("mixamo.com");
	//	_objectList.push_back(object);
	//}

	// Animation with Multi FBX File and Script Testing
	//{
	//	_loader->Init();
	//	auto meshData = _loader->LoadMesh("Man.FBX");
	//	Model* model = new Model;
	//	for (auto mesh : meshData)
	//	{
	//		model->RegisterMesh(mesh.first, mesh.second);
	//	}
	//	model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshShader.hlsl", "VS", "vs_5_0"));
	//	model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshShader.hlsl", "PS", "ps_5_0"));
	//	DXObject* object = new DXObject;
	//	object->SetModel(model);
	//	object->Init();
	////DXObject* swat = _loader->Load("Swat.FBX", std::vector<std::string>{ "Swat@walking_backwards.fbx", "Swat@strafe_2.fbx", "Swat@strafe.fbx"}, "Swat.FBXScript");
	////swat->Init();
	////swat->UpdateCurrentAnimation("strafe_2");
	//	_objectList.push_back(object);
	//}

	//_camera = new ModelViewCamera();
	//_camera->SetTarget(_loader->_rootObject);
	_camera = new DebugCamera();
	ChangeMainCamera(_camera);
	GetMainCamera()->Move({0, 0, -10});
	_camera->Init();

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
