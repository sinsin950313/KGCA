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
		if (_skeletonNodeToSkeletonIndexMap.find(node) == _skeletonNodeToSkeletonIndexMap.end())
		{
			_skeletonNodeToSkeletonIndexMap.insert(std::make_pair(node, _skeletonNodeToSkeletonIndexMap.size()));
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
						ExtractTextureFileName(fileTexture, material, kDiffuse);
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

			_indexToMaterialMap.insert(std::make_pair(i, material));
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

	void FBXLoader::ExtractTextureFileName(FbxFileTexture* texture, Material* material, TextureType textureType)
	{
		std::string fileFullPath = texture->GetFileName();
		auto splitedPath = SplitPath(mtw(fileFullPath));
		std::wstring fileName = splitedPath[2] + splitedPath[3];
		material->Initialize_SetTexture(textureType, TextureLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
	}

	void FBXLoader::ParseMesh()
	{
		for (auto iter : _meshNodeToMeshIndexMap)
		{
			MeshInterface* mesh = nullptr;

			FbxMesh* fbxMesh = iter.first->GetMesh();
			//if (1 < fbxMesh->GetElementMaterialCount())
			if (1 < _indexToMaterialMap.size())
			{
				if (fbxMesh->GetDeformerCount() == 0)
				{
					mesh = new FBXMesh_PCNTs;
					static_cast<FBXMesh_PCNTs*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
				}
				else
				{
					mesh = new FBXMesh_PCNTs_Skinning;
					static_cast<FBXMesh_PCNTs_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
				}
			}
			else
			{
				if (fbxMesh->GetDeformerCount() == 0)
				{
					mesh = new FBXMesh_PCNT;
					static_cast<FBXMesh_PCNT*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
				}
				else
				{
					mesh = new FBXMesh_PCNT_Skinning;
					static_cast<FBXMesh_PCNT_Skinning*>(mesh)->Initialize_SetFBXMesh(fbxMesh);
				}
			}

			mesh->Init();

			RegisterMesh(mesh);
		}
	}

	void FBXLoader::RegisterMesh(MeshInterface* mesh)
	{
		_indexToMeshMap.insert(std::make_pair(_indexToMeshMap.size(), mesh));
	}

	void FBXLoader::SetFileName(std::string fileName)
	{
		PreLoad(fileName);
		ParseNode(_root);
	}

	std::map<MaterialIndex, Material*> FBXLoader::LoadMaterial()
	{
		ExtractMaterial();

		return _indexToMaterialMap;
	}

	Model* FBXLoader::LoadModel()
	{
		ExtractMaterial();

		ParseMesh();

		Model* ret = new Model;
		for (auto mesh : _indexToMeshMap)
		{
			ret->Initialize_RegisterMesh(mesh.first, mesh.second);
		}

		for (auto material : _indexToMaterialMap)
		{
			ret->Initialize_RegisterMaterial(material.first, material.second);
		}

		return ret;
	}

	bool SSB::FBXLoader::Init()
	{
		//_frameSpeed = 30.0f;
		//_tickPerFrame = 160;

		_root = nullptr;
		_skeletonNodeToSkeletonIndexMap.clear();
		_meshNodeToMeshIndexMap.clear();

		//_animationInfo = AnimationFrameInfo();
		//_meshInfo.clear();

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

	//////////////////////////////////////////////////////////////////////////////
	// Don't remove for safety													//
	//////////////////////////////////////////////////////////////////////////////
	//DXObject* SSB::FBXLoader::Load(std::string fileName)
	//{
	//	FbxNode* root = PreLoad(wtm(kFBXPath) + fileName);

	//	DXFBXRootObject* rootObject = nullptr;
	//	if (root)
	//	{
	//		rootObject = LoadObject(root);

	//		FbxAnimStack* animStack = _scene->GetSrcObject<FbxAnimStack>();
	//		std::string animationName(animStack->GetName());
	//		ExtractAnimationInfoData info = ExtractAnimationInfo(animStack);

	//		LoadAnimation(animationName, info);
	//	}

	//	return rootObject;
	//}

	//DXObject* FBXLoader::Load(std::string fileName, std::string scriptFileName)
	//{
	//	std::vector<Script> scriptDatas = ParseScript(scriptFileName);
	//	FbxNode* root = PreLoad(wtm(kFBXPath) + fileName);

	//	DXFBXRootObject* rootObject = nullptr;
	//	if (root)
	//	{
	//		rootObject = LoadObject(root);

	//		FbxAnimStack* animStack = _scene->GetSrcObject<FbxAnimStack>();
	//		ExtractAnimationInfoData info = ExtractAnimationInfo(animStack);

	//		int beforeFrame = 0;
	//		for (auto scriptData : scriptDatas)
	//		{
	//			for (auto& nodeToAnimationInfo : _nodeToAnimationInfo)
	//			{
	//				std::map<std::string, ActionInfo>& actionData = nodeToAnimationInfo.second.FrameInfo;

	//				actionData.insert(std::make_pair(scriptData.ActionName, ActionInfo{ (UINT)scriptData.EndFrame - beforeFrame }));
	//			}
	//			beforeFrame = scriptData.EndFrame;
	//		}

	//		int scriptIndex = 0;
	//		for (FbxLongLong t = info.Start; t <= info.End; ++t)
	//		{
	//			FbxTime time;
	//			time.SetFrame(t, info.TimeMode);

	//			if (scriptDatas[scriptIndex].EndFrame < t)
	//			{
	//				++scriptIndex;

	//				if (scriptDatas.size() <= scriptIndex)
	//				{
	//					break;
	//				}
	//			}
	//			SaveFrame(scriptDatas[scriptIndex].ActionName, time);
	//		}

	//		for (auto scriptData : scriptDatas)
	//		{
	//			for (auto& nodeToAnimationInfo : _nodeToAnimationInfo)
	//			{
	//				Animation* animation = nodeToAnimationInfo.second.Animation;
	//				std::map<std::string, ActionInfo>& actionData = nodeToAnimationInfo.second.FrameInfo;

	//				animation->SetAdditionalAction(scriptData.ActionName, actionData.find(scriptData.ActionName)->second);
	//			}
	//		}

	//		for (auto& nodeToObject : _nodeToObject)
	//		{
	//			FbxNode* node = nodeToObject.first;
	//			DXObject* object = nodeToObject.second;
	//			object->SetAnimation(_nodeToAnimationInfo.find(node)->second.Animation);
	//		}
	//	}

	//	return rootObject;
	//}

	//DXObject* FBXLoader::Load(std::string fileName, std::vector<std::string> animationFileNameList)
	//{
	//	DXFBXRootObject* rootObject = (DXFBXRootObject*)Load(fileName);

	//	FBXLoader animationLoader;
	//	for (auto animationFIleName : animationFileNameList)
	//	{
	//		animationLoader.Init();
	//		FbxNode* animationRoot = animationLoader.PreLoad(wtm(kFBXPath) + animationFIleName);

	//		DXFBXRootObject* animationRootObject = nullptr;
	//		if (animationRoot)
	//		{
	//			{
	//				animationRootObject = animationLoader.LoadObject(animationRoot);

	//				FbxAnimStack* animStack = animationLoader._scene->GetSrcObject<FbxAnimStack>();
	//				std::string animationName(animStack->GetName());
	//				ExtractAnimationInfoData info = animationLoader.ExtractAnimationInfo(animStack);

	//				animationLoader.LoadAnimation(animationName, info);
	//				delete animationRootObject;
	//			}

	//			{
	//				auto& animationSkeletonNodeToIndex = animationLoader._skeletonDataMap;
	//				auto& animationNodeToAnimationInfo = animationLoader._nodeToAnimationInfo;
	//				for (auto nodeToIndex : animationSkeletonNodeToIndex)
	//				{
	//					FbxNode* animationNode = nodeToIndex.first;
	//					AnimationData& animationData = animationNodeToAnimationInfo.find(animationNode)->second;
	//					int index = nodeToIndex.second;
	//					FbxNode* node = _skeletonIndexToObjectMap.find(index)->second;

	//					for (auto& nameAndActionInfo : animationData.FrameInfo)
	//					{
	//						std::string name = nameAndActionInfo.first;
	//						ActionInfo info = nameAndActionInfo.second;
	//						_nodeToAnimationInfo.find(node)->second.FrameInfo.insert(std::make_pair(name, info));
	//					}
	//				}
	//			}
	//		}
	//	}

	//	for (auto& nodeToObject : _nodeToObject)
	//	{
	//		FbxNode* node = nodeToObject.first;
	//		DXObject* object = nodeToObject.second;

	//		auto& nodeToAnimationData = _nodeToAnimationInfo.find(node)->second;
	//		for (auto info : nodeToAnimationData.FrameInfo)
	//		{
	//			nodeToAnimationData.Animation->SetAdditionalAction(info.first, info.second);
	//		}
	//		object->SetAnimation(_nodeToAnimationInfo.find(node)->second.Animation);
	//	}

	//	return rootObject;
	//}

	//DXObject* FBXLoader::Load(std::string fileName, std::vector<std::string> animationFileNameList, std::string animationScriptFileName)
	//{
	//	FbxNode* root = PreLoad(wtm(kFBXPath) + fileName);

	//	DXFBXRootObject* rootObject = nullptr;
	//	if (root)
	//	{
	//		rootObject = LoadObject(root);

	//		std::map<std::string, Script> actionList;
	//		{
	//			std::wstring fileFullPath = kFBXScriptPath + mtw(animationScriptFileName);

	//			FILE* fp_src;
	//			_wfopen_s(&fp_src, fileFullPath.c_str(), _T("rt"));
	//			if (fp_src)
	//			{
	//				TCHAR pBuffer[256] = { 0 };
	//				_fgetts(pBuffer, _countof(pBuffer), fp_src);

	//				int iNumFBXAction = 0;
	//				_stscanf_s(pBuffer, _T("%d"), &iNumFBXAction);

	//				for (int iCnt = 0; iCnt < iNumFBXAction; iCnt++)
	//				{
	//					TCHAR fileName[256] = { 0 };
	//					TCHAR actionName[256] = { 0 };
	//					int iNumFrame = 0;
	//					Script script;

	//					_fgetts(pBuffer, _countof(pBuffer), fp_src);
	//					_stscanf_s(pBuffer, _T("%s %s %d"), fileName, (unsigned int)_countof(fileName), actionName, (unsigned int)_countof(actionName), &iNumFrame);
	//					script.ActionName = wtm(std::wstring(actionName));
	//					script.EndFrame = iNumFrame;

	//					actionList.insert(std::make_pair(wtm(std::wstring(fileName)), script));
	//				}
	//				fclose(fp_src);
	//			}
	//		}

	//		class AnimationFBXLoader : public FBXLoader
	//		{
	//		public:
	//			Script _script;
	//			std::map<int, AnimationData> _skeletonIndexToAnimation;

	//		public:
	//			void SetNodeIndex(std::map<FbxNode*, AnimationData>& nodeToAnimationOrigin, std::map<FbxNode*, int> nodeToSkeletonIndexOrigin)
	//			{
	//				for (auto nodeToAnimation : nodeToAnimationOrigin)
	//				{
	//					FbxNode* node = nodeToAnimation.first;
	//					if (node->GetSkeleton())
	//					{
	//						int index = nodeToSkeletonIndexOrigin.find(node)->second;
	//						AnimationData animData = nodeToAnimation.second;
	//						_skeletonIndexToAnimation.insert(std::make_pair(index, animData));
	//					}
	//				}
	//			}
	//			void LoadAnimation(std::string animationName, ExtractAnimationInfoData info) override
	//			{
	//				for (auto& nodeToAnimationInfo : _nodeToAnimationInfo)
	//				{
	//					FbxNode* node = nodeToAnimationInfo.first;
	//					if (node->GetSkeleton())
	//					{
	//						int index = _skeletonDataMap.find(node)->second;
	//						AnimationData& animData = _skeletonIndexToAnimation.find(index)->second;
	//						animData.FrameInfo.insert(std::make_pair(_script.ActionName, ActionInfo{ (UINT)_script.EndFrame }));
	//					}
	//				}

	//				for (FbxLongLong t = info.Start; t <= info.End; ++t)
	//				{
	//					if (_script.EndFrame < t)
	//					{
	//						break;
	//					}

	//					FbxTime time;
	//					time.SetFrame(t, info.TimeMode);

	//					for (auto nodeToObject : _nodeToObject)
	//					{
	//						FbxNode* node = nodeToObject.first;
	//						if (node->GetSkeleton())
	//						{
	//							ActionFrameInfo actionFrameInfo;
	//							actionFrameInfo.Matrix = Convert(nodeToObject.first->EvaluateGlobalTransform(time));
	//							Decompose(actionFrameInfo.Matrix, actionFrameInfo.Scale, actionFrameInfo.Rotate, actionFrameInfo.Translate);

	//							int index = _skeletonDataMap.find(node)->second;
	//							AnimationData& animData = _skeletonIndexToAnimation.find(index)->second;
	//							ActionInfo& data = animData.FrameInfo.find(_script.ActionName)->second;
	//							data.FrameInfoList.push_back(actionFrameInfo);
	//						}
	//					}
	//				}

	//				for (auto data : _skeletonIndexToAnimation)
	//				{
	//					Animation* animation = data.second.Animation;
	//					std::map<std::string, ActionInfo>& actionData = data.second.FrameInfo;
	//					animation->SetAdditionalAction(_script.ActionName, actionData.find(_script.ActionName)->second);
	//				}
	//			}
	//			bool Init() override
	//			{
	//				for (auto nodeToAnimation : _nodeToAnimationInfo)
	//				{
	//					Animation* animation = nodeToAnimation.second.Animation;
	//					animation->Release();
	//					delete animation;
	//				}

	//				FBXLoader::Init();

	//				return true;
	//			}
	//			bool Release() override
	//			{
	//				for (auto nodeToAnimation : _nodeToAnimationInfo)
	//				{
	//					Animation* animation = nodeToAnimation.second.Animation;
	//					animation->Release();
	//					delete animation;
	//				}

	//				_skeletonIndexToAnimation.clear();
	//				FBXLoader::Release();
	//				return true;
	//			}
	//		};

	//		AnimationFBXLoader animationLoader;
	//		animationLoader.SetNodeIndex(_nodeToAnimationInfo, _skeletonDataMap);
	//		for (auto animationFIleName : animationFileNameList)
	//		{
	//			Script script = actionList.find(animationFIleName)->second;

	//			animationLoader.Init();
	//			FbxNode* animationRoot = animationLoader.PreLoad(wtm(kFBXPath) + animationFIleName);

	//			DXFBXRootObject* animationRootObject = nullptr;
	//			if (animationRoot)
	//			{
	//				{
	//					animationRootObject = animationLoader.LoadObject(animationRoot);

	//					FbxAnimStack* animStack = animationLoader._scene->GetSrcObject<FbxAnimStack>();
	//					std::string animationName(animStack->GetName());
	//					ExtractAnimationInfoData info = animationLoader.ExtractAnimationInfo(animStack);

	//					animationLoader._script = script;
	//					animationLoader.LoadAnimation(animationName, info);

	//					delete animationRootObject;
	//				}
	//			}
	//		}

	//		for (auto& nodeToObject : _nodeToObject)
	//		{
	//			FbxNode* node = nodeToObject.first;
	//			DXObject* object = nodeToObject.second;

	//			auto& nodeToAnimationData = _nodeToAnimationInfo.find(node)->second;
	//			for (auto info : nodeToAnimationData.FrameInfo)
	//			{
	//				nodeToAnimationData.Animation->SetAdditionalAction(info.first, info.second);
	//			}
	//			object->SetAnimation(_nodeToAnimationInfo.find(node)->second.Animation);
	//		}

	//		animationLoader.Release();
	//	}

	//	return rootObject;
	//}

	//void FBXLoader::ExtractSkeletonData(FbxNode* node)
	//{
	//	FbxSkeleton* skeleton = node->GetSkeleton();
	//	if (skeleton)
	//	{
	//		_skeletonDataMap.insert(std::make_pair(node, _skeletonDataMap.size()));
	//	}

	//	for (int i = 0; i < node->GetChildCount(); ++i)
	//	{
	//		FbxNodeAttribute::EType attribute = node->GetChild(i)->GetNodeAttribute()->GetAttributeType();
	//		if (attribute == FbxNodeAttribute::eNull ||
	//			attribute == FbxNodeAttribute::eMesh ||
	//			attribute == FbxNodeAttribute::eSkeleton)
	//		{
	//			ExtractSkeletonData(node->GetChild(i));
	//		}
	//	}
	//}

	//HMatrix44 FBXLoader::Convert(FbxAMatrix matrix)
	//{
	//	HMatrix44 ret
	//	{
	//		(float)matrix.Get(0, 0), (float)matrix.Get(0, 2), (float)matrix.Get(0, 1), 0,
	//		(float)matrix.Get(2, 0), (float)matrix.Get(2, 2), (float)matrix.Get(2, 1), 0,
	//		(float)matrix.Get(1, 0), (float)matrix.Get(1, 2), (float)matrix.Get(1, 1), 0,
	//		(float)matrix.Get(3, 0), (float)matrix.Get(3, 2), (float)matrix.Get(3, 1), 1,
	//	};

	//	return ret;
	//}

	//void FBXLoader::SaveFrame(std::string name, FbxTime timer)
	//{
	//	for (auto nodeToObject : _nodeToObject)
	//	{
	//		ActionFrameInfo actionFrameInfo;
	//		actionFrameInfo.Matrix = Convert(nodeToObject.first->EvaluateGlobalTransform(timer));
	//		Decompose(actionFrameInfo.Matrix, actionFrameInfo.Scale, actionFrameInfo.Rotate, actionFrameInfo.Translate);

	//		AnimationData& animationData = _nodeToAnimationInfo.find(nodeToObject.first)->second;
	//		ActionInfo& frameInfo = animationData.FrameInfo.find(name)->second;
	//		frameInfo.FrameInfoList.push_back(actionFrameInfo);
	//	}
	//}

	//void SSB::FBXLoader::ParseNode(FbxNode* node, DXObject* object, DXFBXRootObject* rootObject)
	//{
	//	FbxMesh* mesh = node->GetMesh();
	//	if(mesh)
	//	{
	//		ParseMeshSkinningData((DXFBXMeshObject*)object, mesh);
	//		ParseMesh(node, mesh, object);
	//	}

	//	for (int i = 0; i < node->GetChildCount(); ++i)
	//	{
	//		FbxNodeAttribute::EType attribute = node->GetChild(i)->GetNodeAttribute()->GetAttributeType();
	//		if (attribute == FbxNodeAttribute::eNull ||
	//			attribute == FbxNodeAttribute::eMesh ||
	//			attribute == FbxNodeAttribute::eSkeleton)
	//		{
	//			DXObject* childObject = nullptr;
	//			if (attribute == FbxNodeAttribute::eMesh)
	//			{
	//				childObject = new DXFBXMeshObject;
	//				((DXFBXMeshObject*)childObject)->SetRootObject(rootObject);
	//				int meshIndex = _meshDataMap.size();
	//				((DXFBXMeshObject*)childObject)->SetMeshIndex(meshIndex);
	//				_meshDataMap.insert(std::make_pair(node->GetChild(i), meshIndex + 1));
	//				// Need to Remove
	//				childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DMeshObject.hlsl", "VS", "vs_5_0"));
	//				childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DMeshObject.hlsl", "PS", "ps_5_0"));
	//			}
	//			else if (attribute == FbxNodeAttribute::eSkeleton)
	//			{
	//				childObject = new DXFBXSkeletonObject;
	//				((DXFBXSkeletonObject*)childObject)->SetRootObject(rootObject);
	//				int boneIndex = _skeletonDataMap.find(node->GetChild(i))->second;
	//				((DXFBXSkeletonObject*)childObject)->SetBoneIndex(boneIndex);
	//				_skeletonIndexToObjectMap.insert(std::make_pair(boneIndex, node->GetChild(i)));
	//				// Need to Remove
	//				childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
	//				childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
	//			}
	//			else
	//			{
	//				childObject = new DXObject;
	//				 //Need to Remove
	//				childObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
	//				childObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
	//			}
	//			_nodeToObject.insert(std::make_pair(node->GetChild(i), childObject));
	//			object->SetAdditionalChildObject(childObject);
	//			ParseNode(node->GetChild(i), childObject, rootObject);
	//		}
	//	}
	//}

	//void SSB::FBXLoader::ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object)
	//{
	//	for (int iLayer = 0; iLayer < mesh->GetLayerCount(); ++iLayer)
	//	{
	//		std::map<int, FBXModel*> modelMap;

	//		FbxLayer* layer = mesh->GetLayer(iLayer);

	//		FbxAMatrix geometricMatrix;
	//		FbxVector4 trans = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	//		FbxVector4 rot = node->GetGeometricRotation(FbxNode::eSourcePivot);
	//		FbxVector4 sca = node->GetGeometricScaling(FbxNode::eSourcePivot);
	//		geometricMatrix.SetT(trans);
	//		geometricMatrix.SetR(rot);
	//		geometricMatrix.SetS(sca);

	//		FbxAMatrix normalLocalMatrix = geometricMatrix;
	//		normalLocalMatrix = normalLocalMatrix.Inverse();
	//		normalLocalMatrix = normalLocalMatrix.Transpose();

	//		//FbxVector4 translation;
	//		//if (node->LclTranslation.IsValid())
	//		//{
	//		//	translation = node->LclTranslation.Get();
	//		//}
	//		//FbxVector4 rotation;
	//		//if (node->LclRotation.IsValid())
	//		//{
	//		//	rotation = node->LclRotation.Get();
	//		//}
	//		//FbxVector4 scale;
	//		//if (node->LclScaling.IsValid())
	//		//{
	//		//	scale = node->LclScaling.Get();
	//		//}

	//		//FbxAMatrix matWorldTransform(translation, rotation, scale);
	//		//FbxAMatrix normalWorldMatrix = matWorldTransform;
	//		//normalWorldMatrix = normalWorldMatrix.Inverse();
	//		//normalWorldMatrix = normalWorldMatrix.Transpose();

	//		int polygonCount = mesh->GetPolygonCount();
	//		int iBasePolyIndex = 0;
	//		FbxVector4* vertexPosition = mesh->GetControlPoints();
	//		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
	//		{
	//			int polygonSize = mesh->GetPolygonSize(iPoly);
	//			int faceCount = polygonSize - 2;
	//			for (int iFace = 0; iFace < faceCount; ++iFace)
	//			{
	//				int iCornerIndex[3];
	//				iCornerIndex[0] = mesh->GetPolygonVertex(iPoly, 0);
	//				iCornerIndex[1] = mesh->GetPolygonVertex(iPoly, iFace + 2);
	//				iCornerIndex[2] = mesh->GetPolygonVertex(iPoly, iFace + 1);

	//				int vertexColor[3] = { 0, iFace + 2, iFace + 1 };

	//				int iuvindex[3];
	//				iuvindex[0] = mesh->gettextureuvindex(ipoly, 0);
	//				iuvindex[1] = mesh->gettextureuvindex(ipoly, iface + 2);
	//				iuvindex[2] = mesh->gettextureuvindex(ipoly, iface + 1);

	//				for (int iIndex = 0; iIndex < 3; ++iIndex)
	//				{
	//					int vertexIndex = iCornerIndex[iIndex];
	//					FbxVector4 v = vertexPosition[vertexIndex];
	//					v = geometricMatrix.MultT(v);
	//					//v = matWorldTransform.MultT(v);

	//					FbxColor c = { 0, 0, 0, 1 };
	//					FbxLayerElementVertexColor* vertexColorSet = mesh->GetElementVertexColor();
	//					if (vertexColorSet)
	//					{
	//						c = Read<FbxColor>(vertexColorSet, iCornerIndex[iIndex], iBasePolyIndex + vertexColor[iIndex]);
	//					}

	//					FbxVector2 texture{ 0, 0 };
	//					FbxLayerElementUV* uv = mesh->GetElementUV();
	//					if (uv)
	//					{
	//						texture = Read(uv, iCornerIndex[iIndex], iUVIndex[iIndex]);
	//					}

	//					FbxVector4 n{ 0, 0, 0, 0 };
	//					FbxLayerElementNormal* normal = layer->GetNormals();
	//					if (normal)
	//					{
	//						n = Read<FbxVector4>(normal, iCornerIndex[iIndex], iBasePolyIndex + vertexColor[iIndex]);
	//						n = normalLocalMatrix.MultT(n);
	//						//n = normalWorldMatrix.MultT(n);
	//					}

	//					Vertex_PNCT vertex
	//					{
	//						{ v.mData[0], v.mData[2], v.mData[1], 1 },
	//						{ n.mData[0], n.mData[2], n.mData[1], 1 },
	//						{ c.mRed, c.mGreen, c.mBlue, c.mAlpha },
	//						{ texture.mData[0], 1 - texture.mData[1] }
	//					};

	//					FbxLayerElementMaterial* MaterialSet = layer->GetMaterials();
	//					int iSubMtrl = 0;
	//					if (MaterialSet)
	//					{
	//						iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
	//					}

	//					auto iter = modelMap.find(iSubMtrl);
	//					if (iter == modelMap.end())
	//					{
	//						NewModel(node, iLayer, iSubMtrl, modelMap);
	//						iter = modelMap.find(iSubMtrl);
	//					}
	//					iter->second->_tmpVertexList.push_back(vertex);

	//					DXFBXMeshObject* meshObject = (DXFBXMeshObject*)object;
	//					meshObject->_skinningData.push_back(meshObject->_skinningDataPerVertex[vertexIndex]);
	//				}
	//			}
	//			iBasePolyIndex += mesh->GetPolygonSize(iPoly);
	//		}

	//		for (auto model : modelMap)
	//		{
	//			object->SetAdditionalModel(model.second);
	//		}
	//	}
	//}

	//void FBXLoader::NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap)
	//{
	//	FBXModel* model = new FBXModel;
	//	FbxSurfaceMaterial* surface = node->GetMaterial(materialIndex);
	//	if (surface)
	//	{
	//		auto prop = surface->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//		if (prop.IsValid())
	//		{
	//			const FbxFileTexture* tex = prop.GetSrcObject<FbxFileTexture>(layerIndex);
	//			if (tex)
	//			{
	//				auto filePath = tex->GetFileName();
	//				auto splitedPath = SplitPath(std::wstring(mtw(filePath)));
	//				if (splitedPath[3] == L".tga" || splitedPath[3] == L".TGA")
	//				{
	//					splitedPath[3] = L".DDS";
	//				}
	//				std::wstring fileName = splitedPath[2] + splitedPath[3];
	//				model->SetSprite(SpriteLoader::GetInstance().Load(fileName, DXStateManager::kDefaultWrapSample));
	//			}
	//		}
	//	}
	//	modelMap.insert(std::make_pair(materialIndex, model));
	//}

	//FBXLoader::ExtractAnimationInfoData FBXLoader::ExtractAnimationInfo(FbxAnimStack* animStack)
	//{
	//	FbxString fbxStr(animStack->GetName());
	//	FbxTakeInfo* info = _scene->GetTakeInfo(fbxStr);

	//	FbxTimeSpan timeSpan = info->mLocalTimeSpan;
	//	FbxTime startTime = timeSpan.GetStart();
	//	FbxTime endTime = timeSpan.GetStop();
	//	FbxTime duration = timeSpan.GetDirection();

	//	ExtractAnimationInfoData ret;
	//	ret.Start = startTime.GetFrameCount(FbxTime::GetGlobalTimeMode());
	//	ret.End = endTime.GetFrameCount(FbxTime::GetGlobalTimeMode());
	//	ret.TimeMode = FbxTime::GetGlobalTimeMode();

	//	return ret;
	//}

	//int SSB::FBXLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
	//{
	//	int iSubMtrl = 0;
	//	if (pMaterialSetList != nullptr)
	//	{
	//		switch (pMaterialSetList->GetMappingMode())
	//		{
	//		case FbxLayerElement::eByPolygon:
	//		{
	//			switch (pMaterialSetList->GetReferenceMode())
	//			{
	//			case FbxLayerElement::eIndex:
	//			{
	//				iSubMtrl = iPoly;
	//			}break;
	//			case FbxLayerElement::eIndexToDirect:
	//			{
	//				iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
	//			}break;
	//			}
	//		}
	//		default:
	//		{
	//			break;
	//		}
	//		}
	//	}
	//	return iSubMtrl;
	//}

	//void FBXLoader::ParseMeshSkinningData(DXFBXMeshObject* object, FbxMesh* mesh)
	//{
	//	object->_skinningDataPerVertex.resize(mesh->GetControlPointsCount());
	//	if (mesh->GetDeformerCount() == 0)
	//	{
	//		object->_meshConstantData.MeshParam.MeshWeight = 1;
	//	}
	//	else
	//	{
	//		int deformerCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
	//		for (int iDeformer = 0; iDeformer < deformerCount; ++iDeformer)
	//		{
	//			FbxDeformer* deformer = mesh->GetDeformer(iDeformer, FbxDeformer::eSkin);
	//			FbxSkin* skin = (FbxSkin*)deformer;
	//			int clusterCount = skin->GetClusterCount();
	//			for (int iCluster = 0; iCluster < clusterCount; ++iCluster)
	//			{
	//				FbxCluster* cluster = skin->GetCluster(iCluster);
	//				int boneIndex = _skeletonDataMap.find(cluster->GetLink())->second;

	//				FbxAMatrix linkMatrix;
	//				cluster->GetTransformLinkMatrix(linkMatrix);

	//				FbxAMatrix adjustMatrix;
	//				cluster->GetTransformMatrix(adjustMatrix);

	//				FbxAMatrix fbxBoneSpaceMatrix = linkMatrix.Inverse() * adjustMatrix;
	//				HMatrix44 toBoneSpaceMatrix = Convert(fbxBoneSpaceMatrix);
	//				object->SetBoneSpaceTransformMatrix(boneIndex, toBoneSpaceMatrix);

	//				int controlPointCount = cluster->GetControlPointIndicesCount();
	//				int* controlPointIndice = cluster->GetControlPointIndices();
	//				double* controlPointWeights = cluster->GetControlPointWeights();
	//				for (int iControlPoint = 0; iControlPoint < controlPointCount; ++iControlPoint)
	//				{
	//					int vertexIndex = controlPointIndice[iControlPoint];
	//					float weight = controlPointWeights[iControlPoint];
	//					object->LinkMeshWithBone(vertexIndex, boneIndex, weight);
	//				}
	//			}
	//		}
	//	}
	//}

	//DXFBXRootObject* FBXLoader::LoadObject(FbxNode* root)
	//{
	//	DXFBXRootObject* rootObject = new DXFBXRootObject;
	//	class FBXRootModel : public Model
	//	{
	//	public:
	//		void Build()
	//		{
	//			_vertexList.push_back({});
	//			_indexList.push_back(0);
	//		}
	//	};
	//	rootObject->SetAdditionalModel(new FBXRootModel);
	//	_nodeToObject.insert(std::make_pair(root, rootObject));
	//	// Need to Remove
	//	rootObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DObject.hlsl", "VS", "vs_5_0"));
	//	rootObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default3DObject.hlsl", "PS", "ps_5_0"));
	//	ExtractSkeletonData(root);
	//	ParseNode(root, rootObject, rootObject);

	//	for (auto nodeToObject : _nodeToObject)
	//	{
	//		FbxNode* node = nodeToObject.first;
	//		DXObject* object = nodeToObject.second;
	//		Animation* animation = new Animation;

	//		_nodeToAnimationInfo.insert(std::make_pair(node, AnimationData{ animation, std::map<std::string, ActionInfo>() }));
	//	}
	//	return rootObject;
	//}

	//void FBXLoader::LoadAnimation(std::string animationName, ExtractAnimationInfoData info)
	//{
	//	for (auto& nodeToAnimationInfo : _nodeToAnimationInfo)
	//	{
	//		std::map<std::string, ActionInfo>& actionData = nodeToAnimationInfo.second.FrameInfo;

	//		actionData.insert(std::make_pair(animationName, ActionInfo{ (UINT)info.End }));
	//	}

	//	for (FbxLongLong t = info.Start; t <= info.End; ++t)
	//	{
	//		FbxTime time;
	//		time.SetFrame(t, info.TimeMode);
	//		SaveFrame(animationName, time);
	//	}

	//	for (auto& nodeToAnimationInfo : _nodeToAnimationInfo)
	//	{
	//		Animation* animation = nodeToAnimationInfo.second.Animation;
	//		std::map<std::string, ActionInfo>& actionData = nodeToAnimationInfo.second.FrameInfo;

	//		animation->SetAdditionalAction(animationName, actionData.find(animationName)->second);
	//	}

	//	for (auto& nodeToObject : _nodeToObject)
	//	{
	//		FbxNode* node = nodeToObject.first;
	//		DXObject* object = nodeToObject.second;
	//		object->SetAnimation(_nodeToAnimationInfo.find(node)->second.Animation);
	//	}
	//}
}
