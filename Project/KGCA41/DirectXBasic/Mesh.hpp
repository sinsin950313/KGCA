#pragma once

#include "DXWindow.h"
#include "Mesh.h"
#include "ShaderManager.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

	template<typename VertexType>
	Mesh<VertexType>::Mesh()
	{
	}
	template<typename VertexType>
	Mesh<VertexType>::~Mesh()
	{
		Release();
	}
	template<typename VertexType>
	inline void Mesh<VertexType>::CheckSize()
	{
		float minX = (std::numeric_limits<float>::max)();
		float minY = (std::numeric_limits<float>::max)();
		float minZ = (std::numeric_limits<float>::max)();
		float maxX = (std::numeric_limits<float>::min)();
		float maxY = (std::numeric_limits<float>::min)();
		float maxZ = (std::numeric_limits<float>::min)();
		for (auto vertex : _vertexList)
		{
			minX = min(minX, vertex.Position.x);
			minY = min(minY, vertex.Position.y);
			minZ = min(minZ, vertex.Position.z);

			maxX = max(maxX, vertex.Position.x);
			maxY = max(maxY, vertex.Position.y);
			maxZ = max(maxZ, vertex.Position.z);
		}

		_minVertex = { minX, minY, minZ };
		_maxVertex = { maxX, maxY, maxZ };
	}
	template<typename VertexType>
	inline void Mesh<VertexType>::SetVertexList(std::vector<VertexType> vertexList)
	{
		_vertexList = vertexList;
	}
	template<typename VertexType>
	inline void Mesh<VertexType>::SetIndexList(std::vector<IndexForMeshVertice> indexList)
	{
		_indexList = indexList;
	}
	template<typename VertexType>
	void Mesh<VertexType>::SetVertexShader(VertexShader* shader)
	{
		_vs = shader;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::CreateVertexLayout()
	{
		D3D11_INPUT_ELEMENT_DESC* inputElementDesc;
		int inputElementDescCount;
		SetVertexLayoutDesc(&inputElementDesc, inputElementDescCount);

		HRESULT hr = g_dxWindow->GetDevice()->CreateInputLayout(inputElementDesc, inputElementDescCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
		delete inputElementDesc;

		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::CreateVertexBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(VertexType) * _vertexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_vertexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::CreateIndexBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(_indexList[0])) * _indexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_indexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	template<typename VertexType>
	inline void Mesh<VertexType>::Initialize_AddSubMesh(MeshInterface* mesh)
	{
		_subMeshes.push_back(mesh);
	}
	template<typename VertexType>
	Vector3 Mesh<VertexType>::GetMinVertex()
	{
		return _minVertex;
	}
	template<typename VertexType>
	Vector3 Mesh<VertexType>::GetMaxVertex()
	{
		return _maxVertex;
	}
	template<typename VertexType>
	inline MeshInterface* Mesh<VertexType>::Clone()
	{
		Mesh<VertexType>* ret = static_cast<Mesh<VertexType>*>(ClonedObject());

		ret->_vertexList = _vertexList;
		ret->_indexList = _indexList;
		for (auto subMesh : _subMeshes)
		{
			ret->Initialize_AddSubMesh(subMesh->Clone());
		}

		ret->_minVertex = _minVertex;
		ret->_maxVertex = _maxVertex;
		ret->_vs = _vs;

		return ret;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::Init()
	{
		Build();
		CheckSize();
		InitialVertexShader();
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVertexLayout();

		for (auto subMesh : _subMeshes)
		{
			subMesh->Init();
		}

		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::Frame()
	{
		for (auto subMesh : _subMeshes)
		{
			subMesh->Frame();
		}

		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::Render()
	{
		ID3D11DeviceContext* dc = g_dxWindow->GetDeviceContext();

		dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		dc->IASetInputLayout(_vertexLayout);
		{
			UINT stride = sizeof(VertexType);
			UINT offset = 0;
			dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
		}
		dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		_vs->Render();

		dc->DrawIndexed(_indexList.size(), 0, 0);

		for (auto subMesh : _subMeshes)
		{
			subMesh->Render();
		}

		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::Release()
	{
		if (_vertexLayout != nullptr)
		{
			_vertexLayout->Release();
			_vertexLayout = nullptr;
		}

		_vertexList.clear();

		if (_vertexBuffer != nullptr)
		{
			_vertexBuffer->Release();
			_vertexBuffer = nullptr;
		}

		_indexList.clear();

		if (_indexBuffer != nullptr)
		{
			_indexBuffer->Release();
			_indexBuffer = nullptr;
		}

		_vs = nullptr;

		for (auto subMesh : _subMeshes)
		{
			subMesh->Release();
			delete subMesh;
		}
		_subMeshes.clear();

		return true;
	}
	template<typename VertexType>
	std::string Mesh<VertexType>::SerializeText(int tabCount)
	{
		std::string ret;

		ret += SerializeableText::SerializeableText::GetTabbedStringText(tabCount);
		ret += "[\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _vertexTypeStr;
		ret += "{\"";
		ret += GetVertexType();
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _vertexListStr;
		ret += "{\"";
		ret += std::to_string(_vertexList.size());
		ret += "\"}\n";
		for (auto vertex : _vertexList)
		{
			ret += SerializeableText::SerializeText(tabCount + 2, vertex);
			ret += SerializeableText::GetTabbedStringText(tabCount + 2);
			ret += ",\n";
		}

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _indexListStr;
		ret += "{\"";
		ret += std::to_string(_indexList.size());
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 2);
		ret += "{ ";
		for (auto index : _indexList)
		{
			ret += "{\"";
			ret += std::to_string(index);
			ret += "\"}, ";
		}
		ret += "},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _minVertexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _minVertex);
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _maxVertexStr;
		ret += SerializeableText::SerializeText(tabCount + 2, _maxVertex);
		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += ",\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _vertexShaderStr;
		ret += "{\"";
		ret += _vs->GetFileName();
		ret += "\"},\n";

		ret += SerializeableText::GetTabbedStringText(tabCount + 1);
		ret += _subMeshStr;
		ret += " : {\"";
		ret += std::to_string(_subMeshes.size());
		ret += "\"},\n";
		for (auto subMesh : _subMeshes)
		{
			auto str = subMesh->SerializeText(tabCount + 2);
			ret += str;
			ret += ",\n";
		}

		ret += SerializeableText::GetTabbedStringText(tabCount);
		ret += "]\n";

		return ret;
	}
	template<typename VertexType>
	void Mesh<VertexType>::DeserializeText(std::string& serialedString)
	{
		serialedString = GetUnitObjectText(serialedString, 0).str;
		int offset = 0;

		{
			auto data = GetUnitElementText(serialedString, 0);
			offset = data.offset;
		}

		int vertexCount;
		{
			auto data = GetUnitElementText(serialedString, offset);
			SerializeableText::DeserializeText(data.str, vertexCount);
			offset = data.offset;
		}

		for (int i = 0; i < vertexCount; ++i)
		{
			auto elemData = GetUnitElementText(serialedString, offset);
			std::string elem = elemData.str;
			offset = elemData.offset;
			VertexType vertex = GetDeserializedVertexText(elem);
			_vertexList.push_back(vertex);
		}

		{
			int indexCount;
			{
				offset = serialedString.find(_indexListStr);
				auto elemData = GetUnitElementText(serialedString, offset);
				offset = elemData.offset;
				SerializeableText::DeserializeText(elemData.str, indexCount);
			}
			_indexList.resize(indexCount);

			auto data = GetUnitElementText(serialedString, offset);
			std::string elem = data.str;
			offset = data.offset;

			int indexOffset = 1;
			for (int i = 0; i < indexCount; ++i)
			{
				auto data = GetUnitElementText(elem, indexOffset);
				int val;
				SerializeableText::DeserializeText(data.str, val);
				_indexList[i] = val;
				indexOffset = data.offset;
			}
		}

		{
			offset = serialedString.find(_minVertexStr, offset);
			auto elemData = GetUnitElementText(serialedString, offset);
			std::string elem = elemData.str;
			offset = elemData.offset;
			Float3 tmp;
			SerializeableText::DeserializeText(elem, tmp);
			_minVertex = tmp;
		}

		{
			offset = serialedString.find(_maxVertexStr, offset);
			auto elemData = GetUnitElementText(serialedString, offset);
			std::string elem = elemData.str;
			offset = elemData.offset;
			Float3 tmp;
			SerializeableText::DeserializeText(elem, tmp);
			_maxVertex = tmp;
		}

		{
			offset = serialedString.find(_vertexShaderStr, offset);
			auto atomicData = GetUnitElementText(serialedString, offset);
			_vs = ShaderManager::GetInstance().LoadVertexShader(mtw(GetUnitAtomicText(atomicData.str, 0).str), "VS", "vs_5_0");
		}

		{
			offset = serialedString.find(_subMeshStr, offset);
			auto atomicData = GetUnitElementText(serialedString, offset);
			int subMeshCount;
			SerializeableText::DeserializeText(atomicData.str, subMeshCount);

			for (int i = 0; i < subMeshCount; ++i)
			{
				auto objectData = GetUnitObjectText(serialedString, offset);
				MeshInterface* mesh;
				if (GetVertexType() == Vertex_PCNT_Keyword)
				{
					mesh = new Mesh_Vertex_PCNT;
				}
				else if (GetVertexType() == Vertex_PCNT_Animatable_Keyword)
				{
					mesh = new Mesh_Vertex_PCNT_Animatable;
				}
				else if (GetVertexType() == Vertex_PCNT_Skinning_Keyword)
				{
					mesh = new Mesh_Vertex_PCNT_Skinning;
				}
				else if (GetVertexType() == Vertex_PCNTs_Keyword)
				{
					mesh = new Mesh_Vertex_PCNTs;
				}
				else if (GetVertexType() == Vertex_PCNTs_Animatable_Keyword)
				{
					mesh = new Mesh_Vertex_PCNTs_Animatable;
				}
				else if (GetVertexType() == Vertex_PCNTs_Skinning_Keyword)
				{
					mesh = new Mesh_Vertex_PCNTs_Skinning;
				}
				//if (vertexType == Vertex_PC_Keyword)
				else
				{
					mesh = new Mesh_Vertex_PC;
				}

				mesh->DeserializeText(objectData.str);
				_subMeshes.push_back(mesh);
			}
		}
	}
	template<typename VertexType>
	inline std::string Mesh<VertexType>::SerializeBinary()
	{
		std::string ret;

		{
			{
				int tmpSize = _vertexList.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto vertex : _vertexList)
			{
				ret += GetSerializedBinaryVertexData(vertex);
			}
		}

		{
			{
				int tmpSize = _indexList.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto index : _indexList)
			{
				{
					int tmpSize = index;
					char* tmpBuffer = new char[sizeof(int)];
					memcpy(tmpBuffer, &tmpSize, sizeof(int));
					std::string tmpStr(tmpBuffer, sizeof(int));
					ret += tmpStr;
					delete tmpBuffer;
				}
			}
		}

		{
			Float3 tmp = _minVertex;
			char* tmpBuffer = new char[sizeof(Float3)];
			memcpy(tmpBuffer, &tmp, sizeof(Float3));
			std::string tmpStr(tmpBuffer, sizeof(Float3));
			ret += tmpStr;
		}

		{
			Float3 tmp = _maxVertex;
			char* tmpBuffer = new char[sizeof(Float3)];
			memcpy(tmpBuffer, &tmp, sizeof(Float3));
			std::string tmpStr(tmpBuffer, sizeof(Float3));
			delete tmpBuffer;
			ret += tmpStr;
		}

		{
			{
				int tmpSize = _subMeshes.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			for (auto mesh : _subMeshes)
			{
				ret += mesh->SerializeBinary();
			}
		}

		{
			std::string vertexshaderFileName = _vs->GetFileName();
			{
				int tmpSize = vertexshaderFileName.size();
				char* tmpBuffer = new char[sizeof(int)];
				memcpy(tmpBuffer, &tmpSize, sizeof(int));
				std::string tmpStr(tmpBuffer, sizeof(int));
				ret += tmpStr;
				delete tmpBuffer;
			}
			ret += vertexshaderFileName;
		}

		return ret;
	}
	template<typename VertexType>
	inline void Mesh<VertexType>::DeserializeBinary(const char* buffer, int size, int& offset)
	{
		{
			int vertexCount;
			memcpy(&vertexCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			_vertexList.resize(vertexCount);
			for (int i = 0; i < vertexCount; ++i)
			{
				_vertexList[i] = GetVertex(buffer, size, offset);
			}
		}

		{
			int indexCount;
			memcpy(&indexCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			_indexList.resize(indexCount);
			for (int i = 0; i < indexCount; ++i)
			{
				int index;
				memcpy(&index, buffer + offset, sizeof(int));
				offset += sizeof(int);
				_indexList[i] = index;
			}
		}

		{
			Float3 tmpBuffer;
			memcpy(&tmpBuffer, buffer + offset, sizeof(Float3));
			offset += sizeof(Float3);
			_minVertex = tmpBuffer;
		}

		{
			Float3 tmpBuffer;
			memcpy(&tmpBuffer, buffer + offset, sizeof(Float3));
			offset += sizeof(Float3);
			_maxVertex = tmpBuffer;
		}

		{
			int subMeshCount;
			memcpy(&subMeshCount, buffer + offset, sizeof(int));
			offset += sizeof(int);

			_subMeshes.resize(subMeshCount);
			for(int i = 0; i < subMeshCount; ++i)
			{
				MeshInterface* mesh = GetMesh();
				mesh->DeserializeBinary(buffer, size, offset);
				_subMeshes[i] = mesh;
			}
		}

		{
			int vertexShaderFileNameSize;
			memcpy(&vertexShaderFileNameSize, buffer + offset, sizeof(int));
			offset += sizeof(int);

			char* fileName = new char[vertexShaderFileNameSize];
			memcpy(fileName, buffer + offset, vertexShaderFileNameSize);
			offset += vertexShaderFileNameSize;
			std::string tmpFileName(fileName, vertexShaderFileNameSize);
			delete fileName;
			_vs = ShaderManager::GetInstance().LoadVertexShader(mtw(tmpFileName), "VS", "vs_5_0");
		}
	}
}
