#pragma once

#include "DXWindow.h"
#include "Mesh.h"

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
	inline void Mesh<VertexType>::SetAdditionalSubMesh(MeshInterface* mesh)
	{
		_subMeshes.push_back(mesh);
	}
	template<typename VertexType>
	void Mesh<VertexType>::SetVertexShader(VertexShader* shader)
	{
		_vs = shader;
	}
	//template<typename VertexType>
	//void Mesh<VertexType>::SetPixelShader(PixelShader* shader)
	//{
	//	_ps = shader;
	//}
	//template<typename VertexType>
	//void SetTextureData(std::map<IndexForMaterial, TextureResource*> textureData)
	//{
	//	_resourceCount = textureData.size();

	//	_shaderResourceViewList = new ID3D11ShaderResourceView*[_resourceCount];
	//	_samplerStateList = new ID3D11SamplerState * [_resourceCount];

	//	for (int i = 0; i < _resourceCount; ++i)
	//	{
	//		auto iter = textureData.find(i)->second;
	//		_shaderResourceViewList[i] = iter->GetResource()->GetShaderResourceView();
	//		_samplerStateList[i] = iter->GetSamplerState();
	//	}
	//}
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
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateVertexLayout();

		return true;
	}
	template<typename VertexType>
	bool Mesh<VertexType>::Frame()
	{
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

		//dc->PSSetSamplers(0, _resourceCount, _samplerStateList);
		//dc->PSSetShaderResources(0, _resourceCount, _shaderResourceViewList);
		//_ps->Render();

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
		//_ps = nullptr;

		//if (_samplerStateList != nullptr)
		//{
		//	for (int i = 0; i < _resourceCount; ++i)
		//	{
		//		_samplerStateList[i] = nullptr;
		//	}
		//	delete _samplerStateList;
		//	_samplerStateList = nullptr;
		//}

		//if (_shaderResourceViewList != nullptr)
		//{
		//	for (int i = 0; i < _resourceCount; ++i)
		//	{
		//		_shaderResourceViewList[i] = nullptr;
		//	}
		//	delete _shaderResourceViewList;
		//	_shaderResourceViewList = nullptr;
		//}

		return true;
	}
}
