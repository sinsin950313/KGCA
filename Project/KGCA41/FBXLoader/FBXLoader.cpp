#include "FBXLoader.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CommonUtility.h"
#include "DXStateManager.h"
#include "HCCalculator.h"
#include "DXObject.h"

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

		FbxSystemUnit::m.ConvertScene(_scene);
		FbxAxisSystem::MayaZUp.ConvertScene(_scene);

		_root = _scene->GetRootNode();

		if (_root)
		{
			//_rootObject = new DXObject;
			_rootObject = new DXFBXRootObject;
			class FBXRootModel : public Model
			{
			public:
				void Build()
				{
					_vertexList.push_back({});
					_indexList.push_back(0);
				}
			};
			_rootObject->SetAdditionalModel(new FBXRootModel);
			// Need to Remove
			_rootObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
			_rootObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
			ExtractSkeletonData(_root);
			ParseNode(_root, _rootObject);
		}
	}

	void FBXLoader::ExtractSkeletonData(FbxNode* node)
	{
		FbxSkeleton* skeleton = node->GetSkeleton();
		if (skeleton)
		{
			_skeletonDataMap.insert(std::make_pair(node, _skeletonDataMap.size()));
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			FbxNodeAttribute::EType attribute = node->GetChild(i)->GetNodeAttribute()->GetAttributeType();
			if (attribute == FbxNodeAttribute::eNull ||
				attribute == FbxNodeAttribute::eMesh ||
				attribute == FbxNodeAttribute::eSkeleton)
			{
				ExtractSkeletonData(node->GetChild(i));
			}
		}
	}

	HMatrix44 FBXLoader::Convert(FbxAMatrix matrix)
	{
		HMatrix44 ret
		{
			(float)matrix.Get(0, 0), (float)matrix.Get(0, 2), (float)matrix.Get(0, 1), 0,
			(float)matrix.Get(2, 0), (float)matrix.Get(2, 2), (float)matrix.Get(2, 1), 0,
			(float)matrix.Get(1, 0), (float)matrix.Get(1, 2), (float)matrix.Get(1, 1), 0,
			(float)matrix.Get(3, 0), (float)matrix.Get(3, 2), (float)matrix.Get(3, 1), 1,
		};

		return ret;
	}

	void FBXLoader::LoadAnimation(FbxAnimStack* animStack, FbxNode* node, DXObject* object)
	{
		FbxString animationName = animStack->GetName();

		FbxTakeInfo* info = _scene->GetTakeInfo(animationName);

		FbxTimeSpan timeSpan = info->mLocalTimeSpan;
		FbxTime startTime = timeSpan.GetStart();
		FbxTime endTime = timeSpan.GetStop();
		FbxTime duration = timeSpan.GetDirection();

		FbxLongLong start = startTime.GetFrameCount(FbxTime::GetGlobalTimeMode());
		FbxLongLong	end = endTime.GetFrameCount(FbxTime::GetGlobalTimeMode());

		// Devide this
		//for (FbxLongLong i = start; i <= end; ++i)
		// Easy for test
		for (FbxLongLong i = start; i <= 0; ++i)
		{
			AnimationInfo info;
			info.StartFrame = start;
			//info.EndFrame = end;
			info.EndFrame = 0;
			info.CurrentFrame = i;

			FbxTime time;
			time.SetFrame(i, FbxTime::GetGlobalTimeMode());
			info.Matrix = Convert(node->EvaluateGlobalTransform(time));
			Decompose(info.Matrix, info.Scale, info.Rotate, info.Translate);

			object->SetAdditionalAnimation(info);
		}
	}

	void SSB::FBXLoader::ParseNode(FbxNode* node, DXObject* object)
	{
		FbxMesh* mesh = node->GetMesh();
		if(mesh)
		{
			ParseMeshSkinningData((DXFBXMeshObject*)object, mesh);
			ParseMesh(node, mesh, object);
		}

		FbxSkeleton* skeleton = node->GetSkeleton();
		if (mesh || skeleton)
		{
			// Load Animation Matrix from here
			FbxAnimStack* animStack = _scene->GetSrcObject<FbxAnimStack>();
			if (animStack)
			{
				LoadAnimation(animStack, node, object);
			}
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			FbxNodeAttribute::EType attribute = node->GetChild(i)->GetNodeAttribute()->GetAttributeType();
			if (attribute == FbxNodeAttribute::eNull ||
				attribute == FbxNodeAttribute::eMesh ||
				attribute == FbxNodeAttribute::eSkeleton)
			{
				DXObject* childObject = nullptr;
				if (attribute == FbxNodeAttribute::eMesh)
				{
					childObject = new DXFBXMeshObject;
					int meshCount = _meshDataMap.size();
					((DXFBXMeshObject*)childObject)->SetMeshIndex(meshCount);
					_meshDataMap.insert(std::make_pair(node->GetChild(i), meshCount));
					// Need to Remove
					childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshObject.hlsl", "VS", "vs_5_0"));
					childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshObject.hlsl", "PS", "ps_5_0"));
				}
				else if (attribute == FbxNodeAttribute::eSkeleton)
				{
					childObject = new DXFBXSkeletonObject;
					((DXFBXSkeletonObject*)childObject)->SetRootObject(_rootObject);
					((DXFBXSkeletonObject*)childObject)->SetBoneIndex(_skeletonDataMap.find(node->GetChild(i))->second);
					// Need to Remove
					childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
					childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
				}
				else
				{
					childObject = new DXObject;
					 //Need to Remove
					childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
					childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
				}
				object->SetAdditionalChildObject(childObject);
				ParseNode(node->GetChild(i), childObject);
			}
		}
	}

	void SSB::FBXLoader::ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object)
	{
		for (int iLayer = 0; iLayer < mesh->GetLayerCount(); ++iLayer)
		{
			std::map<int, FBXModel*> modelMap;

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

			//FbxVector4 translation;
			//if (node->LclTranslation.IsValid())
			//{
			//	translation = node->LclTranslation.Get();
			//}
			//FbxVector4 rotation;
			//if (node->LclRotation.IsValid())
			//{
			//	rotation = node->LclRotation.Get();
			//}
			//FbxVector4 scale;
			//if (node->LclScaling.IsValid())
			//{
			//	scale = node->LclScaling.Get();
			//}

			//FbxAMatrix matWorldTransform(translation, rotation, scale);
			//FbxAMatrix normalWorldMatrix = matWorldTransform;
			//normalWorldMatrix = normalWorldMatrix.Inverse();
			//normalWorldMatrix = normalWorldMatrix.Transpose();

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
						//v = matWorldTransform.MultT(v);

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
							//n = normalWorldMatrix.MultT(n);
						}

						Vertex_PNCT vertex
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ n.mData[0], n.mData[2], n.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha },
							{ texture.mData[0], 1 - texture.mData[1] }
						};

						FbxLayerElementMaterial* MaterialSet = layer->GetMaterials();
						int iSubMtrl = 0;
						if (MaterialSet)
						{
							iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
						}

						auto iter = modelMap.find(iSubMtrl);
						if (iter == modelMap.end())
						{
							NewModel(node, iLayer, iSubMtrl, modelMap);
							iter = modelMap.find(iSubMtrl);
						}
						iter->second->_tmpVertexList.push_back(vertex);

						DXFBXMeshObject* meshObject = (DXFBXMeshObject*)object;
						meshObject->_skinningData.push_back(meshObject->_skinningDataPerVertex[vertexIndex]);
					}
				}
				iBasePolyIndex += mesh->GetPolygonSize(iPoly);
			}

			for (auto model : modelMap)
			{
				object->SetAdditionalModel(model.second);
			}
		}
	}

	void FBXLoader::NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap)
	{
		FBXModel* model = new FBXModel;
		FbxSurfaceMaterial* surface = node->GetMaterial(materialIndex);
		if (surface)
		{
			auto prop = surface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (prop.IsValid())
			{
				const FbxFileTexture* tex = prop.GetSrcObject<FbxFileTexture>(layerIndex);
				if (tex)
				{
					auto filePath = tex->GetFileName();
					auto splitedPath = SplitPath(std::wstring(mtw(filePath)));
					if (splitedPath[3] == L".tga" || splitedPath[3] == L".TGA")
					{
						splitedPath[3] = L".DDS";
					}
					std::wstring fileName = splitedPath[2] + splitedPath[3];
					model->SetSprite(SpriteLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
				}
			}
		}
		modelMap.insert(std::make_pair(materialIndex, model));
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

	void FBXLoader::ParseMeshSkinningData(DXFBXMeshObject* object, FbxMesh* mesh)
	{
		object->_skinningDataPerVertex.resize(mesh->GetControlPointsCount());
		int deformerCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
		for (int iDeformer = 0; iDeformer < deformerCount; ++iDeformer)
		{
			FbxDeformer* deformer = mesh->GetDeformer(iDeformer, FbxDeformer::eSkin);
			FbxSkin* skin = (FbxSkin*)deformer;
			int clusterCount = skin->GetClusterCount();
			for (int iCluster = 0; iCluster < clusterCount; ++iCluster)
			{
				FbxCluster* cluster = skin->GetCluster(iCluster);
				int boneIndex = _skeletonDataMap.find(cluster->GetLink())->second;

				FbxAMatrix linkMatrix;
				cluster->GetTransformLinkMatrix(linkMatrix);

				FbxAMatrix adjustMatrix;
				cluster->GetTransformMatrix(adjustMatrix);

				FbxAMatrix fbxBoneBaseMatrix = linkMatrix.Inverse() * adjustMatrix;
				HMatrix44 boneBaseMatrix = Convert(fbxBoneBaseMatrix);
				_rootObject->SetTransformBoneBasedSpaceMatrix(_meshDataMap.find(mesh->GetNode())->second, boneBaseMatrix);

				int controlPointCount = cluster->GetControlPointIndicesCount();
				int* controlPointIndice = cluster->GetControlPointIndices();
				double* controlPointWeights = cluster->GetControlPointWeights();
				for (int iControlPoint = 0; iControlPoint < controlPointCount; ++iControlPoint)
				{
					int vertexIndex = controlPointIndice[iControlPoint];
					float weight = controlPointWeights[iControlPoint];
					object->LinkMeshWithBone(vertexIndex, boneIndex, weight);
				}
			}
		}
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
		FbxTime::EMode timeMode;
		FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);

		Load();

		_rootObject->Init();

		return true;
	}

	bool SSB::FBXLoader::Frame()
	{
		_rootObject->Frame();

		return true;
	}

	bool SSB::FBXLoader::Render()
	{
		_rootObject->Render();

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

		if (_rootObject)
		{
			_rootObject->Release();
			delete _rootObject;
			_rootObject = nullptr;
		}

		TextureResourceManager::GetInstance().Release();
		DXStateManager::GetInstance().Release();
		ShaderManager::GetInstance().Release();

		return true;
	}
	void DXFBXRootObject::UpdateAnimatedBoneData(int boneIndex, HMatrix44 matrix)
	{
		_objectAnimationData.AnimatedBoneMatrix[boneIndex] = matrix.Transpose();
	}
	void DXFBXRootObject::SetTransformBoneBasedSpaceMatrix(int meshIndex, HMatrix44 transformBoneBasedSpaceMatrix)
	{
		_objectAnimationData.TransformBoneBasedSpace[meshIndex] = transformBoneBasedSpaceMatrix.Transpose();
	}
	bool DXFBXRootObject::CreateConstantBuffer()
	{
		DXObject::CreateConstantBuffer();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(_objectAnimationData);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_objectAnimationData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&desc, &sd, &_objectAnimationDataBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	void DXFBXRootObject::UpdateConstantBuffer()
	{
		DXObject::UpdateConstantBuffer();
		g_dxWindow->GetDeviceContext()->UpdateSubresource(_objectAnimationDataBuffer, 0, nullptr, &_objectAnimationData, 0, 0);
	}
	bool DXFBXRootObject::Release()
	{
		if (_objectAnimationDataBuffer)
		{
			_objectAnimationDataBuffer->Release();
			_objectAnimationDataBuffer = nullptr;
		}

		DXObject::Release();

		return true;
	}
	void DXFBXRootObject::DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc)
	{
		DXObject::DeviceContextSettingBeforeDraw(dc);
		dc->VSSetConstantBuffers(1, 1, &_objectAnimationDataBuffer);
	}
	bool DXFBXSkeletonObject::Frame()
	{
		DXObject::Frame();

		// Easy for Test
		HMatrix44 animationMatrix = GetInterpolate(_animationInfos[0]);
		_root->UpdateAnimatedBoneData(_boneIndex, animationMatrix);

		return true;
	}
	bool DXFBXSkeletonObject::Release()
	{
		_root = nullptr;

		DXObject::Release();

		return true;
	}
	bool DXFBXMeshObject::CreateVertexBuffer()
	{
		DXObject::CreateVertexBuffer();

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(SkinningData) * _skinningData.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_skinningData.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_skinningDataBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	void DXFBXMeshObject::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 6;
		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };

		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}
	void DXFBXMeshObject::LinkMeshWithBone(int vertexIndex, int boneIndex, float weight)
	{
		SkinningData& data = _skinningDataPerVertex[vertexIndex];
		for (int i = 0; i < 4; ++i)
		{
			if (data.Weight[i] < weight)
			{
				for (int j = 3; i < j; --j)
				{
					data.AffectingBoneIndex[j] = data.AffectingBoneIndex[j - 1];
					data.Weight[j] = data.Weight[j - 1];
				}

				data.AffectingBoneIndex[i] = boneIndex;
				data.Weight[i] = weight;

				break;
			}
		}
	}
	bool DXFBXMeshObject::CreateConstantBuffer()
	{
		DXObject::CreateConstantBuffer();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(decltype(_meshIndex)) * 4;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_meshIndex;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&desc, &sd, &_meshConstantBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	void DXFBXMeshObject::UpdateConstantBuffer()
	{
		DXObject::UpdateConstantBuffer();
		g_dxWindow->GetDeviceContext()->UpdateSubresource(_meshConstantBuffer, 0, nullptr, &_meshIndex, 0, 0);
	}
	bool DXFBXMeshObject::Release()
	{
		if (_skinningDataBuffer)
		{
			_skinningDataBuffer->Release();
			_skinningDataBuffer = nullptr;
		}

		DXObject::Release();

		return true;
	}
	void DXFBXMeshObject::DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc)
	{
		DXObject::DeviceContextSettingBeforeDraw(dc);

		UINT stride = sizeof(SkinningData);
		UINT offset = 0;

		dc->IASetVertexBuffers(1, 1, &_skinningDataBuffer, &stride, &offset);
	}
}
