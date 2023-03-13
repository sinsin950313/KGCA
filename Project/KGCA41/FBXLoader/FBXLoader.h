#pragma once

#include "Common.h"
#include <fbxsdk.h>
#include <map>
#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "FBXMaterial.h"
#include "FBXBone.h"
#include "Bone.h"

namespace SSB
{
	class FBXLoader : public Common
	{
	private:
		//struct ExtractAnimationInfoData
		//{
		//	FbxLongLong Start;
		//	FbxLongLong End;
		//	FbxTime::EMode TimeMode;
		//};
		//struct AnimationData
		//{
		//	Animation* Animation;
		//	std::map<std::string, ActionInfo> FrameInfo;
		//};

	private:
		FbxManager* _manager;
		FbxImporter* _importer;
		FbxScene* _scene;

		FbxNode* _root;
		std::map<FbxNode*, int> _boneNodeToBoneIndexMap;
		std::map<FbxNode*, int> _meshNodeToMeshIndexMap;

		std::map<FBXBoneKey, FBXBoneData> _fbxBoneKeyToFbxBoneMap;
		std::map<FBXMaterialKey, FBXMaterialData> _fbxMaterialKeyToFbxMaterialMap;

		std::map<MeshIndex, MeshInterface*> _indexToMeshMap;

		float _frameSpeed = 30.0f;
		float _tickPerFrame = 160;
		std::map<std::string, Animation*> _animations;

		PixelShader* _ps;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void PreLoad(std::string fileName);
		void ParseNode(FbxNode* node);
		void RegisterBoneNode(FbxNode* node);
		void RegisterMeshNode(FbxNode* node);

		void ExtractMaterial();
		//void ExtractTexture(FbxProperty* fbxProperty, Material* material, TextureType textureType);
		//void ExtractTextureFileName(FbxTexture* texture, Material* material, TextureType textureType);
		std::wstring ExtractTextureFileName(FbxFileTexture* texture, Material* material);

		void ParseMesh();
		void RegisterMesh(MeshInterface* mesh);

		void ParseAnimation();
		HMatrix44 Convert(FbxAMatrix matrix);

	public:
		void SetFileName(std::string fileName);
		std::map<MaterialIndex, Material*> LoadMaterial();
		Model* LoadModel();
		std::map<std::string, Animation*> LoadAnimation();
		Skeleton* LoadSkeleton();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	private:
		std::string _actionName;
		int _endFrame;

	public:
		bool HasAnimation();
		std::string GetDefaultActionName();
		int GetEndFrame();
	};
}
