#include "Mesh.h"
#include "Mesh.hpp"
#include "ShaderManager.h"

namespace SSB
{
	std::string Mesh_Vertex_PC::GetVertexType()
	{
		return Vertex_PC_Keyword;
	}
	Vertex_PC Mesh_Vertex_PC::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PC vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}
	void Mesh_Vertex_PC::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 2;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PC::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PC.hlsl", "VS", "vs_5_0"));
	}

	std::string Mesh_Vertex_PCNT::GetVertexType()
	{
		return Vertex_PCNT_Keyword;
	}
	Vertex_PCNT Mesh_Vertex_PCNT::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNT vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}
	void Mesh_Vertex_PCNT::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 4;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNT::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNT.hlsl", "VS", "vs_5_0"));
	}

	bool Mesh_Vertex_PCNT_Animatable::CreateMeshBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(MeshData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_meshData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_meshBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}

	std::string Mesh_Vertex_PCNT_Animatable::GetVertexType()
	{
		return Vertex_PCNT_Animatable_Keyword;
	}
	void Mesh_Vertex_PCNT_Animatable::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 4;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNT_Animatable::Initialize_SetMeshData(MeshData meshData)
	{
		_meshData = meshData;
	}

	bool Mesh_Vertex_PCNT_Animatable::Init()
	{
		Mesh<Vertex_PCNT>::Init();
		CreateMeshBuffer();

		return true;
	}

	bool Mesh_Vertex_PCNT_Animatable::Render()
	{
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(4, 1, &_meshBuffer);
		Mesh<Vertex_PCNT>::Render();
		return true;
	}

	bool Mesh_Vertex_PCNT_Animatable::Release()
	{
		if (_meshBuffer != nullptr)
		{
			_meshBuffer->Release();
			_meshBuffer = nullptr;
		}

		Mesh<Vertex_PCNT>::Release();
		return true;
	}
	std::string Mesh_Vertex_PCNT_Animatable::Serialize(int tabCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "[\n";

		ret += GetTabbedString(tabCount + 1);
		ret += _meshDataStr;
		ret += Serializeable::Serialize(tabCount + 2, _meshData);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNT>::Serialize(tabCount + 1);

		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNT_Animatable::Deserialize(std::string serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElement(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			auto atomicData = GetUnitAtomic(elem, 0);
			std::string atomic = atomicData.str;
			Serializeable::Deserialize(atomic, _meshData);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNT>::Deserialize(serialedString);
	}

	Vertex_PCNT Mesh_Vertex_PCNT_Animatable::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNT vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}

	void Mesh_Vertex_PCNT_Animatable::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNT_Animatable.hlsl", "VS", "vs_5_0"));
	}

	void Mesh_Vertex_PCNT_Skinning::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 6;
	
		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 72, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNT_Skinning::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNT_Skinning.hlsl", "VS", "vs_5_0"));
	}

	std::string Mesh_Vertex_PCNT_Skinning::GetVertexType()
	{
		return Vertex_PCNT_Skinning_Keyword;
	}

	bool Mesh_Vertex_PCNT_Skinning::CreateBoneSpaceTransformBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshToBoneSpaceTransformData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

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
		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = data.BoneSpaceTransformBuffer[i].Transpose();
		}
	}

	bool Mesh_Vertex_PCNT_Skinning::Init()
	{
		Mesh<Vertex_PCNT_Skinning>::Init();

		CreateBoneSpaceTransformBuffer();

		return true;
	}

	bool Mesh_Vertex_PCNT_Skinning::Render()
	{
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(4, 1, &_boneSpaceTransformBuffer);

		Mesh<Vertex_PCNT_Skinning>::Render();

		return true;
	}

	std::string Mesh_Vertex_PCNT_Skinning::Serialize(int tabCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "[\n";

		ret += GetTabbedString(tabCount + 1);
		ret += _meshToBoneSpaceTransformDataStr;
		ret += Serializeable::Serialize(tabCount + 2, _boneSpaceTransformData);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNT_Skinning>::Serialize(tabCount + 1);

		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	void Mesh_Vertex_PCNT_Skinning::Deserialize(std::string serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElement(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			Serializeable::Deserialize(elem, _boneSpaceTransformData);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNT_Skinning>::Deserialize(serialedString);
	}
	Vertex_PCNT_Skinning Mesh_Vertex_PCNT_Skinning::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNT_Skinning vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}
	bool Mesh_Vertex_PCNT_Skinning::Release()
	{
		Mesh<Vertex_PCNT_Skinning>::Release();

		if (_boneSpaceTransformBuffer != nullptr)
		{
			_boneSpaceTransformBuffer->Release();
			_boneSpaceTransformBuffer = nullptr;
		}

		Mesh<Vertex_PCNT_Skinning>::Release();

		return true;
	}

	void Mesh_Vertex_PCNTs::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 5;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "MaterialIndex", 0, DXGI_FORMAT_R32_UINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNTs::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNTs.hlsl", "VS", "vs_5_0"));
	}

	std::string Mesh_Vertex_PCNTs::GetVertexType()
	{
		return Vertex_PCNTs_Animatable_Keyword;
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNTs vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}

	bool Mesh_Vertex_PCNTs_Animatable::CreateMeshBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_meshData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_meshBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}

	void Mesh_Vertex_PCNTs_Animatable::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 5;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "MaterialIndex", 0, DXGI_FORMAT_R32_UINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNTs_Animatable::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNTs_Animatable.hlsl", "VS", "vs_5_0"));
	}

	std::string Mesh_Vertex_PCNTs_Animatable::GetVertexType()
	{
		return Vertex_PCNTs_Animatable_Keyword;
	}

	void Mesh_Vertex_PCNTs_Animatable::Initialize_SetMeshData(MeshData meshData)
	{
		_meshData = meshData;
	}

	bool Mesh_Vertex_PCNTs_Animatable::Init()
	{
		Mesh<Vertex_PCNTs>::Init();
		CreateMeshBuffer();
		return true;
	}

	bool Mesh_Vertex_PCNTs_Animatable::Render()
	{
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(4, 1, &_meshBuffer);

		Mesh<Vertex_PCNTs>::Render();
		return true;
	}

	bool Mesh_Vertex_PCNTs_Animatable::Release()
	{
		if (_meshBuffer != nullptr)
		{
			_meshBuffer->Release();
			_meshBuffer = nullptr;
		}

		Mesh<Vertex_PCNTs>::Release();
		return true;
	}
	std::string Mesh_Vertex_PCNTs_Animatable::Serialize(int tabCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "[\n";

		ret += GetTabbedString(tabCount + 1);
		ret += _meshDataStr;
		ret += Serializeable::Serialize(tabCount + 2, _meshData);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNTs>::Serialize(tabCount + 1);

		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNTs_Animatable::Deserialize(std::string serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElement(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			auto atomicData = GetUnitAtomic(elem, 0);
			std::string atomic = atomicData.str;
			Serializeable::Deserialize(atomic, _meshData);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNTs>::Deserialize(serialedString);
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs_Animatable::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNTs vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}

	std::string Mesh_Vertex_PCNTs_Skinning::GetVertexType()
	{
		return Vertex_PCNTs_Skinning_Keyword;
	}
	void Mesh_Vertex_PCNTs_Skinning::SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count)
	{
		count = 7;

		*desc = new D3D11_INPUT_ELEMENT_DESC[count];
		(*desc)[0] = { "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[1] = { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[2] = { "Normal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[3] = { "Diffuse", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[4] = { "AffectingBoneIndex", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[5] = { "Weight", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 72, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		(*desc)[6] = { "MaterialIndex", 0, DXGI_FORMAT_R32_UINT, 0, 88, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	}

	void Mesh_Vertex_PCNTs_Skinning::InitialVertexShader()
	{
		SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default3DVertexShader_PCNTs_Skinning.hlsl", "VS", "vs_5_0"));
	}

	bool Mesh_Vertex_PCNTs_Skinning::CreateBoneSpaceTransformBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(MeshToBoneSpaceTransformData);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

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
		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = data.BoneSpaceTransformBuffer[i].Transpose();
		}
	}

	bool Mesh_Vertex_PCNTs_Skinning::Init()
	{
		Mesh<Vertex_PCNTs_Skinning>::Init();

		CreateBoneSpaceTransformBuffer();

		return true;
	}

	bool Mesh_Vertex_PCNTs_Skinning::Render()
	{
		g_dxWindow->GetDeviceContext()->VSSetConstantBuffers(4, 1, &_boneSpaceTransformBuffer);

		Mesh<Vertex_PCNTs_Skinning>::Render();

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

		Mesh<Vertex_PCNTs_Skinning>::Release();

		return true;
	}

	std::string Mesh_Vertex_PCNTs_Skinning::Serialize(int tabCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "[\n";

		ret += GetTabbedString(tabCount + 1);
		ret += _meshToBoneSpaceTransformDataStr;
		ret += Serializeable::Serialize(tabCount + 2, _boneSpaceTransformData);
		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNTs_Skinning>::Serialize(tabCount + 1);

		ret += GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNTs_Skinning::Deserialize(std::string serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElement(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			Serializeable::Deserialize(elem, _boneSpaceTransformData);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNTs_Skinning>::Deserialize(serialedString);
	}

	Vertex_PCNTs_Skinning Mesh_Vertex_PCNTs_Skinning::GetDeserializedVertex(std::string str)
	{
		str = GetUnitElement(str, 0).str;
		Vertex_PCNTs_Skinning vertex;
		Serializeable::Deserialize(str, vertex);
		return vertex;
	}

	Box::Box(float width, float height, float depth)
		: _width(width), _height(height), _depth(depth)
	{
	}
	void Box::Build()
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

		SetVertexList(vertexList);

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
	}
	void Triangle::Build()
	{
		std::vector<Vertex_PCNT> vertexList;
		vertexList.resize(3);
		vertexList[0] = Vertex_PCNT{ Float4{+0.0f, +0.5f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0, 0} };
		vertexList[1] = Vertex_PCNT{ Float4{+0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float2{0, 0} };
		vertexList[2] = Vertex_PCNT{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0.0f, 0.0f, -1.0f, 1.0f}, Float4{0, 0} };

		SetVertexList(vertexList);

		std::vector<DWORD> indexList;
		indexList.resize(3);
		int iIndex = 0;
		indexList[iIndex++] = 0;
		indexList[iIndex++] = 1;
		indexList[iIndex++] = 2;

		SetIndexList(indexList);
	}
}