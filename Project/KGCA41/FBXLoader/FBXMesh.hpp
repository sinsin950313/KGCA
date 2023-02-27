#pragma once

#include "FBXMesh.h"

namespace SSB
{
	template<typename T>
	inline T FBXLayerElementReader::Read(FbxLayerElementTemplate<T>* element, int position, int index)
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

	void FBXLoader::ExtractMeshVertexInfo(FbxMesh* fbxMesh, MeshTransformData transformData, MeshVertexInfo meshVertexInfo)
	{
		//int vertexCount = fbxMesh->GetControlPointsCount();
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int layerCount = fbxMesh->GetLayerCount();
		for (int i = 0; i < layerCount; ++i)
		{

		}

		auto colors = fbxMesh->GetLayer(0)->GetVertexColors();
		auto UVs = fbxMesh->GetLayer(0)->GetUVs();
		auto normals = fbxMesh->GetLayer(0)->GetNormals();
		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int polygonVertexIndex[3];
				polygonVertexIndex[0] = fbxMesh->GetPolygonVertex(iPoly, 0);
				polygonVertexIndex[1] = fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				polygonVertexIndex[2] = fbxMesh->GetPolygonVertex(iPoly, iFace + 1); 

				int iUVIndex[3];
				iUVIndex[0] = fbxMesh->GetTextureUVIndex(iPoly, 0);
				iUVIndex[1] = fbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
				iUVIndex[2] = fbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

				for (int iIndex = 0; iIndex < 3; ++iIndex)
				{
					int vertexIndex = polygonVertexIndex[iIndex];

					FbxVector4 v = vertice[vertexIndex];
					v = transformData.Geomatric.MultT(v);

					FbxColor c = { 0, 0, 0, 1 };
					if (colors)
					{
						c = Read<FbxColor>(colors, vertexIndex, iPoly);
					}

					FbxVector2 texture{ 0, 0 };
					if (UVs)
					{
						texture = Read(UVs, vertexIndex, iUVIndex[iIndex]);
					}

					FbxVector4 n{ 0, 0, 0, 0 };
					if (normals)
					{
						n = Read<FbxVector4>(normals, vertexIndex, iPoly);
						n = transformData.NormalLocal.MultT(n);
					}

					Vertex_PCNT vertex
					{
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha }
						},
						{ n.mData[0], n.mData[2], n.mData[1], 1 },
						{ texture.mData[0], 1 - texture.mData[1] }
					};

