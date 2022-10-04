#include "DX2DObject.h"
#include "Shader.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;
    extern BasicWindow* g_Window;
    Position2D operator+(Position2D& lValue, Position2D& rValue)
	{
		return { lValue.x + rValue.x, lValue.y + rValue.y };
	}
}

void SSB::DX2DObject::Resize(float width, float height)
{
    _width = width;
    _height = height;

    UpdateBoundary();
}

bool SSB::DX2DObject::CreateVertexBuffer()
{
    _vertexList.resize(4);
    UpdateBoundary();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex2D) * _vertexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    auto ndcBoundary = GetNDCBoundary();
    sd.pSysMem = &ndcBoundary.at(0);
    HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

bool SSB::DX2DObject::CreateIndexBuffer()
{
    _indexList.resize(6);
    _indexList =
    {
        0, 1, 2,
        2, 1, 3,
    };

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * _indexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &_indexList.at(0);
    HRESULT hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

void SSB::DX2DObject::UpdateBoundary()
{
    float dx[4]{ -1, 1, -1, 1 };
    float dy[4]{ -1, -1, 1, 1 };

    auto texturePart = _sprite->GetCurrentTexturePart();
    float texU[4]{ texturePart.left, texturePart.right, texturePart.left, texturePart.right };
    float texV[4]{ texturePart.top, texturePart.top, texturePart.bottom, texturePart.bottom };

    float hWidth = _width / 2;
    float hHeight = _height / 2;

    for (int i = 0; i < 4; ++i)
    {
        _vertexList[i].pos.x = _parentCenter.x + _center.x + hWidth* dx[i];
        _vertexList[i].pos.y = _parentCenter.y + _center.y + hHeight * dy[i];
        _vertexList[i].col = { 0.0f, 0.0f, 0.0f, 1.0f };
        _vertexList[i].texParam.u = texU[i];
        _vertexList[i].texParam.v = texV[i];
    }
}

std::vector<SSB::SimpleVertex2D> SSB::DX2DObject::GetNDCBoundary()
{
    float width = g_Window->GetClientWidth();
    float height = g_Window->GetClientHeight();

    std::vector<SimpleVertex2D> ret;
    ret.resize(_vertexList.size());
    for (int i = 0; i < ret.size(); ++i)
    {
        ret[i] = _vertexList[i];

        ret[i].pos.x = _vertexList[i].pos.x / width;
        ret[i].pos.x *= 2;
        ret[i].pos.x -= 1;

        ret[i].pos.y = _vertexList[i].pos.y / height;
        ret[i].pos.y *= 2;
        ret[i].pos.y -= 1;
        ret[i].pos.y = -ret[i].pos.y;
    }

    return ret;
}

bool SSB::DX2DObject::Init()
{
    CreateVertexBuffer();
    CreateIndexBuffer();
    UpdateBoundary();

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT iedCount = sizeof(ied) / sizeof(ied[0]);
	HRESULT hr = g_dxWindow->GetDevice()->CreateInputLayout(ied, iedCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
	if (FAILED(hr))
	{
		return false;
	}

    g_dxWindow->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    for (auto dxObject : _childObjectList)
    {
        dxObject->Init();
    }

    return true;
}

bool SSB::DX2DObject::Frame()
{
    UpdateBoundary();
    auto ndcBoundary = GetNDCBoundary();
    g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &ndcBoundary.at(0), 0, 0);

    _sprite->Frame();

	Position2D center = _center + _parentCenter;
    for (auto dxObject : _childObjectList)
    {
        dxObject->UpdateParentCenter(center);
        dxObject->Frame();
    }

    return true;
}

bool SSB::DX2DObject::Render()
{
    //Draw(g_dxWindow->GetDeviceContext());
    g_dxWindow->AddDrawable(this);

    for (auto dxObject : _childObjectList)
    {
        dxObject->Render();
    }

    return true;
}

bool SSB::DX2DObject::Release()
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
    if (_indexBuffer)
    {
        _indexBuffer->Release();
        _indexBuffer = nullptr;
    }
    if (_sprite)
    {
        _sprite->Release();
        delete _sprite;
        _sprite = nullptr;
    }

    for (auto dxObject : _childObjectList)
    {
        dxObject->Release();
        delete dxObject;
    }
    _childObjectList.clear();

    return true;
}

void SSB::DX2DObject::Draw(ID3D11DeviceContext* dc)
{
    UINT stride = sizeof(SimpleVertex2D);
    UINT offset = 0;

    dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    dc->IASetInputLayout(_vertexLayout);
    dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
    dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
    if (_sprite != nullptr)
    {
        dc->PSSetShaderResources(0, 1, _sprite->GetResource()->GetShaderResourceView());
		ID3D11SamplerState* ss = _sprite->GetSamplerState();
		dc->PSSetSamplers(0, 1, &ss);
    }
    if (_sprite->HasMaskResource())
    {
        dc->PSSetShaderResources(1, 1, _sprite->GetMaskResource()->GetShaderResourceView());
    }
	dc->DrawIndexed(_indexList.size(), 0, 0);
}
