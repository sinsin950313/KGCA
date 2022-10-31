#include "FBXLoader.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CommonUtility.h"
#include "DXStateManager.h"

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

	FbxNode* node = mesh->GetNode();
	for(int iMaterial = 0; iMaterial < node->GetMaterialCount(); ++iMaterial)
	{
		FbxSurfaceMaterial* surface = node->GetMaterial(iMaterial);
		if (surface)
		{
			auto prop = surface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (prop.IsValid())
			{
				const FbxFileTexture* tex = prop.GetSrcObject<FbxFileTexture>(0);
				auto filePath = tex->GetFileName();
				auto splitedPath = SplitPath(std::wstring(mtw(filePath)));
				std::wstring fileName = splitedPath[2] + splitedPath[3];
				customModel->SetSprite(SpriteLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
			}
		}
	}

	int polygonCount = mesh->GetPolygonCount();
	int iBasePolyIndex = 0;
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

			int vertexColor[3] = { 0, iFace + 2, iFace + 1 };

			int iUVIndex[3];
			iUVIndex[0] = mesh->GetTextureUVIndex(iPoly, 0);
			iUVIndex[1] = mesh->GetTextureUVIndex(iPoly, iFace + 2);
			iUVIndex[2] = mesh->GetTextureUVIndex(iPoly, iFace + 1);

			for (int iIndex = 0; iIndex < 3; ++iIndex)
			{
				int vertexIndex = iCornerIndex[iIndex];
				FbxVector4 v = vertexPosition[vertexIndex];

				FbxColor c = { 0, 0, 0, 1 };
				FbxLayerElementVertexColor* vertexColorSet = mesh->GetElementVertexColor();
				if (vertexColorSet)
				{
					c = ReadColor(vertexColorSet, iCornerIndex[iIndex], iBasePolyIndex + vertexColor[iIndex]);
				}

				FbxVector2 texture{ 0, 0 };
				FbxLayerElementUV* uv = mesh->GetElementUV();
				if (uv)
				{
					texture = ReadTextureCoordinate(uv, iCornerIndex[iIndex], iUVIndex[iIndex]);
				}

				Vertex vertex
				{
					{ v.mData[0], v.mData[2], v.mData[1], 1 },
					{ c.mRed, c.mGreen, c.mBlue, c.mAlpha },
					{ texture.mData[0], texture.mData[1] }
				};
				customModel->_tmpVertexList.push_back(vertex);
			}
		}
		iBasePolyIndex += mesh->GetPolygonSize(iPoly);
	}

	DXObject* object = new DXObject();
	object->SetModel(customModel);
	object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader.hlsl", "Main", "vs_5_0"));
	object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DPixelShader.hlsl", "Main", "ps_5_0"));
	object->Init();
	_objectList.push_back(object);
}

FbxVector2 SSB::FBXLoader::ReadTextureCoordinate(FbxLayerElementUV* texture, int posIndex, int uvIndex)
{
	FbxVector2 t;
	FbxLayerElement::EMappingMode mode = texture->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (texture->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			t = texture->GetDirectArray().GetAt(posIndex);
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = texture->GetIndexArray().GetAt(posIndex);
			t = texture->GetDirectArray().GetAt(index);
			break;
		}
		break;
		}
	}
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (texture->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		case FbxLayerElementUV::eIndexToDirect:
		{
			t = texture->GetDirectArray().GetAt(uvIndex);
			break;
		}
		}
		break;
	}
	}
	return t;
}

FbxColor SSB::FBXLoader::ReadColor(FbxLayerElementVertexColor* vertexColor, int posIndex, int colorIndex)
{
	FbxColor color(1, 1, 1, 1);
	FbxLayerElement::EMappingMode mode = vertexColor->GetMappingMode();
	switch (mode)
	{
	case FbxLayerElementUV::eByControlPoint:
	{
		switch (vertexColor->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = vertexColor->GetDirectArray().GetAt(posIndex);
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = vertexColor->GetIndexArray().GetAt(posIndex);
			color = vertexColor->GetDirectArray().GetAt(index);
			break;
		}
		}
		break;
	}
	case FbxLayerElementUV::eByPolygonVertex:
	{
		switch (vertexColor->GetReferenceMode())
		{
		case FbxLayerElementUV::eDirect:
		{
			color = vertexColor->GetDirectArray().GetAt(colorIndex);
			break;
		}
		case FbxLayerElementUV::eIndexToDirect:
		{
			int index = vertexColor->GetIndexArray().GetAt(colorIndex);
			color = vertexColor->GetDirectArray().GetAt(index);
			break;
		}
		}
		break;
	}
	}
	return color;
}

int SSB::FBXLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
{
	int iSubMtrl = 0;
	if (pMaterialSetList != nullptr)
	{
		switch (pMaterialSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			switch (pMaterialSetList->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = iPoly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
			}break;
			}
		}
		default:
		{
			break;
		}
		}
	}
	return iSubMtrl;
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
