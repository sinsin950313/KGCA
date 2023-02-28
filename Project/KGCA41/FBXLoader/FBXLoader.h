#pragma once

#include "Common.h"
#include <fbxsdk.h>
#include <map>
#include "Model.h"
#include "Mesh.h"
#include "Material.h"

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
		std::map<FbxNode*, int> _skeletonNodeToSkeletonIndexMap;
		std::map<FbxNode*, int> _meshNodeToMeshIndexMap;

		std::map<MaterialIndex, Material*> _indexToMaterialMap;

		std::map<MeshIndex, MeshInterface*> _indexToMeshMap;

		//float _frameSpeed = 30.0f;
		//float _tickPerFrame = 160;
		//AnimationFrameInfo _animationInfo;

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
		void ExtractTextureFileName(FbxFileTexture* texture, Material* material, TextureType textureType);

		void ParseMesh();
		void RegisterMesh(MeshInterface* mesh);

		//void ParseAnimation();

	public:
		void SetFileName(std::string fileName);
		std::map<MaterialIndex, Material*> LoadMaterial();
		Model* LoadModel();
		//Animation* LoadAnimation();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
