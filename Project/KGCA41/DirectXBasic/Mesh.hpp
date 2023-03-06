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
	std::string Mesh<VertexType>::Serialize(int tabCount)
	{
		std::string ret;

		ret += GetTabbedString(tabCount);
		ret += "[\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "Vertex Type : ";
		ret += GetVertexType();
		ret += ",\n";

		ret += GetTabbedString(tabCount + 1);
		ret += "Vertex List\n";
		for (auto vertex : _vertexList)
		{
			ret += Serializeable::Serialize(tabCount + 2, vertex);
			ret += GetTabbedString(tabCount + 2);
			ret += ",\n";
		}

		ret += GetTabbedString(tabCount + 1);
		ret += "Index List\n";

		ret += GetTabbedString(tabCount + 2);
		ret += "{ ";
		for (auto index : _indexList)
		{
			ret += std::to_string(index);
			ret += ", ";
		}
		ret += "},\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Min Vertex\n";
		ret += Serializeable::Serialize(tabCount + 2, _minVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Max Vertex\n";
		ret += Serializeable::Serialize(tabCount + 2, _maxVertex);
		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "Vertex Shader File Name : ";
		ret += _vs->GetFileName();
		ret += ",\n";

		ret += Serializeable::GetTabbedString(tabCount + 1);
		ret += "SubMesh";
		ret += ",\n";
		for (auto subMesh : _subMeshes)
		{
			ret += subMesh->Serialize(tabCount + 2);
			ret += ",\n";
		}

		ret += GetTabbedString(tabCount);
		ret += "]\n";

		return ret;
	}
	template<typename VertexType>
	void Mesh<VertexType>::Deserialize(std::string serialedString)
	{
		{
			std::regex re(GetVertexRegex());
			std::smatch match;

			while (std::regex_search(serialedString, match, re))
			{
				std::string str = match.str();
				serialedString = match.suffix();
				VertexType vertex;
				DeSerialize(str, vertex);
				_vertexList.push_back(vertex);
			}
		}

		{
			std::regex re(R"(\s+Index List\s+\{ ([\s\S]*) \},)");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string indexListStr = match.str();
			serialedString = match.suffix();

			{
				std::regex indexReg("[0-9]+");
				while (std::regex_search(indexListStr, match, indexReg))
				{
					_indexList.push_back(std::stoi(match.str()));
					indexListStr = match.suffix();
				}
			}
		}

		{
			std::regex re(R"(Min Vertex\s*\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = R"(\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})";
			std::regex_search(str, match, re);

			Float3 tmp;
			DeSerialize(match.str(), tmp);
			_minVertex = tmp;
		}

		{
			std::regex re(R"(Max Vertex\s*\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			re = R"(\{[0-9.e+-]+, [0-9.e+-]+, [0-9.e+-]+\})";
			std::regex_search(str, match, re);

			Float3 tmp;
			DeSerialize(match.str(), tmp);
			_maxVertex = tmp;
		}

		{
			std::regex re("Vertex Shader File Name : .*.hlsl,");
			std::smatch match;

			std::regex_search(serialedString, match, re);
			std::string str = match.str();
			serialedString = match.suffix();

			std::string tmp = "Vertex Shader File Name : ";
			int offset = tmp.size();
			std::string vertexShaderFileName;
			while (str[offset] != ',')
			{
				vertexShaderFileName += str[offset];
				++offset;
			}

			_vs = ShaderManager::GetInstance().LoadVertexShader(mtw(vertexShaderFileName), "VS", "vs_5_0");
		}


		std::regex subMeshReg("SubMesh,");
		std::smatch match;

		if(std::regex_search(serialedString, match, subMeshReg))
		{
			std::regex re(R"(\[([\s\S])\])");

			while (std::regex_search(serialedString, match, re))
			{
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

				mesh->Deserialize(match.str());
				serialedString = match.suffix();
			}
		}
	}
}