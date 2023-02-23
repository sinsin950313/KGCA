#pragma once

#include "Common.h"
#include <fbxsdk.h>
#include <vector>
#include "Model.h"
#include "DXObject.h"

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
		struct Script
		{
			std::string ActionName;
			FrameIndex StartFrame;
			FrameIndex EndFrame;
		};

	private:
		FbxManager* _manager;
		FbxImporter* _importer;
		FbxScene* _scene;

		float _frameSpeed = 30.0f;
		float _tickPerFrame = 160;

		std::map<int, FbxSurfaceMaterial*> _indexToMaterialMap;
		std::map<FbxNode*, int> _skeletonNodeToSkeletonIndexMap;
		std::map<FbxNode*, int> _meshNodeToMeshIndexMap;

		AnimationFrameInfo _animationInfo;
		std::map<MeshIndex, Mesh*> _meshInfo;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void ExtractMaterial();
		void ExtractTexture(FbxSurfaceMaterial* material);
		FbxNode* PreLoad(std::string fileName);
		void ParseNode(FbxNode* node);
		void RegisterBoneNode(FbxNode* node);
		void RegisterMeshNode(FbxNode* node);
		std::vector<Script> ParseScript(std::string fileName);
		void ExtractMeshVertex(FbxMesh* fbxMesh, Mesh* mesh, FbxAMatrix geometricMatrix, FbxAMatrix normalLocalMatrix);
		void ExtractMeshVertexIndex(FbxMesh* fbxMesh, Mesh* mesh);
		void RegisterMesh(Mesh* mesh);
		void RegisterMaterialToMesh(Mesh* mesh);
		void ParseMesh();
		void ParseAnimation();
		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);

		//void ExtractSkeletonData(FbxNode* node);
		//HMatrix44 Convert(FbxAMatrix matrix);
		//ExtractAnimationInfoData ExtractAnimationInfo(FbxAnimStack* animStack);
		//void SaveFrame(std::string name, FbxTime timer);
		//void ParseNode(FbxNode* node, DXObject* object, DXFBXRootObject* rootObject);
		//void ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object);
		//void NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap);
		//void ParseMeshSkinningData(DXFBXMeshObject* object, FbxMesh* mesh);
		//DXFBXRootObject* LoadObject(FbxNode* root);
		//virtual void LoadAnimation(std::string animationName, ExtractAnimationInfoData info);
		//int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);

	private:
		template<typename T>
		T Read(FbxLayerElementTemplate<T>* element, int position, int index);

	public:
		//AnimationFrameInfo LoadAnimation(std::string fileName);
		std::map<MeshIndex, Mesh*> LoadMesh(std::string fileName);

		//DXObject* Load(std::string fileName);
		//DXObject* Load(std::string fileName, std::string scriptFileName);
		//DXObject* Load(std::string fileName, std::vector<std::string> animationFileNameList);
		//DXObject* Load(std::string fileName, std::vector<std::string> animationFileNameList, std::string animationScriptFileName);

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
