#pragma once

#include "Vector.h"
#include "Matrix.h"
#include <d3d11.h>
#include "Texture.h"
#include "Shader.h"

namespace SSB
{
	typedef DWORD IndexForMeshVertice;
	typedef unsigned int IndexForMeshTexture;

	class MeshInterface : public Common
	{
	public:
		virtual void SetVertexShader(VertexShader* shader) = 0;
		virtual void SetPixelShader(PixelShader* shader) = 0;
		virtual void SetSpriteData(std::map<IndexForMeshTexture, Sprite*> spriteData) = 0;

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

		VertexShader* _vs;
		PixelShader* _ps;

		int _resourceCount;
		ID3D11SamplerState** _samplerStateList;
		ID3D11ShaderResourceView** _shaderResourceViewList;

	public:
		Mesh();
		virtual ~Mesh();

	private:
		bool CreateVertexLayout();
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();

	protected:
		virtual void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) = 0;

	public:
		void SetVertexList(std::vector<VertexType> vertexList);
		void SetIndexList(std::vector<IndexForMeshVertice> indexList);

	public:
		void SetVertexShader(VertexShader* shader) override;
		void SetPixelShader(PixelShader* shader) override;
		void SetSpriteData(std::map<IndexForMeshTexture, Sprite*> spriteData) override;

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
		unsigned int TextureIndex;
	};
	class Mesh_Vertex_PCNTs : Mesh<Vertex_PCNTs>
	{
	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;
	};

	struct Vertex_PCNTs_Skinning : public Vertex_PCNT
	{
		int AffectedBoneIndex[kAffectedBoneCount];
		float Weight[kAffectedBoneCount];
		unsigned int TextureIndex;
	};
	class Mesh_Vertex_PCNTs_Skinning : public Mesh<Vertex_PCNTs_Skinning>
	{
	private:
		MeshToBoneSpaceTransformData _boneSpaceTransformData;
		ID3D11Buffer* _boneSpaceTransformBuffer;

	private:
		void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count) override;

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
	};

	class Box : public Mesh_Vertex_PCNT
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
	};
}

//#include "Mesh.hpp"
