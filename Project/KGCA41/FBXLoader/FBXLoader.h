#pragma once

#include "Common.h"
#include <fbxsdk.h>
#include <vector>
#include "DXObject.h"

namespace SSB
{
	class FBXModel : public Model
	{
	private:
		std::vector<Vertex_PNCT> _tmpVertexList;

	public:
		void Build();

		friend class FBXLoader;
	};

	struct SkeletonAnimationData
	{
		HMatrix44 ToBoneSpaceMatrix[255];
		HMatrix44 ToWorldSpaceMatrix[255];
	};

	class DXFBXRootObject : public DXObject
	{
	private:
		SkeletonAnimationData _skeletonAnimationData;
		ID3D11Buffer* _skeletonAnimationDataBuffer;
		int _boneIndexCounter = 0;
		std::map<FbxNode*, int> _skeletonDataMap;

	public:
		~DXFBXRootObject() { Release(); }

	private:
		void SetAdditionalBone(FbxNode* node);
		int FindBoneIndex(FbxNode* node);
		void SetBoneSpaceMatrix(int boneIndex, HMatrix44 toBoneSpace);

	private:
		bool CreateConstantBuffer() override;
		void UpdateConstantBuffer() override;

	public:
		bool Release() override;
		bool Render() override;
		void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc) override;

		friend class FBXLoader;
	};

	//class DXFBXSkeletonObject : public DXObject
	//{
	//private:
	//	DXFBXRootObject* _root;
	//	int _boneIndex;

	//public:
	//	~DXFBXSkeletonObject() { Release(); }

	//public:
	//	void SetRootObject(DXFBXRootObject* root) { _root = root; }
	//	void SetBoneIndex(int index) { _boneIndex = index; }

	//public:
	//	bool Frame() override;
	//	bool Release() override;
	//};

	struct SkinningData
	{
		int AffectingBoneIndex[4]{ 0, };
		float Weight[4]{ 0, };
	};

	class DXFBXMeshObject : public DXObject
	{
	private:
		std::vector<SkinningData> _skinningDataList;
		ID3D11Buffer* _skinningDataBuffer;

	public:
		~DXFBXMeshObject() { Release(); }

	private:
		void LinkMeshWithBone(int vertexIndex, int boneIndex, float weight);

	private:
		bool CreateVertexBuffer() override;
		void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc) override;
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;

	public:
		bool Release() override;

		friend class FBXLoader;
	};

	class FBXLoader : public Common
	{
	private:
		std::string _fileName;
		FbxManager* _manager;
		FbxImporter* _importer;
		FbxScene* _scene;
		FbxNode* _root;
		//std::vector<FbxMesh*> _meshList;

	public:
		DXFBXRootObject* _rootObject;
		//DXObject* _rootObject;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void Load();
		void ExtractSkeletonData(FbxNode* node);
		HMatrix44 Convert(FbxAMatrix matrix);
		void LoadAnimation(FbxAnimStack* animStack, FbxNode* node, DXObject* object);
		void ParseNode(FbxNode* node, DXObject* object);
		void ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object);
		void NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap);
		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);
		int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
		//void ParseSkeleton();
		void ParseMeshSkinningData(DXFBXMeshObject* object, FbxMesh* mesh);

	private:
		template<typename T>
		T Read(FbxLayerElementTemplate<T>* element, int position, int index);

	public:
		void SetFileName(std::string fileName) { _fileName = fileName; }

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
