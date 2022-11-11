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

	class DXFBXRootObject : public DXObject
	{
	private:
		struct ObjectAnimationData
		{
			//HMatrix44 MeshWorldInverseMatrix[255];
			HMatrix44 AnimatedBoneMatrix[255];	// Bone Index
			HMatrix44 TransformBoneBasedSpace[255];	// Mesh Index
		};

	private:
		ObjectAnimationData _objectAnimationData;
		ID3D11Buffer* _objectAnimationDataBuffer;

	public:
		~DXFBXRootObject() { Release(); }

	public:
		void UpdateAnimatedBoneData(int boneIndex, HMatrix44 matrix);
		//void UpdateMeshWorldAnimationData(int meshIndex, HMatrix44 matrix);

	private:
		void SetTransformBoneBasedSpaceMatrix(int meshIndex, HMatrix44 transformBoneBasedSpaceMatrix);

	private:
		bool CreateConstantBuffer() override;
		void UpdateConstantBuffer() override;

	public:
		bool Release() override;
		void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc) override;

		friend class FBXLoader;
	};

	class DXFBXSkeletonObject : public DXObject
	{
	private:
		DXFBXRootObject* _root;
		int _boneIndex;

	public:
		~DXFBXSkeletonObject() { Release(); }

	public:
		void SetRootObject(DXFBXRootObject* root) { _root = root; }
		void SetBoneIndex(int index) { _boneIndex = index; }

	public:
		bool Frame() override;
		bool Release() override;
	};

	class DXFBXMeshObject : public DXObject
	{
	private:
		struct SkinningData
		{
			int AffectingBoneIndex[4]{ 0, };
			float Weight[4]{ 0, };
		};

	private:
		int _meshIndex;
		ID3D11Buffer* _meshConstantBuffer;
		std::vector<SkinningData> _skinningDataPerVertex;
		std::vector<SkinningData> _skinningData;
		ID3D11Buffer* _skinningDataBuffer;

	public:
		~DXFBXMeshObject() { Release(); }

	private:
		void LinkMeshWithBone(int vertexIndex, int boneIndex, float weight);

	private:
		bool CreateVertexBuffer() override;
		bool CreateConstantBuffer() override;
		void UpdateConstantBuffer() override;
		void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc) override;
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;

	public:
		bool Release() override;

	public:
		void SetMeshIndex(int index) { _meshIndex = index; }

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
		std::map<FbxNode*, int> _skeletonDataMap;
		std::map<FbxNode*, int> _meshDataMap;

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
