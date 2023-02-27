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

	void FBXLayerElementReader::ExtractMeshVertexIndex()
	{
		std::vector<DWORD> vertexIndexList;
		int polygonCount = _fbxMesh->GetPolygonCount();
		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = _fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int iCornerIndex[3];
				iCornerIndex[0] = _fbxMesh->GetPolygonVertex(iPoly, 0);
				iCornerIndex[1] = _fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				iCornerIndex[2] = _fbxMesh->GetPolygonVertex(iPoly, iFace + 1);

				vertexIndexList.push_back(iCornerIndex[0]);
				vertexIndexList.push_back(iCornerIndex[1]);
				vertexIndexList.push_back(iCornerIndex[2]);
			}
		}

		SetIndexList(vertexIndexList);
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

		for (int i = 0; i < _fbxMesh->GetLayerCount(); ++i)
		{
			? ? ? ;
			ExtractMeshVertexPosition(transformData.Geomatric);
			ExtractMeshVertexColor();
			ExtractMeshVertexNormal(transformData.NormalLocal);
			ExtractMeshVertexTexture();
			ExtractMeshVertexIndex();
		}
	}
	void FBXMesh_PCNT::InitialFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs::InitialFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNT_Skinning::InitialFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
	void FBXMesh_PCNTs_Skinning::InitialFBXMesh(FbxMesh* fbxMesh)
	{
		_fbxMesh = fbxMesh;
	}
}
