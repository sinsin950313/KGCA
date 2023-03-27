#include "Mesh.h"
#include "Mesh.hpp"
#include "ShaderManager.h"

namespace SSB
{
	std::string Mesh_Vertex_PC::GetVertexType()
	{
		return Vertex_PC_Keyword;
	}
	Vertex_PC Mesh_Vertex_PC::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PC vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}
	std::string Mesh_Vertex_PC::GetSerializedBinaryVertexData(Vertex_PC vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		return ret;
	}
	Vertex_PC Mesh_Vertex_PC::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PC ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		return ret;
	}
	Mesh<Vertex_PC>* Mesh_Vertex_PC::GetMesh()
	{
		return new Mesh_Vertex_PC;
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

	MeshInterface* Mesh_Vertex_PC::ClonedObject()
	{
		return new Mesh_Vertex_PC;
	}

	std::string Mesh_Vertex_PCNT::GetVertexType()
	{
		return Vertex_PCNT_Keyword;
	}
	Vertex_PCNT Mesh_Vertex_PCNT::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNT vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}
	std::string Mesh_Vertex_PCNT::GetSerializedBinaryVertexData(Vertex_PCNT vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		return ret;
	}
	Vertex_PCNT Mesh_Vertex_PCNT::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNT ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		return ret;
	}
	Mesh<Vertex_PCNT>* Mesh_Vertex_PCNT::GetMesh()
	{
		return new Mesh_Vertex_PCNT;
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

	MeshInterface* Mesh_Vertex_PCNT::ClonedObject()
	{
		return new Mesh_Vertex_PCNT;
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
	Vertex_PCNT Mesh_Vertex_PCNT_Animatable::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNT vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}
	std::string Mesh_Vertex_PCNT_Animatable::GetSerializedBinaryVertexData(Vertex_PCNT vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		return ret;
	}
	Vertex_PCNT Mesh_Vertex_PCNT_Animatable::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNT ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		return ret;
	}
	Mesh<Vertex_PCNT>* Mesh_Vertex_PCNT_Animatable::GetMesh()
	{
		return new Mesh_Vertex_PCNT_Animatable;
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
	std::string Mesh_Vertex_PCNT_Animatable::SerializeText(int tabCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshDataStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _meshData);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNT>::SerializeText(tabCount + 1);

		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNT_Animatable::DeserializeText(std::string& serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			auto atomicData = GetUnitElementText(elem, 0);
			std::string atomic = atomicData.str;
			SerializeableText::DeserializeText(atomic, _meshData);
		}

		serialedString = GetUnitObjectText(serialedString, offset).str;
		Mesh<Vertex_PCNT>::DeserializeText(serialedString);
	}

	std::string Mesh_Vertex_PCNT_Animatable::SerializeBinary()
	{
		std::string ret = Mesh<Vertex_PCNT>::SerializeBinary();

		{
			int tmpSize = _meshData.MeshIndex;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		return ret;
	}

	void Mesh_Vertex_PCNT_Animatable::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		Mesh<Vertex_PCNT>::DeserializeBinary(buffer, size, offset);

		memcpy(&_meshData.MeshIndex, buffer + offset, sizeof(int));
		offset += sizeof(int);
	}


	MeshInterface* Mesh_Vertex_PCNT_Animatable::Clone()
	{
		Mesh_Vertex_PCNT_Animatable* newMesh = static_cast<Mesh_Vertex_PCNT_Animatable*>(Mesh<Vertex_PCNT>::Clone());
		newMesh->_meshData = _meshData;
		return newMesh;
	}


	MeshInterface* Mesh_Vertex_PCNT_Animatable::ClonedObject()
	{
		return new Mesh_Vertex_PCNT_Animatable;
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
		//_boneSpaceTransformData.MeshIndex = data.MeshIndex;
		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = data.BoneSpaceTransformBuffer[i].Transpose();
		}
	}

	void Mesh_Vertex_PCNT_Skinning::SetMeshAnimationWeight(float weight)
	{
		_boneSpaceTransformData.MeshWeight = weight;
	}

	void Mesh_Vertex_PCNT_Skinning::Initialize_SetMaxBoneCount(int maxBoneCount)
	{
		_maxBoneCount = maxBoneCount;
	}

	void Mesh_Vertex_PCNT_Skinning::Initialize_SetMeshData(int index)
	{
		_boneSpaceTransformData.MeshIndex = index;
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

	std::string Mesh_Vertex_PCNT_Skinning::SerializeText(int tabCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshIndexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData.MeshIndex);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshWeightStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData.MeshWeight);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _maxBoneCountStr;
		ret += "{\"";
		ret += std::to_string(_maxBoneCount);
		ret += "\"}\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshToBoneSpaceTransformDataStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData, _maxBoneCount);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNT_Skinning>::SerializeText(tabCount + 1);

		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}
	void Mesh_Vertex_PCNT_Skinning::DeserializeText(std::string& serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData.MeshIndex);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData.MeshWeight);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _maxBoneCount);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData, _maxBoneCount);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNT_Skinning>::DeserializeText(serialedString);
	}
	std::string Mesh_Vertex_PCNT_Skinning::SerializeBinary()
	{
		std::string ret = Mesh<Vertex_PCNT_Skinning>::SerializeBinary();

		{
			int tmpSize = _maxBoneCount;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		{
			for (int i = 0; i < _maxBoneCount; ++i)
			{
				Float44 tmpBuffer = _boneSpaceTransformData.BoneSpaceTransformBuffer[i];
				std::string tmpStr((char*)&tmpBuffer, sizeof(Float44));
				ret += tmpStr;
			}

			{
				int tmpSize = _boneSpaceTransformData.MeshIndex;
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			{
				float tmpSize = _boneSpaceTransformData.MeshWeight;
				char* tmpBuffer = new char[sizeof(float)];
				memcpy(tmpBuffer, &tmpSize, sizeof(float));
				std::string tmpStr(tmpBuffer, sizeof(float));
				ret += tmpStr;
				delete tmpBuffer;
			}
		}

		return ret;
	}
	void Mesh_Vertex_PCNT_Skinning::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		Mesh<Vertex_PCNT_Skinning>::DeserializeBinary(buffer, size, offset);

		{
			memcpy(&_maxBoneCount, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		for (int i = 0; i < _maxBoneCount; ++i)
		{
			Float44 tmpBuffer;
			memcpy(&tmpBuffer, buffer + offset, sizeof(Float44));
			offset += sizeof(Float44);
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = {
				tmpBuffer.e11, tmpBuffer.e12, tmpBuffer.e13, tmpBuffer.e14,
				tmpBuffer.e21, tmpBuffer.e22, tmpBuffer.e23, tmpBuffer.e24,
				tmpBuffer.e31, tmpBuffer.e32, tmpBuffer.e33, tmpBuffer.e34,
				tmpBuffer.e41, tmpBuffer.e42, tmpBuffer.e43, tmpBuffer.e44,
			};
		}

		memcpy(&_boneSpaceTransformData.MeshIndex, buffer + offset, sizeof(int));
		offset += sizeof(int);

		memcpy(&_boneSpaceTransformData.MeshWeight, buffer + offset, sizeof(float));
		offset += sizeof(float);
	}
	MeshInterface* Mesh_Vertex_PCNT_Skinning::Clone()
	{
		Mesh_Vertex_PCNT_Skinning* newMesh = static_cast<Mesh_Vertex_PCNT_Skinning*>(Mesh<Vertex_PCNT_Skinning>::Clone());
		newMesh->_maxBoneCount = _maxBoneCount;
		memcpy(&newMesh->_boneSpaceTransformData, &_boneSpaceTransformData, sizeof(MeshToBoneSpaceTransformData));
		return newMesh;
	}
	Vertex_PCNT_Skinning Mesh_Vertex_PCNT_Skinning::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNT_Skinning vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}
	std::string Mesh_Vertex_PCNT_Skinning::GetSerializedBinaryVertexData(Vertex_PCNT_Skinning vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		{
			for (int i = 0; i < 4; ++i)
			{
				{
					int tmpSize = vertex.AffectedBoneIndex[i];
					char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
				{
					int tmpSize = vertex.Weight[i];
					char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
			}
		}

		return ret;
	}
	Vertex_PCNT_Skinning Mesh_Vertex_PCNT_Skinning::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNT_Skinning ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		{
			for (int i = 0; i < 4; ++i)
			{
				memcpy(&ret.AffectedBoneIndex[i], buffer + offset, sizeof(int));
				offset += sizeof(int);

				memcpy(&ret.Weight[i], buffer + offset, sizeof(float));
				offset += sizeof(float);
			}
		}

		return ret;
	}
	Mesh<Vertex_PCNT_Skinning>* Mesh_Vertex_PCNT_Skinning::GetMesh()
	{
		return new Mesh_Vertex_PCNT_Skinning;
	}
	MeshInterface* Mesh_Vertex_PCNT_Skinning::ClonedObject()
	{
		return new Mesh_Vertex_PCNT_Skinning;
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
		return Vertex_PCNTs_Keyword;
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNTs vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}

	std::string Mesh_Vertex_PCNTs::GetSerializedBinaryVertexData(Vertex_PCNTs vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		{
			int tmpSize = vertex.MaterialIndex;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		return ret;
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNTs ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		{
			memcpy(&ret.MaterialIndex, buffer + offset, sizeof(unsigned int));
			offset += sizeof(unsigned int);
		}

		return ret;
	}

	Mesh<Vertex_PCNTs>* Mesh_Vertex_PCNTs::GetMesh()
	{
		return new Mesh_Vertex_PCNTs;
	}

	MeshInterface* Mesh_Vertex_PCNTs::ClonedObject()
	{
		return new Mesh_Vertex_PCNTs;
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
	std::string Mesh_Vertex_PCNTs_Animatable::SerializeText(int tabCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshDataStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _meshData);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNTs>::SerializeText(tabCount + 1);

		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNTs_Animatable::DeserializeText(std::string& serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			auto atomicData = GetUnitElementText(elem, 0);
			std::string atomic = atomicData.str;
			SerializeableText::DeserializeText(atomic, _meshData);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNTs>::DeserializeText(serialedString);
	}

	std::string Mesh_Vertex_PCNTs_Animatable::SerializeBinary()
	{
		std::string ret = Mesh<Vertex_PCNTs>::SerializeBinary();

		{
			int tmpSize = _meshData.MeshIndex;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		return ret;
	}

	void Mesh_Vertex_PCNTs_Animatable::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		Mesh<Vertex_PCNTs>::DeserializeBinary(buffer, size, offset);

		memcpy(&_meshData.MeshIndex, buffer + offset, sizeof(int));
		offset += sizeof(int);
	}

	MeshInterface* Mesh_Vertex_PCNTs_Animatable::Clone()
	{
		Mesh_Vertex_PCNTs_Animatable* newMesh = static_cast<Mesh_Vertex_PCNTs_Animatable*>(Mesh<Vertex_PCNTs>::Clone());
		newMesh->_meshData = _meshData;
		return newMesh;
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs_Animatable::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNTs vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}

	std::string Mesh_Vertex_PCNTs_Animatable::GetSerializedBinaryVertexData(Vertex_PCNTs vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		{
			int tmpSize = vertex.MaterialIndex;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		return ret;
	}

	Vertex_PCNTs Mesh_Vertex_PCNTs_Animatable::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNTs ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		{
			memcpy(&ret.MaterialIndex, buffer + offset, sizeof(unsigned int));
			offset += sizeof(unsigned int);
		}

		return ret;
	}

	Mesh<Vertex_PCNTs>* Mesh_Vertex_PCNTs_Animatable::GetMesh()
	{
		return new Mesh_Vertex_PCNTs_Animatable;
	}

	MeshInterface* Mesh_Vertex_PCNTs_Animatable::ClonedObject()
	{
		return new Mesh_Vertex_PCNTs_Animatable;
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
		//_boneSpaceTransformData.MeshIndex = data.MeshIndex;
		for (int i = 0; i < kMaximumBoneCount; ++i)
		{
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = data.BoneSpaceTransformBuffer[i].Transpose();
		}
	}

	void Mesh_Vertex_PCNTs_Skinning::Initialize_SetMaxBoneCount(int maxBoneCount)
	{
		_maxBoneCount = maxBoneCount;
	}

	void Mesh_Vertex_PCNTs_Skinning::Initialize_SetMeshData(int index)
	{
		_boneSpaceTransformData.MeshIndex = index;
	}

	void Mesh_Vertex_PCNTs_Skinning::SetMeshAnimationWeight(float weight)
	{
		_boneSpaceTransformData.MeshWeight = weight;
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

	std::string Mesh_Vertex_PCNTs_Skinning::SerializeText(int tabCount)
	{
		std::string ret;

		ret += GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshIndexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData.MeshIndex);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshWeightStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData.MeshWeight);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _maxBoneCountStr;
		ret += "{\"";
		ret += std::to_string(_maxBoneCount);
		ret += "\"}\n";

		ret += GetTabbedStringText(tabCount + 1);
		ret += _meshToBoneSpaceTransformDataStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _boneSpaceTransformData, _maxBoneCount);
		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += Mesh<Vertex_PCNTs_Skinning>::SerializeText(tabCount + 1);

		ret += GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}

	void Mesh_Vertex_PCNTs_Skinning::DeserializeText(std::string& serialedString)
	{
		int offset = 0;
		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData.MeshIndex);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData.MeshWeight);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _maxBoneCount);
		}

		{
			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;
			SerializeableText::DeserializeText(elem, _boneSpaceTransformData, _maxBoneCount);
		}

		serialedString = std::string(serialedString.begin() + offset, serialedString.end());
		Mesh<Vertex_PCNTs_Skinning>::DeserializeText(serialedString);
	}

	std::string Mesh_Vertex_PCNTs_Skinning::SerializeBinary()
	{
		std::string ret = Mesh<Vertex_PCNTs_Skinning>::SerializeBinary();

		{
			int tmpSize = _maxBoneCount;
			char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
			std::string tmpStr(tmpBuffer, sizeof(int));
			ret += tmpStr;
			delete tmpBuffer;
		}

		{
			for (int i = 0; i < _maxBoneCount; ++i)
			{
				Float44 tmpBuffer = _boneSpaceTransformData.BoneSpaceTransformBuffer[i];
				std::string tmpStr((char*)&tmpBuffer, sizeof(Float44));
				ret += tmpStr;
			}

			{
				int tmpSize = _boneSpaceTransformData.MeshIndex;
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			{
				float tmpSize = _boneSpaceTransformData.MeshWeight;
				char* tmpBuffer = new char[sizeof(float)];
				memcpy(tmpBuffer, &tmpSize, sizeof(float));
				std::string tmpStr(tmpBuffer, sizeof(float));
				ret += tmpStr;
				delete tmpBuffer;
			}
		}

		return ret;
	}

	void Mesh_Vertex_PCNTs_Skinning::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		Mesh<Vertex_PCNTs_Skinning>::DeserializeBinary(buffer, size, offset);

		{
			memcpy(&_maxBoneCount, buffer + offset, sizeof(int));
			offset += sizeof(int);
		}

		for (int i = 0; i < _maxBoneCount; ++i)
		{
			Float44 tmpBuffer;
			memcpy(&tmpBuffer, buffer + offset, sizeof(Float44));
			offset += sizeof(Float44);
			_boneSpaceTransformData.BoneSpaceTransformBuffer[i] = {
				tmpBuffer.e11, tmpBuffer.e12, tmpBuffer.e13, tmpBuffer.e14,
				tmpBuffer.e21, tmpBuffer.e22, tmpBuffer.e23, tmpBuffer.e24,
				tmpBuffer.e31, tmpBuffer.e32, tmpBuffer.e33, tmpBuffer.e34,
				tmpBuffer.e41, tmpBuffer.e42, tmpBuffer.e43, tmpBuffer.e44,
			};
		}

		memcpy(&_boneSpaceTransformData.MeshIndex, buffer + offset, sizeof(int));
		offset += sizeof(int);

		memcpy(&_boneSpaceTransformData.MeshWeight, buffer + offset, sizeof(float));
		offset += sizeof(float);
	}

	MeshInterface* Mesh_Vertex_PCNTs_Skinning::Clone()
	{
		Mesh_Vertex_PCNTs_Skinning* newMesh = static_cast<Mesh_Vertex_PCNTs_Skinning*>(Mesh<Vertex_PCNTs_Skinning>::Clone());
		newMesh->_maxBoneCount = _maxBoneCount;
		memcpy(&newMesh->_boneSpaceTransformData, &_boneSpaceTransformData, sizeof(MeshToBoneSpaceTransformData));
		return newMesh;
	}

	Vertex_PCNTs_Skinning Mesh_Vertex_PCNTs_Skinning::GetDeserializedVertexText(std::string str)
	{
		str = GetUnitElementText(str, 0).str;
		Vertex_PCNTs_Skinning vertex;
		SerializeableText::DeserializeText(str, vertex);
		return vertex;
	}

	std::string Mesh_Vertex_PCNTs_Skinning::GetSerializedBinaryVertexData(Vertex_PCNTs_Skinning vertex)
	{
		std::string ret;

		{
			Float4 tmp = vertex.Position;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Color;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float4 tmp = vertex.Normal;
			char* tmpBuffer = new char[sizeof(Float4)];
			memcpy(tmpBuffer, &tmp, sizeof(Float4));
			std::string tmpStr(tmpBuffer, sizeof(Float4));
			ret += tmpStr;
		}

		{
			Float2 tmp = vertex.TextureUV;
			char* tmpBuffer = new char[sizeof(Float2)];
			memcpy(tmpBuffer, &tmp, sizeof(Float2));
			std::string tmpStr(tmpBuffer, sizeof(Float2));
			ret += tmpStr;
		}

		{
			{
				int tmpSize = vertex.MaterialIndex;
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
		}

		{
			for (int i = 0; i < 4; ++i)
			{
				{
					int tmpSize = vertex.AffectedBoneIndex[i];
					char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
				{
					float tmpSize = vertex.Weight[i];
					char* tmpBuffer = new char[sizeof(float)];
				memcpy(tmpBuffer, &tmpSize, sizeof(float));
					std::string tmpStr(tmpBuffer, sizeof(float));
					ret += tmpStr;
					delete tmpBuffer;
				}
			}
		}

		return ret;
	}

	Vertex_PCNTs_Skinning Mesh_Vertex_PCNTs_Skinning::GetVertex(const char* buffer, int size, int& offset)
	{
		Vertex_PCNTs_Skinning ret;

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Position = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Color = tmp;
		}

		{
			Float4 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float4));
			offset += sizeof(Float4);
			ret.Normal = tmp;
		}

		{
			Float2 tmp;
			memcpy(&tmp, buffer + offset, sizeof(Float2));
			offset += sizeof(Float2);
			ret.TextureUV = tmp;
		}

		{
			memcpy(&ret.MaterialIndex, buffer + offset, sizeof(unsigned int));
			offset += sizeof(unsigned int);
		}

		{
			for (int i = 0; i < 4; ++i)
			{
				memcpy(&ret.AffectedBoneIndex[i], buffer + offset, sizeof(int));
				offset += sizeof(int);

				memcpy(&ret.Weight[i], buffer + offset, sizeof(float));
				offset += sizeof(float);
			}
		}

		return ret;
	}

	Mesh<Vertex_PCNTs_Skinning>* Mesh_Vertex_PCNTs_Skinning::GetMesh()
	{
		return new Mesh_Vertex_PCNTs_Skinning;
	}

	MeshInterface* Mesh_Vertex_PCNTs_Skinning::ClonedObject()
	{
		return new Mesh_Vertex_PCNTs_Skinning;
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