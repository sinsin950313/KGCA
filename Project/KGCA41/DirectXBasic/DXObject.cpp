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
    bool DXObject::Init()
    {
        _model->Init();
        //_model->Build();

        CreateVertexBuffer();
        CreateIndexBuffer();
        CreateVertexLayout();

        return true;
    }
    bool DXObject::Frame()
    {
		//static Float3 vPos{ 0, 10, 0 };
		//static Float3 vTarget{ 0, 0, 0 };
		//float coeff = 0.0001f;
		//if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		//{
		//	vPos.z += 10.0f * coeff;
		//	vTarget.z += 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		//{
		//	vPos.z -= 10.0f * coeff;
		//	vTarget.z -= 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		//{
		//	vPos.x -= 10.0f * coeff;
		//	vTarget.x -= 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		//{
		//	vPos.x += 10.0f * coeff;
		//	vTarget.x += 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
		//{
		//	vPos.y += 10.0f * coeff;
		//	vTarget.y += 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('E') == EKeyState::KEY_HOLD)
		//{
		//	vPos.y -= 10.0f * coeff;
		//	vTarget.y -= 10.0f * coeff;
		//}

		//Vector3 up{ 0, 1, 0 };
		//Vector3 pos{ vPos.x, vPos.y, vPos.z - 10 };
		//Vector3 target{ vTarget.x, vTarget.y, vTarget.z };
		////Vector3 target{ 0, 0, 0 };
		//HMatrix44 view = HMatrix44::LookAtMatrix(pos, target, up);
		//view = view.Inverse();

		//HMatrix44 perspective;
		//{
		//	float    h, w, Q;
		//	float fNearPlane = 1.0f;
		//	float fFarPlane = 100.0f;
		//	float fovy = 3.141592f * 0.5f;
		//	float Aspect = 800.0f / 600.0f;

		//	h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
		//	w = h / Aspect;

		//	Q = fFarPlane / (fFarPlane - fNearPlane);

		//	HMatrix44 ret
		//	{
		//		w, 0, 0, 0,
		//		0, h, 0, 0,
		//		0, 0, Q, 1,
		//		0, 0, -Q * fNearPlane, 0
		//	};

		//	memcpy(&perspective, &ret, sizeof(HMatrix44));
		//}

		//_model->Frame();
		static float val = 0.001f;
		_matrix = _matrix * HMatrix44::RotateFromYAxis(val);

		return true;
	}
	bool DXObject::Render()
	{
		g_dxWindow->AddDrawable(this);

		return true;
	}
	bool DXObject::Release()
	{
		if (_vertexBuffer)
        {
            _vertexBuffer->Release();
        }
        if (_indexBuffer)
        {
            _indexBuffer->Release();
        }
        if (_vertexLayout)
        {
            _vertexLayout->Release();
        }
		_vs = nullptr;
		_ps = nullptr;
        if (_model)
        {
            _model->Release();
            delete _model;
            _model = nullptr;
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
		//	dc->DrawIndexed(_direction->GetIndexList().size(), 0, 0);
		//	dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
		//}

		// Move to Model Frame
		HMatrix44 view = g_dxWindow->GetMainCamera()->GetViewMatrix();
		HMatrix44 projection = g_dxWindow->GetMainCamera()->GetProjectionMatrix();

		// Use Constant Buffer instead
		auto& vertexList = _model->GetVertexList();
		std::vector<Vertex> update;
		for (int i = 0; i < vertexList.size(); ++i)
		{
			HVector4 position{ vertexList[i].position, 1.0f };
			position = position * _matrix;
			position = position * view;
			position = position * projection;
			position.Normalize();

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
		dc->DrawIndexed(_model->GetIndexList().size(), 0, 0);
		dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
    }
}
