#include "Map.h"
#include "DXWindow.h"
#include <cassert>
#include "DXStateManager.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

	void Map::CreateVertex()
	{
		int hWidthVertexCount = _widthVertexCount / 2;
		int hHeightVertexCount = _heightVertexCount / 2;

		// z x-->
		// |
		// |
		// v
		_vertexList.resize(_widthVertexCount * _heightVertexCount);
		for (int row = 0; row < _heightVertexCount; ++row)
		{
			for (int col = 0; col < _widthVertexCount; ++col)
			{
				int index = row * _widthVertexCount + col;
				_vertexList[index].position = { (float)(col - hWidthVertexCount) * _cellDistance, 0.0f, (float)(hHeightVertexCount - row) * _cellDistance, 1.0f };
				_vertexList[index].color = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f };
				_vertexList[index].texture = { ((float)col / (float)(_widthVertexCount - 1.0f)) * tileX, ((float)row / (float)(_heightVertexCount - 1.0f)) * tileY };
			}
		}

		// index-- -- -
		//   |  / | /|
		//   | /  |/ |
		//    ---- -- -
		_indexList.resize((_widthVertexCount - 1) * (_heightVertexCount - 1) * 2 * 3);
		unsigned int index = 0;
		for (int row = 0; row < _heightVertexCount - 1; ++row)
		{
			for (int col = 0; col < _widthVertexCount - 1; ++col)
			{
				int vIndex = row * _widthVertexCount + col;
				_indexList[index + 0] = vIndex;
				_indexList[index + 1] = vIndex + 1;
				_indexList[index + 2] = vIndex + _widthVertexCount;

				_indexList[index + 3] = vIndex + _widthVertexCount;
				_indexList[index + 4] = vIndex + 1;
				_indexList[index + 5] = vIndex + _widthVertexCount + 1;

				index += 6;
			}
		}
	}

	bool Map::CreateVertexBuffer()
    {
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(_vertexList[0])) * _vertexList.size();
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
    bool Map::CreateVertexLayout()
    {
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		UINT iedCount = sizeof(ied) / sizeof(ied[0]);
		HRESULT hr = g_dxWindow->GetDevice()->CreateInputLayout(ied, iedCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
		if (FAILED(hr))
		{
			return false;
		}

		g_dxWindow->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//for (auto dxObject : _childObjectList)
		//{
		//	dxObject->Init();
		//}
		return true;
    }
	bool Map::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(ConstantData);
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &_constantData;
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&desc, &sd, &_constantBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
	}
	void Map::UpdateConstantBuffer()
	{
		_constantData.World = GetMatrix().Transpose();
		_constantData.View = g_dxWindow->GetMainCamera()->GetViewMatrix().Transpose();
		_constantData.Projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix().Transpose();

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_constantBuffer, 0, nullptr, &_constantData, 0, 0);
	}
	void Map::Move(Vector3 vec)
	{
		HMatrix44 trans{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			vec.GetX(), vec.GetY(), vec.GetZ(), 1
		};
		_matrix = _matrix * trans;
	}
	OBB Map::GetOBB()
	{
		OBB ret;
		ret.Width = 1.0f;
		ret.Height = 1.0f;
		ret.Depth = 1.0f;
		ret.Matrix = _matrix;
		return ret;
	}
	bool Map::Init()
    {
		CreateVertex();
		_root = new Node(*this, 0, , , _indexList.size(), 0);
        CreateVertexBuffer();
        CreateVertexLayout();
		CreateConstantBuffer();

        return true;
    }
    bool Map::Frame()
    {
		return true;
	}
	bool Map::Render()
	{
		UpdateConstantBuffer();
		_root->Check(_drawingNodeList, g_dxWindow->GetMainCamera());
		g_dxWindow->AddDrawable(this);

		return true;
	}
	bool Map::Release()
	{
		if (_vertexBuffer)
        {
            _vertexBuffer->Release();
			_vertexBuffer = nullptr;
        }
        if (_vertexLayout)
        {
            _vertexLayout->Release();
			_vertexLayout = nullptr;
        }
		_vs = nullptr;
		_ps = nullptr;
		if (_constantBuffer)
		{
			_constantBuffer->Release();
			_constantBuffer = nullptr;
		}

        return true;
    }
    void Map::Draw(ID3D11DeviceContext* dc)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &_vertexList.at(0), 0, 0);

		dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
		dc->IASetInputLayout(_vertexLayout);
		dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
		dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
		dc->PSSetShaderResources(0, 1, _sprite->GetResource()->GetShaderResourceView());
		ID3D11SamplerState* ss = _sprite->GetSamplerState();
		dc->PSSetSamplers(0, 1, &ss);
		dc->PSSetShaderResources(1, 1, _sprite->GetMaskResource()->GetShaderResourceView());
		dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
		dc->VSSetConstantBuffers(0, 1, &_constantBuffer);

		for (auto node : _drawingNodeList)
		{
			dc->IASetIndexBuffer(node->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
			dc->DrawIndexed(node->GetIndexList().size(), 0, 0);
		}
		_drawingNodeList.clear();
	}
	bool Map::Node::CreateIndexBuffer()
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
	bool Map::Node::Init()
	{
		CreateIndexBuffer();
		return true;
	}
	bool Map::Node::Frame()
	{
		return true;
	}
	bool Map::Node::Render()
	{
		return true;
	}
	bool Map::Node::Release()
	{
		return false;
	}
}
