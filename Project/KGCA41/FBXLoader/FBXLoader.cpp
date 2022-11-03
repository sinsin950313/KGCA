#include "FBXLoader.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CommonUtility.h"
#include "DXStateManager.h"

namespace SSB
{
	void SSB::FBXModel::Build()
	{
		_vertexList = _tmpVertexList;
		for (int i = 0; i < _vertexList.size(); ++i)
		{
			_indexList.push_back(i);
		}
	}

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
		FbxNode* node = mesh->GetNode();

		std::vector<FBXModel*> models;
		models.resize(node->GetMaterialCount());
		for (int iMaterial = 0; iMaterial < node->GetMaterialCount(); ++iMaterial)
		{
			FBXModel* model = new FBXModel();
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
					model->SetSprite(SpriteLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
				}
			}
			models[iMaterial] = model;
		}
		if (models.empty())
		{
			models.resize(1);
			models[0] = new FBXModel;
		}

		for (int iLayer = 0; iLayer < mesh->GetLayerCount(); ++iLayer)
		{
			FbxLayer* layer = mesh->GetLayer(iLayer);

			FbxAMatrix geometricMatrix;
			FbxVector4 trans = node->GetGeometricTranslation(FbxNode::eSourcePivot);
			FbxVector4 rot = node->GetGeometricRotation(FbxNode::eSourcePivot);
			FbxVector4 sca = node->GetGeometricScaling(FbxNode::eSourcePivot);
			geometricMatrix.SetT(trans);
			geometricMatrix.SetR(rot);
			geometricMatrix.SetS(sca);

			FbxAMatrix normalLocalMatrix = geometricMatrix;
			normalLocalMatrix = normalLocalMatrix.Inverse();
			normalLocalMatrix = normalLocalMatrix.Transpose();

			FbxVector4 translation;
			if (node->LclTranslation.IsValid())
			{
				translation = node->LclTranslation.Get();
			}
			FbxVector4 rotation;
			if (node->LclRotation.IsValid())
			{
				rotation = node->LclRotation.Get();
			}
			FbxVector4 scale;
			if (node->LclScaling.IsValid())
			{
				scale = node->LclScaling.Get();
			}

			FbxAMatrix matWorldTransform(translation, rotation, scale);
			FbxAMatrix normalWorldMatrix = matWorldTransform;
			normalWorldMatrix = normalWorldMatrix.Inverse();
			normalWorldMatrix = normalWorldMatrix.Transpose();

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
						v = geometricMatrix.MultT(v);
						v = matWorldTransform.MultT(v);

						FbxColor c = { 0, 0, 0, 1 };
						FbxLayerElementVertexColor* vertexColorSet = mesh->GetElementVertexColor();
						if (vertexColorSet)
						{
							c = Read<FbxColor>(vertexColorSet, iCornerIndex[iIndex], iBasePolyIndex + vertexColor[iIndex]);
						}

						FbxVector2 texture{ 0, 0 };
						FbxLayerElementUV* uv = mesh->GetElementUV();
						if (uv)
						{
							texture = Read(uv, iCornerIndex[iIndex], iUVIndex[iIndex]);
						}

						FbxVector4 n{ 0, 0, 0, 0 };
						FbxLayerElementNormal* normal = layer->GetNormals();
						if (normal)
						{
							n = Read<FbxVector4>(normal, iCornerIndex[iIndex], iBasePolyIndex + vertexColor[iIndex]);
							n = normalLocalMatrix.MultT(n);
							n = normalWorldMatrix.MultT(n);
						}

						Vertex_PNCT vertex
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ n.mData[0], n.mData[2], n.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha },
							{ texture.mData[0], texture.mData[1] }
						};

						FbxLayerElementMaterial* MaterialSet = layer->GetMaterials();
						int iSubMtrl = 0;
						if (MaterialSet)
						{
							iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
						}
						models[iSubMtrl]->_tmpVertexList.push_back(vertex);
					}
				}
				iBasePolyIndex += mesh->GetPolygonSize(iPoly);
			}

			DXObject* object = new DXObject();
			for (auto model : models)
			{
				object->SetAdditionalModel(model);
			}
			object->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
			object->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
			object->Init();
			_objectList.push_back(object);
		}
	}

	FbxVector2 SSB::FBXLoader::Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex)
	{
		FbxVector2 t;
		FbxLayerElement::EMappingMode mode = element->GetMappingMode();
		switch (mode)
		{
		case FbxLayerElementUV::eByControlPoint:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElementUV::eDirect:
			{
				t = element->GetDirectArray().GetAt(pointIndex);
				break;
			}
			case FbxLayerElementUV::eIndexToDirect:
			{
				int index = element->GetIndexArray().GetAt(pointIndex);
				t = element->GetDirectArray().GetAt(index);
				break;
			}
			break;
			}
		}
		case FbxLayerElementUV::eByPolygonVertex:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElementUV::eDirect:
			case FbxLayerElementUV::eIndexToDirect:
			{
				t = element->GetDirectArray().GetAt(polygonIndex);
				break;
			}
			}
			break;
		}
		}
		return t;
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

		FbxSystemUnit::cm.ConvertScene(_scene);
		FbxAxisSystem::MayaZUp.ConvertScene(_scene);

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

		TextureResourceManager::GetInstance().Release();
		DXStateManager::GetInstance().Release();
		ShaderManager::GetInstance().Release();

		return true;
	}
}
