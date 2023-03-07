#include "FBXLoaderTest.h"
#include "InputManager.h"
#include "DXStateManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "FileIOObject.h"
#include <iostream>

SSB::FBXLoaderTest::~FBXLoaderTest()
{
	Release();
}

bool SSB::FBXLoaderTest::Init()
{
	DXWindow::Init();

	_loader = new FBXLoader();

	//Mesh Loading Test
	{
		_loader->Init();
		_loader->SetFileName("box.FBX");

		Model* model = _loader->LoadModel();
		model->Init();

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Box", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Box");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			object->SetModel(readedModel);
		}
	}

	//Multi Material = Multi Texture Test
	{
		_loader->Init();
		_loader->SetFileName("MultiCameras.FBX");

		Model* model = _loader->LoadModel();
		model->Init();

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_MultiCameras", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_MultiCameras");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			object->SetModel(readedModel);
		}
	}

	//Multi Material = Multi Texture Test
	{
		_loader->Init();
		_loader->SetFileName("Ship.FBX");

		Model* model = _loader->LoadModel();
		model->Init();

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Ship", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Ship");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			object->SetModel(readedModel);
		}
	}

	//Object Animation Testing
	{
		_loader->Init();
		_loader->SetFileName("Turret_Deploy1.FBX");

		Model* model = _loader->LoadModel();
		model->Init();

		std::map<std::string, Animation*> animations = _loader->LoadAnimation();
		for (auto animation : animations)
		{
			model->Initialize_RegisterAnimation(animation.first, animation.second);
		}
		model->SetCurrentAnimation("Take 001");

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Turret", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Turret");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			readedModel->SetCurrentAnimation("Take 001");
			object->SetModel(readedModel);
		}
	}

	//Multi Layer Testing
	//Skinning Animation Testing
	{
		_loader->Init();
		_loader->SetFileName("Man.FBX");

		Model* model = _loader->LoadModel();
		model->Init();

		std::map<std::string, Animation*> animations = _loader->LoadAnimation();
		for (auto animation : animations)
		{
			model->Initialize_RegisterAnimation(animation.first, animation.second);
		}
		model->SetCurrentAnimation("Take 001");

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Man", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Man");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			readedModel->SetCurrentAnimation("Take 001");
			object->SetModel(readedModel);
		}
	}

	//Script Animation with Single FBX Testing
	{
		_loader->Init();
		_loader->SetFileName("Swat.fbx");

		Model* model = _loader->LoadModel();
		model->Init();

		_loader->Init();
		_loader->SetFileName("Swat@strafe.fbx");
		std::map<std::string, Animation*> animations = _loader->LoadAnimation();
		for (auto animation : animations)
		{
			model->Initialize_RegisterAnimation(animation.first, animation.second);
		}
		model->SetCurrentAnimation("mixamo.com");

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Swat", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Swat");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			readedModel->SetCurrentAnimation("mixamo.com");
			object->SetModel(readedModel);
		}
	}

	{
		_loader->Init();
		_loader->SetFileName("Cs_Avatar_Girl_Bow_Ambor #1 (merge).fbx");

		Model* model = _loader->LoadModel();
		model->Init();

		DXObject* object = new DXObject;
		object->Init();
		object->SetModel(model);

		_objectList.push_back(object);

		{
			ObjectScriptIO io;
			std::string str = model->Serialize(0);
			io.Write("ModelWriteTest_Amber", str);
		}

		{
			ObjectScriptIO io;
			std::string str = io.Read("ModelWriteTest_Amber");
			Model* readedModel = new Model;
			readedModel->Deserialize(str);
			readedModel->Init();
			object->SetModel(readedModel);
		}
	}

	//_camera = new ModelViewCamera();
	//_camera->SetTarget(_loader->_rootObject);
	_camera = new DebugCamera();
	ChangeMainCamera(_camera);
	GetMainCamera()->Move({ 0, 0, -10 });
	_camera->Init();

	return false;
}

bool SSB::FBXLoaderTest::Frame()
{
	InputManager::GetInstance().Frame();

	DXWindow::Frame();

	for (auto object : _objectList)
	{
		object->Rotate(0, 0.001f);
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
