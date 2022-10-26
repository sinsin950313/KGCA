#include "DXObject.h"
#include "DXWindow.h"
#include <cassert>
#include "HCCalculator.h"
#include "DXStateManager.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

    bool DXObject::CreateVertexBuffer()
    {
        auto& vertexList = _model->GetVertexList();
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(vertexList[0])) * vertexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &vertexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
		return true;
    }
	bool DXObject::CreateIndexBuffer()
	{
        auto indexList = _model->GetIndexList();
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(decltype(indexList[0])) * indexList.size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &indexList.at(0);
		HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}
        return true;
    }
    bool DXObject::CreateVertexLayout()
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
	bool DXObject::CreateConstantBuffer()
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
	void DXObject::UpdateConstantBuffer()
	{
		_constantData.World = GetMatrix().Transpose();
		_constantData.View = g_dxWindow->GetMainCamera()->GetViewMatrix().Transpose();
		_constantData.Projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix().Transpose();

		g_dxWindow->GetDeviceContext()->UpdateSubresource(_constantBuffer, 0, nullptr, &_constantData, 0, 0);
	}
	void DXObject::Move(Vector3 vec)
	{
		HMatrix44 trans{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			vec.GetX(), vec.GetY(), vec.GetZ(), 1
		};
		_matrix = _matrix * trans;
	}
	void DXObject::Rotate(float pitch, float yaw)
	{
		_matrix = _matrix * HMatrix44::RotateFromXAxis(pitch) * HMatrix44::RotateFromYAxis(yaw);
	}
	OBB DXObject::GetOBB()
	{
		OBB ret;
		ret.Width = 1.0f;
		ret.Height = 1.0f;
		ret.Depth = 1.0f;
		ret.Matrix = _matrix;
		return ret;
	}
	bool DXObject::Init()
    {
        _model->Init();

        CreateVertexBuffer();
        CreateIndexBuffer();
        CreateVertexLayout();
		CreateConstantBuffer();

        return true;
    }
    bool DXObject::Frame()
    {

		return true;
	}
	bool DXObject::Render()
	{
		if (g_dxWindow->GetMainCamera()->IsRender(this))
		{
			UpdateConstantBuffer();
			g_dxWindow->AddDrawable(this);
		}
		else
		{
			OutputDebugString(L"Invisible\n");
		}

		return true;
	}
	bool DXObject::Release()
	{
		if (_vertexBuffer)
        {
            _vertexBuffer->Release();
			_vertexBuffer = nullptr;
        }
        if (_indexBuffer)
        {
            _indexBuffer->Release();
			_indexBuffer = nullptr;
        }
        if (_vertexLayout)
        {
            _vertexLayout->Release();
			_vertexLayout = nullptr;
        }
		_vs = nullptr;
		_ps = nullptr;
        if (_model)
        {
            _model->Release();
            delete _model;
            _model = nullptr;
        }
		if (_constantBuffer)
		{
			_constantBuffer->Release();
			_constantBuffer = nullptr;
		}

        return true;
    }
    void DXObject::Draw(ID3D11DeviceContext* dc)
    {
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		//{
		//	// Move to Model Frame
		//	HMatrix44 view = g_dxWindow->GetMainCamera()->GetViewMatrix();
		//	HMatrix44 projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix();

		//	// Use Constant Buffer instead
		//	auto& vertexList = _direction->GetVertexList();
		//	std::vector<Vertex> update;
		//	for (int i = 0; i < vertexList.size(); ++i)
		//	{
		//		HVector4 position{ vertexList[i].position, 1.0f };
		//		position = position * view;
		//		position = position * projection;
		//		position.Normalize();

		//		Vertex vertex = vertexList[i];
		//		memcpy(&vertex.position, &position, sizeof(Float4));
		//		update.push_back(vertex);
		//	}
		//	g_dxWindow->GetDeviceContext()->UpdateSubresource(_directionVertexBuffer, NULL, NULL, &update.at(0), 0, 0);

		//	dc->IASetVertexBuffers(0, 1, &_directionVertexBuffer, &stride, &offset);
		//	dc->IASetIndexBuffer(_directionIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//	dc->IASetInputLayout(_vertexLayout);
		//	dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
		//	dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
		//	dc->PSSetShaderResources(0, 1, _direction->GetSprite()->GetResource()->GetShaderResourceView());
		//	ID3D11SamplerState* ss = _direction->GetSprite()->GetSamplerState();
		//	dc->PSSetSamplers(0, 1, &ss);
		//	dc->PSSetShaderResources(1, 1, _direction->GetSprite()->GetMaskResource()->GetShaderResourceView());
		//	dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
		//	dc->DrawIndexed(_direction->GetIndexList().size(), 0, 0);
		//}

		{
			// Move to Model Frame
			//HMatrix44 view = g_dxWindow->GetMainCamera()->GetViewMatrix();
			//HMatrix44 projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix();

			// Use Constant Buffer instead
			auto& vertexList = _model->GetVertexList();
			std::vector<Vertex> update;
			for (int i = 0; i < vertexList.size(); ++i)
			{
				HVector4 position{ vertexList[i].position, 1.0f };
				//position = position * _matrix;
				//position = position * view;
				//position = position * projection;
				//position.Normalize();

				Vertex vertex = vertexList[i];
				memcpy(&vertex.position, &position, sizeof(Float4));
				update.push_back(vertex);
			}
			g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &update.at(0), 0, 0);

			dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
			dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
			dc->IASetInputLayout(_vertexLayout);
			dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
			dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
			dc->PSSetShaderResources(0, 1, _model->GetSprite()->GetResource()->GetShaderResourceView());
			ID3D11SamplerState* ss = _model->GetSprite()->GetSamplerState();
			dc->PSSetSamplers(0, 1, &ss);
			dc->PSSetShaderResources(1, 1, _model->GetSprite()->GetMaskResource()->GetShaderResourceView());
			dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
			dc->VSSetConstantBuffers(0, 1, &_constantBuffer);
			dc->DrawIndexed(_model->GetIndexList().size(), 0, 0);
		}
    }
}