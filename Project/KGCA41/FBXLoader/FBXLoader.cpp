#include "FBXLoader.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CommonUtility.h"
#include "DXStateManager.h"
#include "HCCalculator.h"
#include "DXObject.h"
#include "CommonPath.h"
#include "TextureManager.h"
#include "FBXMesh.h"

namespace SSB
{
	SSB::FBXLoader::FBXLoader()
	{
		_manager = FbxManager::Create();
		_scene = FbxScene::Create(_manager, "");
	}

	SSB::FBXLoader::~FBXLoader()
	{
		Release();
	}

	void FBXLoader::PreLoad(std::string fileName)
	{
		_importer = FbxImporter::Create(_manager, "");
		bool ret = _importer->Initialize((wtm(kFBXPath) + fileName).c_str());
		if (!ret)
		{
			OutputDebugStringA(_importer->GetStatus().GetErrorString());
			assert(ret);
		}
		FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);

		ret = _importer->Import(_scene);
		if (!ret)
		{
			OutputDebugStringA(_importer->GetStatus().GetErrorString());
			assert(ret);
		}
		_importer->Destroy();

		FbxSystemUnit::m.ConvertScene(_scene);
		FbxAxisSystem::MayaZUp.ConvertScene(_scene);
		_root = _scene->GetRootNode();
	}

	void FBXLoader::ParseNode(FbxNode* node)
	{
		if (node->GetNodeAttribute() != nullptr)
		{
			FbxNodeAttribute::EType attribute = node->GetNodeAttribute()->GetAttributeType();
			if (attribute == FbxNodeAttribute::eNull)
			{
				// Nothing to do
			}
			if (attribute == FbxNodeAttribute::eMesh)
			{
				RegisterMeshNode(node);
			}
			if (attribute == FbxNodeAttribute::eSkeleton)
			{
				RegisterBoneNode(node);
			}
		}

		for (int i = 0; i < node->GetChildCount(); ++i)
		{
			ParseNode(node->GetChild(i));
		}
	}

	void FBXLoader::RegisterBoneNode(FbxNode* node)
	{
		if (_boneNodeToBoneIndexMap.find(node) == _boneNodeToBoneIndexMap.end())
		{
			int index = _boneNodeToBoneIndexMap.size();
			_boneNodeToBoneIndexMap.insert(std::make_pair(node, index));

			std::string name = node->GetName();
			BoneInfo info;
			if (_fbxBoneKeyToFbxBoneMap.size() != 0)
			{
				info.Name = name;
				info.ParentIndex = _boneNodeToBoneIndexMap.find(node->GetParent())->second;
			}
			else
			{
				info.Name = name;
				info.ParentIndex = -1;
			}

			FbxAMatrix localMatrix;
			FbxVector4 trans = node->LclTranslation.Get();
			FbxVector4 rot = node->LclRotation.Get();
			FbxVector4 sca = node->LclScaling.Get();
			//FbxVector4 trans = node->GetGeometricTranslation(FbxNode::eSourcePivot);
			//FbxVector4 rot = node->GetGeometricRotation(FbxNode::eSourcePivot);
			//FbxVector4 sca = node->GetGeometricScaling(FbxNode::eSourcePivot);
			localMatrix.SetT(trans);
			localMatrix.SetR(rot);
			localMatrix.SetS(sca);
			info.LocalMatrix = Convert(localMatrix);

			_fbxBoneKeyToFbxBoneMap.insert(std::make_pair(node, FBXBoneData{index, info}));
		}
	}

	void FBXLoader::RegisterMeshNode(FbxNode* node)
	{
		if (_meshNodeToMeshIndexMap.find(node) == _meshNodeToMeshIndexMap.end())
		{
			_meshNodeToMeshIndexMap.insert(std::make_pair(node, _meshNodeToMeshIndexMap.size()));
		}
	}

	void FBXLoader::ExtractMaterial()
	{
		int count = _scene->GetMaterialCount();
		for (int i = 0; i < count; ++i)
		{
			FBXMaterialKey key;

			Material* material = new Material;
			material->Initialize_SetMaterialIndex(i);

			FbxSurfaceMaterial* fbxMaterial = _scene->GetMaterial(i);

			if (fbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				FbxSurfaceLambert* lambertMaterial = (FbxSurfaceLambert*)fbxMaterial;

				//FbxDouble3 emissive = lambertMaterial->Emissive;
				//FbxDouble emissiveFactor = lambertMaterial->EmissiveFactor;

				//FbxDouble3 ambient = lambertMaterial->Ambient;
				//FbxDouble ambientFactor = lambertMaterial->AmbientFactor;

				{
					FbxDouble3 diffuse = lambertMaterial->Diffuse;
					FbxProperty prop = fbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
					if (prop.IsValid())
					{
						FbxFileTexture* fileTexture = prop.GetSrcObject<FbxFileTexture>();
						if (fileTexture != nullptr)
						{
							std::wstring fileName = ExtractTextureFileName(fileTexture, material);
							material->Initialize_SetTexture(kDiffuse, TextureLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
							key = wtm(fileName);
						}
					}
					//ExtractTexture(&prop, material, kDiffuse);
					FbxDouble diffuseFactor = lambertMaterial->DiffuseFactor;
				}

				//FbxDouble3 normal = lambertMaterial->NormalMap;
			}

			if (fbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong* phongMaterial = (FbxSurfacePhong*)fbxMaterial;

				//FbxDouble3 specular = phongMaterial->Specular;
				//FbxDouble specularFactor = phongMaterial->SpecularFactor;

				//FbxDouble shininess = phongMaterial->Shininess;

				//FbxDouble3 reflection = phongMaterial->Reflection;
				//FbxDouble reflectionFactor = phongMaterial->ReflectionFactor;
			}
			material->Init();

			if (!key.empty())
			{
				_fbxMaterialKeyToFbxMaterialMap.insert(std::make_pair(key, FBXMaterialData{ i, material }));
			}
		}
	}

	//void FBXLoader::ExtractTexture(FbxProperty* fbxProperty, Material* material, TextureType textureType)
	//{
	//	if (fbxProperty->IsValid())
	//	{
	//		//int layeredTextureCount = fbxProperty->GetSrcObjectCount<FbxLayeredTexture>();
	//		//for (int j = 0; j < layeredTextureCount; ++j)
	//		//{
	//		//	FbxLayeredTexture* layeredTexture = fbxProperty->GetSrcObject<FbxLayeredTexture>(j);
	//		//	if (layeredTexture)
	//		//	{
	//		//		int layeredTextureCount = layeredTexture->GetSrcObjectCount();
	//		//		for (int k = 0; k < layeredTextureCount; ++k)
	//		//		{
	//		//			FbxTexture* texture = layeredTexture->GetSrcObject<FbxTexture>(k);
	//		//			if (texture != nullptr)
	//		//			{
	//		//				ExtractTextureFileName(texture, textureFileNameSet);
	//		//			}
	//		//		}
	//		//	}
	//		//}

	//		int textureCount = fbxProperty->GetSrcObjectCount<FbxTexture>();
	//		for (int j = 0; j < textureCount; ++j)
	//		{
	//			FbxTexture* texture = fbxProperty->GetSrcObject<FbxTexture>(j);
	//			if (texture != nullptr)
	//			{
	//				ExtractTextureFileName(texture, material, textureType);
	//			}
	//		}
	//	}
	//}

	//void FBXLoader::ExtractTextureFileName(FbxTexture* texture, Material* material, TextureType textureType)
	//{
	//	for (int i = 0; i < texture->GetSrcObjectCount<FbxFileTexture>(); ++i)
	//	{
	//		FbxFileTexture* fileTexture = texture->GetSrcObject<FbxFileTexture>();
	//		if (fileTexture != nullptr)
	//		{
	//			std::string fileFullPath = fileTexture->GetFileName();
	//			auto splitedPath = SplitPath(mtw(fileFullPath));
	//			std::wstring fileName = splitedPath[2] + splitedPath[3];
	//			material->Initialize_SetTexture(textureType, TextureLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
	//		}
	//	}
	//}

	std::wstring FBXLoader::ExtractTextureFileName(FbxFileTexture* texture, Material* material)
	{
		std::string fileFullPath = texture->GetFileName();
		auto splitedPath = SplitPath(mtw(fileFullPath));
		if (splitedPath[3] == L".tga" || splitedPath[3] == L".TGA")
		{
			splitedPath[3] = L".DDS";
		}
		std::wstring fileName = splitedPath[2] + splitedPath[3];
		return fileName;
	}

	void FBXLoader::ParseMesh()
	{
		for (auto iter : _meshNodeToMeshIndexMap)
		{
			MeshInterface* mesh = nullptr;

			FbxMesh* fbxMesh = iter.first->GetMesh();
			//if (1 < _scene->GetMaterialCount())
			if (1 < _fbxMaterialKeyToFbxMaterialMap.size())
			{
				if (_boneNodeToBoneIndexMap.empty())
				{
					mesh = new FBXMesh_PCNTs_Animatable;
					static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
					static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetMaterialData(_fbxMaterialKeyToFbxMaterialMap);
					static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetMeshData(MeshData{ iter.second });
				}
				else
				{
					mesh = new FBXMesh_PCNTs_Skinning;
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetMaterialData(_fbxMaterialKeyToFbxMaterialMap);
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetBoneData(_fbxBoneKeyToFbxBoneMap);
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetMaxBoneCount(_fbxBoneKeyToFbxBoneMap.size());
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetMeshData(iter.second);
				}
				_ps = ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader_PCNT_P.hlsl", "PS", "ps_5_0");
			}
			else
			{
				if (_boneNodeToBoneIndexMap.empty())
				{
					mesh = new FBXMesh_PCNT_Animatable;
					static_cast<FBXMesh_PCNT_Animatable*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
					static_cast<FBXMesh_PCNT_Animatable*>(mesh)->Initialize_SetMeshData({ iter.second });
				}
				else
				{
					mesh = new FBXMesh_PCNT_Skinning;
					static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
					static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetBoneData(_fbxBoneKeyToFbxBoneMap);
					static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetMaxBoneCount(_fbxBoneKeyToFbxBoneMap.size());
					static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetMeshData(iter.second);
				}
				_ps = ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader_PCNT.hlsl", "PS", "ps_5_0");
			}
			////if (1 < _scene->GetMaterialCount())
			//if (1 < _fbxMaterialKeyToFbxMaterialMap.size())
			//{
			//	if (_scene->GetSrcObjectCount<FbxAnimStack>() == 0)
			//	{
			//		// Not Tested
			//		mesh = new FBXMesh_PCNTs;
			//		static_cast<FBXMesh_PCNTs*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//		static_cast<FBXMesh_PCNTs*>(mesh)->Initialize_SetMaterialData(_fbxMaterialKeyToFbxMaterialMap);
			//	}
			//	else if (fbxMesh->GetDeformerCount() == 0)
			//	{
			//		mesh = new FBXMesh_PCNTs_Animatable;
			//		static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//		static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetMaterialData(_fbxMaterialKeyToFbxMaterialMap);
			//		static_cast<FBXMesh_PCNTs_Animatable*>(mesh)->Initialize_SetMeshData(MeshData{ iter.second });
			//	}
			//	else
			//	{
			//		mesh = new FBXMesh_PCNTs_Skinning;
			//		static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//		static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetMaterialData(_fbxMaterialKeyToFbxMaterialMap);
			//		static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetBoneData(_fbxBoneKeyToFbxBoneMap);
			//	}
			//	_ps = ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader_PCNT_P.hlsl", "PS", "ps_5_0");
			//}
			//else
			//{
			//	if (_scene->GetSrcObjectCount<FbxAnimStack>() == 0)
			//	{
			//		// Not Tested
			//		mesh = new FBXMesh_PCNT;
			//		static_cast<FBXMesh_PCNT*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//	}
			//	if (fbxMesh->GetDeformerCount() == 0)
			//	{
			//		mesh = new FBXMesh_PCNT_Animatable;
			//		static_cast<FBXMesh_PCNT_Animatable*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//		static_cast<FBXMesh_PCNT_Animatable*>(mesh)->Initialize_SetMeshData({ iter.second });
			//	}
			//	else
			//	{
			//		mesh = new FBXMesh_PCNT_Skinning;
			//		static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
			//		static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetBoneData(_fbxBoneKeyToFbxBoneMap);
			//	}
			//	_ps = ShaderManager::GetInstance().LoadPixelShader(L"DefaultPixelShader_PCNT.hlsl", "PS", "ps_5_0");
			//}

			mesh->Init();

			RegisterMesh(mesh);
		}
	}

	void FBXLoader::RegisterMesh(MeshInterface* mesh)
	{
		_indexToMeshMap.insert(std::make_pair(_indexToMeshMap.size(), mesh));
	}

	void FBXLoader::ParseAnimation()
	{
		int animStackCount = _scene->GetSrcObjectCount<FbxAnimStack>();
		for(int i = 0; i < animStackCount; ++i)
		{
			FbxAnimStack* animStack = _scene->GetSrcObject<FbxAnimStack>(i);
			std::string animationName(animStack->GetName());

			FbxString fbxStr(animStack->GetName());
			FbxTakeInfo* info = _scene->GetTakeInfo(fbxStr);

			FbxTimeSpan timeSpan = info->mLocalTimeSpan;
			FbxTime startTime = timeSpan.GetStart();
			FbxTime endTime = timeSpan.GetStop();
			FbxTime duration = timeSpan.GetDirection();

			FbxLongLong startFrame = startTime.GetFrameCount(FbxTime::GetGlobalTimeMode());
			FbxLongLong endFrame = endTime.GetFrameCount(FbxTime::GetGlobalTimeMode());
			FbxTime::EMode timeMode = FbxTime::GetGlobalTimeMode();

			std::vector<AnimationFrameInfo*> data;
			for (FbxLongLong t = startFrame; t <= endFrame; ++t)
			{
				FbxTime time;
				time.SetFrame(t, timeMode);

				AnimationFrameInfo* actionFrameInfo = new AnimationFrameInfo;
				for (auto node : _boneNodeToBoneIndexMap)
				{
					AnimationUnitInfo unitInfo;
					unitInfo.Matrix = Convert(node.first->EvaluateGlobalTransform(time));
					Decompose(unitInfo.Matrix, unitInfo.Scale, unitInfo.Rotate, unitInfo.Translate);

					actionFrameInfo->BoneAnimationUnit[node.second] = unitInfo;
				}

				for (auto node : _meshNodeToMeshIndexMap)
				{
					AnimationUnitInfo unitInfo;
					unitInfo.Matrix = Convert(node.first->EvaluateGlobalTransform(time));
					Decompose(unitInfo.Matrix, unitInfo.Scale, unitInfo.Rotate, unitInfo.Translate);

					actionFrameInfo->MeshAnimationUnit[node.second] = unitInfo;
				}
				data.push_back(actionFrameInfo);
			}
			Animation* animation = new Animation;

			animation->Initialize_SetAnimationFrameData(data);
			animation->Initialize_SetAnimationUnitMaximumCount(_boneNodeToBoneIndexMap.size(), _meshNodeToMeshIndexMap.size());
			animation->Initialize_SetFrameInterval(0, endFrame - startFrame);
			animation->Init();

			_animations.insert(std::make_pair(animationName, animation));
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

	void FBXLoader::SetFileName(std::string fileName)
	{
		PreLoad(fileName);
		ParseNode(_root);
	}

	std::map<MaterialIndex, Material*> FBXLoader::LoadMaterial()
	{
		ExtractMaterial();

		std::map<MaterialIndex, Material*> ret;
		for (auto materialData : _fbxMaterialKeyToFbxMaterialMap)
		{
			ret.insert(std::make_pair(materialData.second.Index, materialData.second.MeshMaterial));
		}

		return ret;
	}

	Model* FBXLoader::LoadModel()
	{
		Model* ret = new Model;
		auto materialMap = LoadMaterial();
		for (auto material : materialMap)
		{
			ret->Initialize_RegisterMaterial(material.first, material.second);
		}

		ParseMesh();

		for (auto mesh : _indexToMeshMap)
		{
			ret->Initialize_RegisterMesh(mesh.first, mesh.second);
		}
		ret->SetPixelShader(_ps);

		return ret;
	}

	std::map<std::string, Animation*> FBXLoader::LoadAnimation()
	{
		ParseAnimation();

		return _animations;
	}

	Skeleton* FBXLoader::LoadSkeleton()
	{
		std::map<BoneIndex, BoneInfo> data;
		for (auto& info : _fbxBoneKeyToFbxBoneMap)
		{
			data.insert(std::make_pair(info.second.FBXBoneIndex, info.second.Info));
		}
		Skeleton* ret = new Skeleton;
		ret->Initialize_SetBoneData(data);

		return ret;
	}

	bool SSB::FBXLoader::Init()
	{
		_frameSpeed = 30.0f;
		_tickPerFrame = 160;

		_root = nullptr;
		_boneNodeToBoneIndexMap.clear();
		_meshNodeToMeshIndexMap.clear();
		_fbxBoneKeyToFbxBoneMap.clear();
		_fbxMaterialKeyToFbxMaterialMap.clear();
		_indexToMeshMap.clear();
		_animations.clear();

		_ps = nullptr;

		return true;
	}

	bool SSB::FBXLoader::Frame()
	{
		return true;
	}

	bool SSB::FBXLoader::Render()
	{
		return true;
	}

	bool SSB::FBXLoader::Release()
	{
		//if (_importer)
		//{
		//	_importer->Destroy();
		//	_importer = nullptr;
		//}
		if (_scene)
		{
			_scene->Destroy();
			_scene = nullptr;
		}
		if (_manager)
		{
			_manager->Destroy();
			_manager = nullptr;
		}

		return true;
	}
}
