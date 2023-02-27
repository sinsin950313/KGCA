#pragma once

#include "Mesh.h"
#include "Mesh.hpp"
#include <fbxsdk.h>

namespace SSB
{
	class FBXMeshInterface
	{
	protected:
		struct MeshTransformData
		{
			FbxAMatrix Geomatric;
			FbxAMatrix NormalLocal;
		};

	protected:
		MeshTransformData CalculateTransformData(FbxNode* node);

	public:
		virtual void InitialFBXMesh(FbxMesh* fbxMesh) = 0;
	};

	class FBXLayerElementReader : public FBXMeshInterface
	{
	protected:
		template<typename VertexType>
		class VertexRefiner
		{
			std::vector<VertexType> _vertexList;
			std::vector<IndexForMeshVertice> _indexList;

		private:
			IndexForMeshVertice AddVertex(VertexType vertex);

		public:
			void Refine(FbxMesh* fbxMesh, std::vector<VertexType> vertexList);

		public:
			std::vector<VertexType> GetVertexList();
			std::vector<IndexForMeshVertice> GetIndexList();
		};

	protected:
		template<typename T>
		T Read(FbxLayerElementTemplate<T>* element, int pointIndex, int polygonIndex);
		FbxVector2 Read(FbxLayerElementUV* element, int pointIndex, int polygonIndex);

		template<typename VertexType>
		void ExtractMeshVertexPosition(FbxMesh* fbxMesh, std::vector<VertexType>& vertexList);

		template<typename VertexType>
		void ExtractMeshVertexColor(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList);

		template<typename VertexType>
		void ExtractMeshVertexNormal(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList);

		template<typename VertexType>
		void ExtractMeshVertexTextureUV(FbxMesh* fbxMesh, int layerCount, std::vector<VertexType>& vertexList);

		template<typename VertexType>
		void ExtractMeshVertexSkinningData(FbxMesh* fbxMesh, std::vector<VertexType>& vertexList);
	};

	class FBXMesh_PCNT : public Mesh_Vertex_PCNT, public FBXLayerElementReader
	{
	private:
		FbxMesh* _fbxMesh;

	private:
		void Build() override;

	public:
		void InitialFBXMesh(FbxMesh* fbxMesh) override;
	};

	class FBXMesh_PCNTs : public Mesh_Vertex_PCNTs, public FBXLayerElementReader
	{
	private:
		FbxMesh* _fbxMesh;

	private:
		void Build() override;

	public:
		void InitialFBXMesh(FbxMesh* fbxMesh) override;
	};

	class FBXMesh_PCNT_Skinning : public Mesh_Vertex_PCNT_Skinning, public FBXLayerElementReader
	{
	private:
		FbxMesh* _fbxMesh;

	private:
		void Build() override;

	public:
		void InitialFBXMesh(FbxMesh* fbxMesh) override;
	};

	class FBXMesh_PCNTs_Skinning : public Mesh_Vertex_PCNTs_Skinning, public FBXLayerElementReader
	{
	private:
		FbxMesh* _fbxMesh;

	private:
		void Build() override;

	public:
		void InitialFBXMesh(FbxMesh* fbxMesh) override;
	};
}
