#include "FBXLoader.h"
#include "ShaderManager.h"

SSB::FBXLoader::FBXLoader()
{
}

SSB::FBXLoader::~FBXLoader()
{
	Release();
}

void SSB::FBXLoader::Load()
{
	_importer->Import(_scene);
	_root = _scene->GetRootNode();

	PreProcess(_root);

	for (auto mesh : _meshList)
	{
		ParseMesh(mesh);
	}
}

void SSB::FBXLoader::PreProcess(FbxNode* node)
{
	if (node)
	{
		FbxMesh* mesh;
		if ((mesh = node->GetMesh()) != nullptr)
		{
			_meshList.push_back(mesh);
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			PreProcess(node->GetChild(i));
		}
	}
}

void SSB::FBXLoader::ParseMesh(FbxMesh* mesh)
{
	//for (int iLayer = 0; mesh->GetiLayer(); ++iLayer)
	//{
	//	FbxLayer* layer = mesh->GetLayer(iLayer);
	//	if (layer->GetUVs())
	//	{
	//		layer->GetUVs();
	//	}
	//}

	class CustomModel : public Model
	{
	public:
		std::vector<Vertex> _tmpVertexList;

	public:
		void Build()
		{
			_vertexList = _tmpVertexList;
			for (int i = 0; i < _vertexList.size(); ++i)
			{
				_indexList.push_back(i);
			}
		}
	};

	CustomModel* customModel = new CustomModel();

	int polygonCount = mesh->GetPolygonCount();
	FbxVector4* vertexPosition = mesh->GetControlPoints();
	for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
	{
		int polygonSize = mesh->GetPolygonSize(iPoly);
		int faceCount = polygonSize - 2;
		for (int iFace = 0; iFace < faceCount; ++iFace)
		{
			int iCornerIndex[3];
			iCornerIndex[0] = mesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = mesh->GetPolygonVertex(iPoly, iFace + 2);
			iCornerIndex[2] = mesh->GetPolygonVertex(iPoly, iFace + 1);
			for (int iIndex = 0; iIndex < 3; ++iIndex)
			{
				int vertexIndex = iCornerIndex[iIndex];
				FbxVector4 v = vertexPosition[vertexIndex];
				Vertex vertex
				{
					{ v.mData[0], v.mData[2], v.mData[1], 1 },
					{ 0, 0, 0, 1 },
					{ 0, 0 }
				};
				customModel->_tmpVertexList.push_back(vertex);
			}
		}
	}

	DXObject* object = new DXObject();
	object->SetModel(customModel);
	object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
	object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader.hlsl", "Main", "ps_5_0"));
	object->Init();
	_objectList.push_back(object);
}

bool SSB::FBXLoader::Init()
{
	_manager = FbxManager::Create();
	_importer = FbxImporter::Create(_manager, "");
	_scene = FbxScene::Create(_manager, "");
	bool ret = _importer->Initialize(_fileName.c_str());
	if (!ret)
	{
		OutputDebugStringA(_importer->GetStatus().GetErrorString());
	}
	Load();

	return true;
}

bool SSB::FBXLoader::Frame()
{
	for (auto object : _objectList)
	{
		object->Frame();
	}

	return true;
}

bool SSB::FBXLoader::Render()
{
	for (auto object : _objectList)
	{
		object->Render();
	}

	return true;
}

bool SSB::FBXLoader::Release()
{
	//for (auto object : _objectList)
	//{
	//	object->Release();
	//}
	//_objectList.clear();
	//if (_manager)
	//{
	//	// FbxManager is singleton
	//	_manager = nullptr;
	//}
	//if (_importer)
	//{
	//	_importer->Destroy();
	//	_importer = nullptr;
	//}
	//if (_scene)
	//{
	//	_scene->Destroy();
	//	_scene = nullptr;
	//}
	//if (_root)
	//{
	//	_root->Destroy();
	//	_root = nullptr;
	//}
	//for (auto mesh : _meshList)
	//{
	//	mesh->Destroy();
	//}
	//_meshList.clear();
	for (auto object : _objectList)
	{
		object->Release();
		delete object;
	}
	_objectList.clear();

	return true;
}
