#pragma once

#include <d3d11.h>
#include "Common.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shader.h"
#include <vector>

namespace SSB
{
	typedef DWORD IndexForMeshVertice;
	typedef int MeshIndex;

	class MeshInterface : public Common
	{
	protected:
		virtual void InitialVertexShader() = 0;
		virtual bool CreateVertexLayout() = 0;
		virtual bool CreateVertexBuffer() = 0;
		virtual bool CreateIndexBuffer() = 0;
		virtual void Build() = 0;

	public:
		virtual void Initialize_AddSubMesh(MeshInterface* mesh) = 0;

	public:
		virtual void SetVertexShader(VertexShader* shader) = 0;

	public:
		virtual Vector3 GetMinVertex() = 0;
		virtual Vector3 GetMaxVertex() = 0;
	};

	template<typename VertexType>
	class Mesh : public MeshInterface
	{
	private:
		ID3D11InputLayout* _vertexLayout;
		std::vector<VertexType> _vertexList;
		ID3D11Buffer* _vertexBuffer;
		std::vector<IndexForMeshVertice> _indexList;
		ID3D11Buffer* _indexBuffer;

		Vector3 _minVertex;
		Vector3 _maxVertex;

		std::vector<MeshInterface*> _subMeshes;

		VertexShader* _vs;

	public:
		Mesh();
		virtual ~Mesh();

	private:
		bool CreateVertexLayout() override;
		bool CreateVertexBuffer() override;
		bool CreateIndexBuffer() override;

	protected:
		void SetVertexList(std::vector<VertexType> vertexList);
		void SetIndexList(std::vector<IndexForMeshVertice> indexList);

	protected:
		virtual void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) = 0;

	public:
		void Initialize_AddSubMesh(MeshInterface* mesh) override;

	public:
		void SetVertexShader(VertexShader* shader) override;

	public:
		Vector3 GetMinVertex() override;
		Vector3 GetMaxVertex() override;

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	struct Vertex_PC
	{
		Float4 Position;
		Float4 Color;
	};
	class Mesh_Vertex_PC : public Mesh<Vertex_PC>
	{
	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
		void InitialVertexShader() override;
	};

	struct Vertex_PCNT : public Vertex_PC
	{
		Float4 Normal;
		Float2 TextureUV;
	};
	class Mesh_Vertex_PCNT : public Mesh<Vertex_PCNT>
	{
	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
		void InitialVertexShader() override;
	};

	static const int kAffectedBoneCount = 4;
	struct Vertex_PCNT_Skinning : public Vertex_PCNT
	{
		int AffectedBoneIndex[kAffectedBoneCount];
		float Weight[kAffectedBoneCount];
	};
	struct MeshToBoneSpaceTransformData
	{
		HMatrix44 BoneSpaceTransformBuffer[255];
	};
	class Mesh_Vertex_PCNT_Skinning : public Mesh<Vertex_PCNT_Skinning>
	{
	private:
		MeshToBoneSpaceTransformData _boneSpaceTransformData;
		ID3D11Buffer* _boneSpaceTransformBuffer;

	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
		void InitialVertexShader() override;

	private:
		bool CreateBoneSpaceTransformBuffer();

	public:
		void SetMeshData(MeshToBoneSpaceTransformData data);

	public:
		bool Init() override;
		bool Render() override;
		bool Release() override;
	};

	struct Vertex_PCNTs : public Vertex_PCNT
	{
		unsigned int MaterialIndex;
	};
	class Mesh_Vertex_PCNTs : public Mesh<Vertex_PCNTs>
	{
	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
		void InitialVertexShader() override;
	};

	struct Vertex_PCNTs_Skinning : public Vertex_PCNT
	{
		int AffectedBoneIndex[kAffectedBoneCount];
		float Weight[kAffectedBoneCount];
		unsigned int MaterialIndex;
	};
	class Mesh_Vertex_PCNTs_Skinning : public Mesh<Vertex_PCNTs_Skinning>
	{
	private:
		MeshToBoneSpaceTransformData _boneSpaceTransformData;
		ID3D11Buffer* _boneSpaceTransformBuffer;

	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
		void InitialVertexShader() override;

	private:
		bool CreateBoneSpaceTransformBuffer();

	public:
		void SetMeshData(MeshToBoneSpaceTransformData data);

	public:
		bool Init() override;
		bool Render() override;
		bool Release() override;
	};

	//class Direction : public Mesh_Vertex_PC
	//{
	//public:
	//	Direction();
	//};

	class Triangle : public Mesh_Vertex_PCNT
	{
	public:
		Triangle();

	private:
		void Build() override;
	};

	class Box : public Mesh_Vertex_PCNT
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	private:
		void Build() override;
	};
}

//#include "Mesh.hpp"
