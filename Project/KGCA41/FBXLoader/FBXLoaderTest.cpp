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

	//// Mesh Loading Test
	//{
	//	_loader->Init();
	//	_loader->SetFileName("box.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();
	//	//model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNT.hlsl", "VS", "vs_5_0"));
	//	//model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "PS", "ps_5_0"));

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Multi Material = Multi Texture Test
	//{
	//	_loader->Init();
	//	_loader->SetFileName("MultiCameras.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();
	//	//model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNTs.hlsl", "VS", "vs_5_0"));
	//	//model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader_PCNTs.hlsl", "PS", "ps_5_0"));

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Multi Material = Multi Texture Test
	//{
	//	_loader->Init();
	//	_loader->SetFileName("Ship.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();
	//	//model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNTs.hlsl", "VS", "vs_5_0"));
	//	//model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader_PCNTs.hlsl", "PS", "ps_5_0"));

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Object Animation Testing
	//{
	//	_loader->Init();
	//	_loader->SetFileName("Turret_Deploy1.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();

	//	std::map<std::string, Animation*> animations = _loader->LoadAnimation();
	//	for (auto animation : animations)
	//	{
	//		model->Initialize_RegisterAnimation(animation.first, animation.second);
	//	}
	//	model->SetCurrentAnimation("Take 001");

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Multi Layer Testing
	//{
	//	_loader->Init();
	//	_loader->SetFileName("Man.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Skinning Animation Testing
	//{
	//	_loader->Init();
	//	_loader->SetFileName("Man.FBX");

	//	Model* model = _loader->LoadModel();
	//	model->Init();

	//	std::map<std::string, Animation*> animations = _loader->LoadAnimation();
	//	for (auto animation : animations)
	//	{
	//		model->Initialize_RegisterAnimation(animation.first, animation.second);
	//	}
	//	model->SetCurrentAnimation("Take 001");

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	//// Script Animation with Single FBX Testing
	//{
	//	_loader->Init();
	//	_loader->SetFileName("Swat.fbx");

	//	Model* model = _loader->LoadModel();
	//	model->Init();

	//	_loader->Init();
	//	_loader->SetFileName("Swat@strafe.fbx");
	//	std::map<std::string, Animation*> animations = _loader->LoadAnimation();
	//	for (auto animation : animations)
	//	{
	//		model->Initialize_RegisterAnimation(animation.first, animation.second);
	//	}
	//	model->SetCurrentAnimation("mixamo.com");

	//	DXObject* object = new DXObject;
	//	object->Init();
	//	object->SetModel(model);

	//	_objectList.push_back(object);
	//}

	{
		_loader->Init();
		_loader->SetFileName("Cs_Avatar_Girl_Bow_Ambor #1 (merge).fbx");

		Model* model = _loader->LoadModel();
		model->Init();
		//model->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNT.hlsl", "VS", "vs_5_0"));
		//model->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "PS", "ps_5_0"));

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);
	}

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
