#include "FBXMesh.h"
#include "FBXMesh.hpp"

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
			ExtractMeshVertexTextureUV(_fbxMesh, 0, vertice);

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
			ExtractMeshVertexTextureUV(_fbxMesh, i, vertice);

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
	void FBXMesh_PCNT_Skinning::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNT_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, vertice);

			VertexRefiner<Vertex_PCNT_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNT_Skinning* subMesh = new FBXMesh_PCNT_Skinning;

			std::vector<Vertex_PCNT_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, vertice);

			VertexRefiner<Vertex_PCNT_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNT_Skinning::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs_Skinning::Build()
	{
		auto transformData = CalculateTransformData(_fbxMesh->GetNode());
		{
			std::vector<Vertex_PCNTs_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, 0, vertice);
			ExtractMeshVertexNormal(_fbxMesh, 0, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, 0, vertice);

			VertexRefiner<Vertex_PCNTs_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			SetVertexList(refiner.GetVertexList());
			SetIndexList(refiner.GetIndexList());
		}

		for (int i = 1; i < _fbxMesh->GetLayerCount(); ++i)
		{
			FBXMesh_PCNTs_Skinning* subMesh = new FBXMesh_PCNTs_Skinning;

			std::vector<Vertex_PCNTs_Skinning> vertice;
			ExtractMeshVertexPosition(_fbxMesh, vertice);
			ExtractMeshVertexColor(_fbxMesh, i, vertice);
			ExtractMeshVertexNormal(_fbxMesh, i, vertice);
			ExtractMeshVertexTextureUV(_fbxMesh, i, vertice);

			VertexRefiner<Vertex_PCNTs_Skinning> refiner;
			refiner.Refine(_fbxMesh, vertice);
			subMesh->SetVertexList(refiner.GetVertexList());
			subMesh->SetIndexList(refiner.GetIndexList());

			Initialize_AddSubMesh(subMesh);
		}
	}
	void FBXMesh_PCNTs_Skinning::Initialize_SetFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
}