					void* ptr = *vertexDataBlock;
					memcpy(ptr + , &vertex, sizeof(Vertex_PCNT));
				}
			}
		}

		meshVertexInfo.Mesh->SetVertexList(*vertexDataBlock, vertexCount);
	}

	void FBXLoader::ExtractMeshVertexInfo(FbxMesh* fbxMesh, MeshTransformData transformData, MeshVertexInfo meshVertexInfo)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int layerCount = fbxMesh->GetLayerCount();
		for (int i = 0; i < layerCount; ++i)
		{

		}

		auto colors = fbxMesh->GetLayer(0)->GetVertexColors();
		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int polygonVertexIndex[3];
				polygonVertexIndex[0] = fbxMesh->GetPolygonVertex(iPoly, 0);
				polygonVertexIndex[1] = fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				polygonVertexIndex[2] = fbxMesh->GetPolygonVertex(iPoly, iFace + 1); 

				for (int iIndex = 0; iIndex < 3; ++iIndex)
				{
					int vertexIndex = polygonVertexIndex[iIndex];
					FbxColor c = { 0, 0, 0, 1 };
					if (colors)
					{
						c = Read<FbxColor>(colors, vertexIndex, iPoly);
					}

					Vertex_PCNT vertex
					{
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha }
						},
						{ n.mData[0], n.mData[2], n.mData[1], 1 },
						{ texture.mData[0], 1 - texture.mData[1] }
					};
				}
			}
		}
	}

	void FBXLoader::ExtractMeshVertexInfo(FbxMesh* fbxMesh, MeshTransformData transformData, MeshVertexInfo meshVertexInfo)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int layerCount = fbxMesh->GetLayerCount();
		for (int i = 0; i < layerCount; ++i)
		{

		}

		auto UVs = fbxMesh->GetLayer(0)->GetUVs();
		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int polygonVertexIndex[3];
				polygonVertexIndex[0] = fbxMesh->GetPolygonVertex(iPoly, 0);
				polygonVertexIndex[1] = fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				polygonVertexIndex[2] = fbxMesh->GetPolygonVertex(iPoly, iFace + 1); 

				int iUVIndex[3];
				iUVIndex[0] = fbxMesh->GetTextureUVIndex(iPoly, 0);
				iUVIndex[1] = fbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
				iUVIndex[2] = fbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

				for (int iIndex = 0; iIndex < 3; ++iIndex)
				{
					int vertexIndex = polygonVertexIndex[iIndex];
					FbxVector2 texture{ 0, 0 };
					if (UVs)
					{
						texture = Read(UVs, vertexIndex, iUVIndex[iIndex]);
					}

					Vertex_PCNT vertex
					{
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha }
						},
						{ n.mData[0], n.mData[2], n.mData[1], 1 },
						{ texture.mData[0], 1 - texture.mData[1] }
					};
				}
			}
		}
	}

	void FBXLoader::ExtractMeshVertexInfo(FbxMesh* fbxMesh, MeshTransformData transformData, MeshVertexInfo meshVertexInfo)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int layerCount = fbxMesh->GetLayerCount();
		for (int i = 0; i < layerCount; ++i)
		{

		}

		auto normals = fbxMesh->GetLayer(0)->GetNormals();
		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int polygonVertexIndex[3];
				polygonVertexIndex[0] = fbxMesh->GetPolygonVertex(iPoly, 0);
				polygonVertexIndex[1] = fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				polygonVertexIndex[2] = fbxMesh->GetPolygonVertex(iPoly, iFace + 1); 

				for (int iIndex = 0; iIndex < 3; ++iIndex)
				{
					int vertexIndex = polygonVertexIndex[iIndex];
					FbxVector4 n{ 0, 0, 0, 0 };
					if (normals)
					{
						n = Read<FbxVector4>(normals, vertexIndex, iPoly);
						n = transformData.NormalLocal.MultT(n);
					}

					Vertex_PCNT vertex
					{
						{
							{ v.mData[0], v.mData[2], v.mData[1], 1 },
							{ c.mRed, c.mGreen, c.mBlue, c.mAlpha }
						},
						{ n.mData[0], n.mData[2], n.mData[1], 1 },
						{ texture.mData[0], 1 - texture.mData[1] }
					};
				}
			}
		}
	}

	template<typename VertexType>
	inline void FBXLayerElementReader::ExtractMeshVertexPosition(FbxMesh* fbxMesh, std::vector<VertexType>& vertexList)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		for (int iPoly = 0; iPoly < polygonCount; ++iPoly)
		{
			int polygonSize = fbxMesh->GetPolygonSize(iPoly);
			int faceCount = polygonSize - 2;
			for (int iFace = 0; iFace < faceCount; ++iFace)
			{
				int polygonVertexIndex[3];
				polygonVertexIndex[0] = fbxMesh->GetPolygonVertex(iPoly, 0);
				polygonVertexIndex[1] = fbxMesh->GetPolygonVertex(iPoly, iFace + 2);
				polygonVertexIndex[2] = fbxMesh->GetPolygonVertex(iPoly, iFace + 1); 

				for (int iIndex = 0; iIndex < 3; ++iIndex)
				{
					int vertexIndex = polygonVertexIndex[iIndex];

					FbxVector4 v = vertice[vertexIndex];
					v = transformData.Geomatric.MultT(v);

					VertexType vertex;
					vertex.Position = { v.mData[0], v.mData[2], v.mData[1], 1 };
					vertexList.push_back(vertex);
				}
			}
		}
	}
}
