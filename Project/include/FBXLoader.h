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
		//std::vector<DXObject*> _objectList;
		DXObject* _rootObject;

	public:
		FBXLoader();
		~FBXLoader();

	private:
		void Load();
		HMatrix44 Convert(FbxAMatrix matrix);
		void LoadAnimation(FbxAnimStack* animStack, FbxNode* node, DXObject* object);
		void ParseNode(FbxNode* node, DXObject* object);
		void ParseMesh(FbxNode* node, FbxMesh* mesh, DXObject* object);
		void NewModel(FbxNode* node, int layerIndex, int materialIndex, std::map<int, FBXModel*>& modelMap);
		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);
		int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);

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
