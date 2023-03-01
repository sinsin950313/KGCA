#include "FBXMesh.h"
#include "FBXMesh.hpp"
#include "CommonUtility.h"

namespace SSB
{
	FBXMeshInterface::MeshTransformData FBXMeshInterface::CalculateTransformData(FbxNode* node)
	{
		FbxAMatrix geometricMatrix;
		FbxVector4 trans = node->GetGeometricTranslation(FbxNode::eSourcePivot);
		FbxVector4 rot = node->GetGeometricRotation(FbxNode::eSourcePivot);
		FbxVector4 sca = node->GetGeometricScaling(FbxNode::eSourcePivot);
		geometricMatrix.SetT(trans);
		geometricMatrix.SetR(rot);
		geometricMatrix.SetS(sca);

		FbxAMatrix normalLocalMatrix = geometricMatrix;
		normalLocalMatrix = normalLocalMatrix.Inverse();
		normalLocalMatrix = normalLocalMatrix.Transpose();

		return { geometricMatrix, normalLocalMatrix };
	}

	MaterialIndex FBXLayerElementReader::GetMaterialIndex(FbxMesh* fbxMesh, int polygonIndex, int layerIndex, std::map<FBXMaterialKey, FBXMaterialData>& fbxMaterialKeyToFbxMaterialDataMap)
	{
		FbxLayer* layer = fbxMesh->GetLayer(layerIndex);
		FbxLayerElementMaterial* materialSet = layer->GetMaterials();
		int subMaterialIndex = GetSubMaterialIndex(polygonIndex, materialSet);

		MaterialIndex ret = -1;
		FbxSurfaceMaterial* surface = fbxMesh->GetNode()->GetMaterial(subMaterialIndex);
		if (surface)
		{
			auto prop = surface->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (prop.IsValid())
			{
				const FbxFileTexture* tex = prop.GetSrcObject<FbxFileTexture>(layerIndex);
				if (tex)
				{
					auto filePath = tex->GetFileName();
					auto splitedPath = SplitPath(mtw(filePath));
					std::wstring fileName = splitedPath[2] + splitedPath[3];
					ret = fbxMaterialKeyToFbxMaterialDataMap.find(wtm(fileName))->second.Index;
				}
			}
		}

		assert(ret != -1);

		return ret;
	}

	int FBXLayerElementReader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
	{
		int iSubMtrl = 0;
		if (pMaterialSetList != nullptr)
		{
			switch (pMaterialSetList->GetMappingMode())
			{
			case FbxLayerElement::eByPolygon:
			{
				switch (pMaterialSetList->GetReferenceMode())
				{
				case FbxLayerElement::eIndex:
				{
					iSubMtrl = iPoly;
				}break;
				case FbxLayerElement::eIndexToDirect:
				{
					iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
				}break;
				}
			}
			default:
			{
				break;
			}
			}
		}
		return iSubMtrl;
	}

	HMatrix44 FBXLayerElementReader::Convert(FbxAMatrix matrix)
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

