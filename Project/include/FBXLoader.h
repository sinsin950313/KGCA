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
			HMatrix44 AnimatedBoneMatrix[255];	// Bone Index
			HMatrix44 AnimatedMeshMatrix[255];	// Mesh Index
		};

	private:
		ObjectAnimationData _objectAnimationData;
		ID3D11Buffer* _objectAnimationDataBuffer;

	public:
		~DXFBXRootObject() { Release(); }

	public:
		void UpdateAnimatedBoneData(int boneIndex, HMatrix44 matrix);
		void UpdateAnimatedMeshData(int meshIndex, HMatrix44 matrix);

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
		struct MeshParam
		{
			float MeshIndex;
			float MeshWeight = 0;
			float padding[2];
		};
		struct MeshConstantData
		{
			HMatrix44 ToBoneSpaceMatrixData[255];
			MeshParam MeshParam;
		};

	private:
		std::vector<SkinningData> _skinningDataPerVertex;
		std::vector<SkinningData> _skinningData;
		ID3D11Buffer* _skinningDataBuffer;
		MeshConstantData _meshConstantData;
		ID3D11Buffer* _meshConstantBuffer;
		DXFBXRootObject* _root;
		int _meshIndex;

	public:
		~DXFBXMeshObject() { Release(); }

	private:
		void SetRootObject(DXFBXRootObject* root) { _root = root; }
		void SetMeshIndex(int meshIndex) { _meshIndex = meshIndex; _meshConstantData.MeshParam.MeshIndex = meshIndex; }
		void SetBoneSpaceTransformMatrix(int boneIndex, HMatrix44 toBoneSpaceTransform) { _meshConstantData.ToBoneSpaceMatrixData[boneIndex] = toBoneSpaceTransform.Transpose(); }
		void LinkMeshWithBone(int vertexIndex, int boneIndex, float weight);

	private:
		bool CreateVertexBuffer() override;
		bool CreateConstantBuffer() override;
		void UpdateConstantBuffer() override;
		void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc) override;
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;

	public:
		bool Frame() override;
		bool Release() override;

		friend class FBXLoader;
	};

	class FBXLoader : public Common
	{
	private:
		struct ExtractAnimationInfoData
		{
			FbxLongLong Start;
			FbxLongLong End;
			FbxTime::EMode TimeMode;
		};
		struct AnimationData
		{
			Animation* Animation;
			std::map<std::string, ActionInfo> FrameInfo;
		};
		struct Script
		{
			std::string ActionName;
			int EndFrame;
		};

	private:
		FbxManager* _manager;
		FbxImporter* _importer;
		FbxScene* _scene;
		std::map<FbxNode*, int> _skeletonDataMap;
		std::map<int, FbxNode*> _skeletonIndexToObjectMap;
		std::map<FbxNode*, int> _meshDataMap;

		float _frameSpeed = 30.0f;
		float _tickPerFrame = 160;
		std::map<FbxNode*, DXObject*> _nodeToObject;
		std::map<FbxNode*, AnimationData> _nodeToAnimationInfo;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void ExtractSkeletonData(FbxNode* node);
		HMatrix44 Convert(FbxAMatrix matrix);
		ExtractAnimationInfoData ExtractAnimationInfo(FbxAnimStack* animStack);
		void SaveFrame(std::string name, FbxTime timer);
		void ParseNode(FbxNode* node, DXObject* object, DXFBXRootObject* rootObject);
		void ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object);
		void NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap);
		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);
		int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
		void ParseMeshSkinningData(DXFBXMeshObject* object, FbxMesh* mesh);
		FbxNode* PreLoad(std::string fileName);
		DXFBXRootObject* LoadObject(FbxNode* root);
		virtual void LoadAnimation(std::string animationName, ExtractAnimationInfoData info);
		std::vector<Script> ParseScript(std::string fileName);

	private:
		template<typename T>
		T Read(FbxLayerElementTemplate<T>* element, int position, int index);

	public:
		DXObject* Load(std::string fileName);
		DXObject* Load(std::string fileName, std::string scriptFileName);
		DXObject* Load(std::string fileName, std::vector<std::string> animationFileNameList);
		DXObject* Load(std::string fileName, std::vector<std::string> animationFileNameList, std::string animationScriptFileName);

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
