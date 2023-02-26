#include "Mesh.h"
#include "Mesh.hpp"

namespace SSB
{
	void Mesh_Vertex_PC::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 2;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNT::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 4;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNT_Skinning::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 6;
	
		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 72, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	bool Mesh_Vertex_PCNT_Skinning::CreateBoneSpaceTransformBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshToBoneSpaceTransformData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_boneSpaceTransformData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_boneSpaceTransformBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}

	void Mesh_Vertex_PCNT_Skinning::SetMeshData(MeshToBoneSpaceTransformData data)
	{
		_boneSpaceTransformData = data;
	}

	bool Mesh_Vertex_PCNT_Skinning::Init()
	{
		Mesh<Vertex_PCNT_Skinning>::Init();

		CreateBoneSpaceTransformBuffer();

		return true;
	}

	bool Mesh_Vertex_PCNT_Skinning::Render()
	{
		Mesh<Vertex_PCNT_Skinning>::Render();

		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(3, 1, &_boneSpaceTransformBuffer);

		return true;
	}

	bool Mesh_Vertex_PCNT_Skinning::Release()
	{
		Mesh<Vertex_PCNT_Skinning>::Release();

		if (_boneSpaceTransformBuffer != nullptr)
		{
			_boneSpaceTransformBuffer->Release();
			_boneSpaceTransformBuffer = nullptr;
		}

		return true;
	}

	void Mesh_Vertex_PCNTs::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 5;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "MaterialIndex", 0, DXGI_FORMAT_R32_UINT, 0, 76, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNTs_Skinning::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 7;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 72, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[6] = { "MaterialIndex", 0, DXGI_FORMAT_R32_UINT, 0, 76, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	bool Mesh_Vertex_PCNTs_Skinning::CreateBoneSpaceTransformBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshToBoneSpaceTransformData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_boneSpaceTransformData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_boneSpaceTransformBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}

	void Mesh_Vertex_PCNTs_Skinning::SetMeshData(MeshToBoneSpaceTransformData data)
	{
		_boneSpaceTransformData = data;
	}

	bool Mesh_Vertex_PCNTs_Skinning::Init()
	{
		Mesh<Vertex_PCNTs_Skinning>::Init();

		CreateBoneSpaceTransformBuffer();

		return true;
	}

	bool Mesh_Vertex_PCNTs_Skinning::Render()
	{
		Mesh<Vertex_PCNTs_Skinning>::Render();

		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(3, 1, &_boneSpaceTransformBuffer);

		return true;
	}

	bool Mesh_Vertex_PCNTs_Skinning::Release()
	{
		Mesh<Vertex_PCNTs_Skinning>::Release();

		if (_boneSpaceTransformBuffer != nullptr)
		{
			_boneSpaceTransformBuffer->Release();
			_boneSpaceTransformBuffer = nullptr;
		}

		return true;
	}

	Box::Box(float width, float height, float depth)
		: _width(width), _height(height), _depth(depth)
	{
		std::vector<Vertex_PCNT> vertexList;
		vertexList.resize(24);
		// ¾Õ¸é
		vertexList[0] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[1] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[2] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[3] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0.0f, 0.5f} };
		// µÞ¸é
		vertexList[4] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[5] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[6] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[7] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿À¸¥ÂÊ
		vertexList[8] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[9] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[10] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[11] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿ÞÂÊ
		vertexList[12] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[13] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[14] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[15] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float4{-1.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// À­¸é
		vertexList[16] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[17] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[18] = Vertex_PCNT{ Float4{0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[19] = Vertex_PCNT{ Float4{-0.5f * _width, 0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¾Æ·§¸é
		vertexList[20] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		vertexList[21] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, -0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		vertexList[22] = Vertex_PCNT{ Float4{0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		vertexList[23] = Vertex_PCNT{ Float4{-0.5f * _width, -0.5f * _height, 0.5f * _depth, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, -1.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		SetVertexList(&vertexList.at(0), 24);

		std::vector<DWORD> indexList;
		indexList.resize(36);
		int iIndex = 0;
		indexList[iIndex++] = 0; 	indexList[iIndex++] = 1; 	indexList[iIndex++] = 2; 	indexList[iIndex++] = 0;	indexList[iIndex++] = 2; 	indexList[iIndex++] = 3;
		indexList[iIndex++] = 4; 	indexList[iIndex++] = 5; 	indexList[iIndex++] = 6; 	indexList[iIndex++] = 4;	indexList[iIndex++] = 6; 	indexList[iIndex++] = 7;
		indexList[iIndex++] = 8; 	indexList[iIndex++] = 9; 	indexList[iIndex++] = 10; indexList[iIndex++] = 8;	indexList[iIndex++] = 10; indexList[iIndex++] = 11;
		indexList[iIndex++] = 12; indexList[iIndex++] = 13; indexList[iIndex++] = 14; indexList[iIndex++] = 12;	indexList[iIndex++] = 14; indexList[iIndex++] = 15;
		indexList[iIndex++] = 16; indexList[iIndex++] = 17; indexList[iIndex++] = 18; indexList[iIndex++] = 16;	indexList[iIndex++] = 18; indexList[iIndex++] = 19;
		indexList[iIndex++] = 20; indexList[iIndex++] = 21; indexList[iIndex++] = 22; indexList[iIndex++] = 20;	indexList[iIndex++] = 22; indexList[iIndex++] = 23;

		SetIndexList(indexList);
	}
	Triangle::Triangle()
	{
		std::vector<Vertex_PCNT> vertexList;
		vertexList.resize(3);
		vertexList[0] = Vertex_PCNT{ Float4{+0.0f, +0.5f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0, 0} };
		vertexList[1] = Vertex_PCNT{ Float4{+0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0, 0} };
		vertexList[2] = Vertex_PCNT{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0, 0} };

		SetVertexList(&vertexList.at(0), 3);

		std::vector<DWORD> indexList;
		indexList.resize(3);
		int iIndex = 0;
		indexList[iIndex++] = 0;
		indexList[iIndex++] = 1;
		indexList[iIndex++] = 2;

		SetIndexList(indexList);
	}
}