	FbxVector2 FBXLayerElementReader::Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex)
	{
		FbxVector2 t;
		FbxLayerElement::EMappingMode mode = element->GetMappingMode();
		switch (mode)
		{
		case FbxLayerElementUV::eByControlPoint:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElementUV::eDirect:
			{
				t = element->GetDirectArray().GetAt(pointIndex);
				break;
			}
			case FbxLayerElementUV::eIndexToDirect:
			{
				int index = element->GetIndexArray().GetAt(pointIndex);
				t = element->GetDirectArray().GetAt(index);
				break;
			}
			break;
			}
		}
		case FbxLayerElementUV::eByPolygonVertex:
		{
			switch (element->GetReferenceMode())
			{
			case FbxLayerElementUV::eDirect:
			case FbxLayerElementUV::eIndexToDirect:
			{
				t = element->GetDirectArray().GetAt(polygonIndex);
				break;
			}
			}
			break;
		}
		}
		return t;
	}

	void FBXMesh_PCNT::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNT> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, vertice);

			VertexRefiner<Vertex_PCNT> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNT* subMesh = new FBXMesh_PCNT;

			std::vector<Vertex_PCNT> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, vertice);

			VertexRefiner<Vertex_PCNT> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNT::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNTs> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, _fbxMaterialKeyToFbxMaterialMap, vertice);

			VertexRefiner<Vertex_PCNTs> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNTs* subMesh = new FBXMesh_PCNTs;

			std::vector<Vertex_PCNTs> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, _fbxMaterialKeyToFbxMaterialMap, vertice);

			VertexRefiner<Vertex_PCNTs> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNTs::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs::Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap)
	{
		_fbxMaterialKeyToFbxMaterialMap = fbxMaterialKeyToFbxMaterialMap;
	}
	void FBXMesh_PCNT_Skinning::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNT_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, vertice);

			MeshToBoneSpaceTransformData transformData;
			ExtractMeshVertexSkinningData(_fbxMesh, _fbxBoneKeyToFbxBoneDataMap, vertice, transformData);

			VertexRefiner<Vertex_PCNT_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
			SetMeshData(transformData);
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNT_Skinning* subMesh = new FBXMesh_PCNT_Skinning;

			std::vector<Vertex_PCNT_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, vertice);

			MeshToBoneSpaceTransformData transformData;
			ExtractMeshVertexSkinningData(_fbxMesh, _fbxBoneKeyToFbxBoneDataMap, vertice, transformData);

			VertexRefiner<Vertex_PCNT_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());
			SetMeshData(transformData);

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNT_Skinning::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNT_Skinning::Initialize_SetBoneData(std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneDataMap)
	{
		fbxBoneKeyToFbxBoneDataMap = fbxBoneKeyToFbxBoneDataMap;
	}
	void FBXMesh_PCNTs_Skinning::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNTs_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, _fbxMaterialKeyToFbxMaterialMap, vertice);

			MeshToBoneSpaceTransformData transformData;
			ExtractMeshVertexSkinningData(_fbxMesh, _fbxBoneKeyToFbxBoneDataMap, vertice, transformData);

			VertexRefiner<Vertex_PCNTs_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
			SetMeshData(transformData);
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNTs_Skinning* subMesh = new FBXMesh_PCNTs_Skinning;

			std::vector<Vertex_PCNTs_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, _fbxMaterialKeyToFbxMaterialMap, vertice);

			MeshToBoneSpaceTransformData transformData;
			ExtractMeshVertexSkinningData(_fbxMesh, _fbxBoneKeyToFbxBoneDataMap, vertice, transformData);

			VertexRefiner<Vertex_PCNTs_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());
			SetMeshData(transformData);

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNTs_Skinning::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs_Skinning::Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap)
	{
		_fbxMaterialKeyToFbxMaterialMap = fbxMaterialKeyToFbxMaterialMap;
	}
	void FBXMesh_PCNTs_Skinning::Initialize_SetBoneData(std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneDataMap)
	{
		_fbxBoneKeyToFbxBoneDataMap = fbxBoneKeyToFbxBoneDataMap;
	}
	void FBXMesh_PCNT_Animatable::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNT> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);

			VertexRefiner<Vertex_PCNT> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNT_Animatable* subMesh = new FBXMesh_PCNT_Animatable;

			std::vector<Vertex_PCNT> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);

			VertexRefiner<Vertex_PCNT> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNT_Animatable::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs_Animatable::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNTs> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, _fbxMaterialKeyToFbxMaterialMap, vertice);

			VertexRefiner<Vertex_PCNTs> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNTs_Animatable* subMesh = new FBXMesh_PCNTs_Animatable;

			std::vector<Vertex_PCNTs> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, _fbxMaterialKeyToFbxMaterialMap, vertice);

			VertexRefiner<Vertex_PCNTs> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNTs_Animatable::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs_Animatable::Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap)
	{
		_fbxMaterialKeyToFbxMaterialMap = fbxMaterialKeyToFbxMaterialMap;
	}
}
