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
		void ExtractTexture(FbxProperty* fbxProperty, Material* material, TextureType textureType);
		void ExtractTextureFileName(FbxTexture* texture, Material* material, TextureType textureType);

		struct MeshTransformData
		{
			FbxAMatrix Geomatric;
			FbxAMatrix NormalLocal;
		};
		struct MeshVertexInfo
		{
			MeshInterface* Mesh;
			int MeshVertexSize;
		};
		void ParseMesh();
		MeshTransformData CalculateTransformData(FbxNode* node);
		MeshVertexInfo GetMeshVertexInfo();
		void ExtractMeshVertex(FbxMesh* fbxMesh, MeshTransformData transformData, MeshVertexInfo meshVertexInfo);
		void ExtractMeshVertexIndex(FbxMesh* fbxMesh, MeshInterface* mesh);
		void RegisterMesh(MeshInterface* mesh);

		//void ParseAnimation();

		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);

	private:
		template<typename T>
		T Read(FbxLayerElementTemplate<T>* element, int position, int index);

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

	template<typename T>
	inline T FBXLoader::Read(FbxLayerElementTemplate<T>* element, int pointIndex, int polygonIndex)
	{
		T t;
		switch (element->GetMappingMode())
		{
		case FbxLayerElement::eByControlPoint:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				t = element->GetDirectArray().GetAt(pointIndex);
				break;
			}
			case FbxLayerElement::eIndexToDirect:
			{
				int index = element->GetIndexArray().GetAt(pointIndex);
				t = element->GetDirectArray().GetAt(index);
				break;
			}
			}
			break;
		}
		case FbxLayerElement::eByPolygonVertex:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				t = element->GetDirectArray().GetAt(polygonIndex);
				break;
			}
			case FbxLayerElement::eIndexToDirect:
			{
				int index = element->GetIndexArray().GetAt(polygonIndex);
				t = element->GetDirectArray().GetAt(index);
				break;
			}
			}
			break;
		}
		}
		return t;
	}
}
