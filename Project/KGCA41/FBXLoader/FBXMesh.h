#pragma once

#include "Mesh.h"
#include "Mesh.hpp"
#include <fbxsdk.h>
#include "FBXMaterial.h"
#include "FBXBone.h"

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
		virtual void Initialize_SetFBXMesh(FbxMesh* fbxMesh) = 0;
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

	private:
		MaterialIndex GetMaterialIndex(FbxMesh* fbxMesh, int polygonIndex, int layerIndex, std::map<FBXMaterialKey, FBXMaterialData>& fbxMaterialKeyToFbxMaterialDataMap);
		int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
		HMatrix44 Convert(FbxAMatrix matrix);

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
		void ExtractMeshVertexTextureUV(FbxMesh* fbxMesh, int layerCount, std::map<FBXMaterialKey, FBXMaterialData>& fbxMaterialKeyToFbxMaterialData, std::vector<VertexType>& vertexList);

		template<typename VertexType>
		void ExtractMeshVertexSkinningData(FbxMesh* fbxMesh, std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneData, std::vector<VertexType>& vertexList, MeshToBoneSpaceTransformData& transformData);
	};

	class FBXMesh_PCNT : public Mesh_Vertex_PCNT, public FBXLayerElementReader
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
	};

	class FBXMesh_PCNT_Sub : public FBXMesh_PCNT
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};

	class FBXMesh_PCNT_Animatable : public Mesh_Vertex_PCNT_Animatable, public FBXLayerElementReader
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
	};

	class FBXMesh_PCNT_Animatable_Sub : public FBXMesh_PCNT_Animatable
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};

	class FBXMultiTextureInterface
	{
	public:
		virtual void Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap) = 0;
	};

	class FBXMesh_PCNTs : public Mesh_Vertex_PCNTs, public FBXLayerElementReader, public FBXMultiTextureInterface
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;
		std::map<FBXMaterialKey, FBXMaterialData> _fbxMaterialKeyToFbxMaterialMap;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
		void Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap) override;
	};

	class FBXMesh_PCNTs_Sub : public FBXMesh_PCNTs
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};

	class FBXMesh_PCNTs_Animatable : public Mesh_Vertex_PCNTs_Animatable, public FBXLayerElementReader, public FBXMultiTextureInterface
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;
		std::map<FBXMaterialKey, FBXMaterialData> _fbxMaterialKeyToFbxMaterialMap;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
		void Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap) override;
	};

	class FBXMesh_PCNTs_Animatable_Sub : public FBXMesh_PCNTs_Animatable
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};

	class FBXSkinningMeshInterface
	{
	public:
		virtual void Initialize_SetBoneData(std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneDataMap) = 0;
	};

	class FBXMesh_PCNT_Skinning : public Mesh_Vertex_PCNT_Skinning, public FBXLayerElementReader, public FBXSkinningMeshInterface
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;
		std::map<FBXBoneKey, FBXBoneData> _fbxBoneKeyToFbxBoneDataMap;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
		void Initialize_SetBoneData(std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneDataMap) override;
	};

	class FBXMesh_PCNT_Skinning_Sub : public FBXMesh_PCNT_Skinning
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};

	class FBXMesh_PCNTs_Skinning
		: public Mesh_Vertex_PCNTs_Skinning, public FBXLayerElementReader, public FBXMultiTextureInterface, public FBXSkinningMeshInterface
	{
	protected:
		FbxMesh* _fbxMesh = nullptr;
		std::map<FBXMaterialKey, FBXMaterialData> _fbxMaterialKeyToFbxMaterialMap;
		std::map<FBXBoneKey, FBXBoneData> _fbxBoneKeyToFbxBoneDataMap;

	private:
		void Build() override;

	public:
		void Initialize_SetFBXMesh(FbxMesh* fbxMesh) override;
		void Initialize_SetMaterialData(std::map<FBXMaterialKey, FBXMaterialData> fbxMaterialKeyToFbxMaterialMap) override;
		void Initialize_SetBoneData(std::map<FBXBoneKey, FBXBoneData>& fbxBoneKeyToFbxBoneDataMap) override;
	};

	class FBXMesh_PCNTs_Skinning_Sub : public FBXMesh_PCNTs_Skinning
	{
	private:
		int _layerIndex;

	public:
		void Initialize_SetLayerIndex(int index);

	private:
		void Build() override;
	};
}
