#pragma once

#include "FBXMesh.h"

namespace SSB
{
	template<typename T>
	inline T FBXLayerElementReader::Read(FbxLayerElementTemplate<T>* element, int pointIndex, int polygonIndex)
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

	template<typename VertexType>
	inline IndexForMeshVertice FBXLayerElementReader::VertexRefiner<VertexType>::AddVertex(VertexType vertex)
	{
		int index = 0;
		for (auto addedVertex : _vertexList)
		{
			if (memcmp(&vertex, &addedVertex, sizeof(VertexType)) == 0)
			{
				return index;
			}
			++index;
		}
		_vertexList.push_back(vertex);
		return index;
	}

	template<typename VertexType>
	inline void FBXLayerElementReader::VertexRefiner<VertexType>::Refine(FbxMesh* fbxMesh, std::vector<VertexType> vertexList)
	{
		for (auto vertex : vertexList)
		{
			IndexForMeshVertice index = AddVertex(vertex);
			_indexList.push_back(index);
		}
	}
	template<typename VertexType>
	inline std::vector<VertexType> FBXLayerElementReader::VertexRefiner<VertexType>::GetVertexList()
	{
		return _vertexList;
	}
	template<typename VertexType>
	inline std::vector<IndexForMeshVertice> FBXLayerElementReader::VertexRefiner<VertexType>::GetIndexList()
	{
		return _indexList;
	}

	template<typename VertexType>
	inline void FBXLayerElementReader::ExtractMeshVertexPosition(FbxMesh* fbxMesh, std::vector<VertexType>& vertexList)
	{
		MeshTransformData transformData = CalculateTransformData(fbxMesh->GetNode());

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
					vertex.Position = { (float)v.mData[0], (float)v.mData[2], (float)v.mData[1], 1 };
					vertexList.push_back(vertex);
				}
			}
		}
	}

	template<typename VertexType>
	void FBXLayerElementReader::ExtractMeshVertexColor(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int vertexCount = 0;
		auto colors = fbxMesh->GetLayer(layerCount)->GetVertexColors();
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

					VertexType vertex;
					vertex.Color = { (float)c.mRed, (float)c.mGreen, (float)c.mBlue, (float)c.mAlpha };
					vertexList[vertexCount].Color = vertex.Color;
					++vertexCount;
				}
			}
		}
	}

	template<typename VertexType>
	void FBXLayerElementReader::ExtractMeshVertexNormal(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList)
	{
		MeshTransformData transformData = CalculateTransformData(fbxMesh->GetNode());

		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int vertexCount = 0;
		auto normals = fbxMesh->GetLayer(layerCount)->GetNormals();
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

					VertexType vertex;
					vertex.Normal = { (float)n.mData[0], (float)n.mData[1], (float)n.mData[2], 1 };
					vertexList[vertexCount].Normal = vertex.Normal;
					++vertexCount;
				}
			}
		}
	}

	template<typename VertexType>
	inline void FBXLayerElementReader::ExtractMeshVertexTextureUV(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int vertexCount = 0;
		auto UVs = fbxMesh->GetLayer(layerCount)->GetUVs();
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

					VertexType vertex;
					vertex.TextureUV = { (float)texture.mData[0], 1 - (float)texture.mData[1] };
					vertexList[vertexCount].TextureUV = vertex.TextureUV;
					++vertexCount;
				}
			}
		}
	}

	template<typename VertexType>
	void FBXLayerElementReader::ExtractMeshVertexTextureUV(FbxMesh* fbxMesh, int layerCount, std::map<FBXMaterialKey, FBXMaterialData>& indexToMaterialMap, std::vector<VertexType>& vertexList)
	{
		auto vertice = fbxMesh->GetControlPoints();
		int polygonCount = fbxMesh->GetPolygonCount();

		int vertexCount = 0;
		auto UVs = fbxMesh->GetLayer(layerCount)->GetUVs();
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

					VertexType vertex;
					vertex.TextureUV = { (float)texture.mData[0], 1 - (float)texture.mData[1] };
					vertex.MaterialIndex = GetMaterialIndex(fbxMesh, iPoly, layerCount, indexToMaterialMap);
					vertexList[vertexCount].TextureUV = vertex.TextureUV;
					++vertexCount;
				}
			}
		}
	}
	template<typename VertexType>
	inline void FBXLayerElementReader::ExtractMeshVertexSkinningData(FbxMesh* fbxMesh, std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneData, std::vector<VertexType>& vertexList)
	{
		int deformerCount = fbxMesh->GetDeformerCount(FbxDeformer::eSkin);
		for (int iDeformer = 0; iDeformer < deformerCount; ++iDeformer)
		{
			FbxDeformer* deformer = fbxMesh->GetDeformer(iDeformer, FbxDeformer::eSkin);
			FbxSkin* skin = (FbxSkin*)deformer;
			int clusterCount = skin->GetClusterCount();
			for (int iCluster = 0; iCluster < clusterCount; ++iCluster)
			{
				FbxCluster* cluster = skin->GetCluster(iCluster);
				int boneIndex = fbxBoneKeyToFbxBoneData.find(cluster->GetLink())->second.FBXBoneIndex;

				{
					FbxAMatrix linkMatrix;
					cluster->GetTransformLinkMatrix(linkMatrix);

					FbxAMatrix adjustMatrix;
					cluster->GetTransformMatrix(adjustMatrix);

					FbxAMatrix fbxBoneSpaceMatrix = linkMatrix.Inverse() * adjustMatrix;
					HMatrix44 toBoneSpaceMatrix = Convert(fbxBoneSpaceMatrix);
					object->SetBoneSpaceTransformMatrix(boneIndex, toBoneSpaceMatrix);
				}

				int controlPointCount = cluster->GetControlPointIndicesCount();
				int* controlPointIndice = cluster->GetControlPointIndices();
				double* controlPointWeights = cluster->GetControlPointWeights();
				for (int iControlPoint = 0; iControlPoint < controlPointCount; ++iControlPoint)
				{
					int vertexIndex = controlPointIndice[iControlPoint];
					float weight = controlPointWeights[iControlPoint];

					VertexType& data = vertexList[vertexIndex];
					for (int i = 0; i < 4; ++i)
					{
						if (data.Weight[i] < weight)
						{
							for (int j = 3; i < j; --j)
							{
								data.AffectedBoneIndex[j] = data.AffectedBoneIndex[j - 1];
								data.Weight[j] = data.Weight[j - 1];
							}

							data.AffectedBoneIndex[i] = boneIndex;
							data.Weight[i] = weight;

							break;
						}
					}
				}
			}
		}
	}
}
