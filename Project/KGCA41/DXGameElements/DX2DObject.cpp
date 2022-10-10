#include "DX2DObject.h"
#include "Shader.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DXWindow.h"
#include "Common.h"
#include "DXStateManager.h"
#include <cassert>

namespace SSB
{
    extern DXWindow* g_dxWindow;
    extern BasicWindow* g_Window;
    Position2D operator+(Position2D& lValue, Position2D& rValue)
	{
		return { lValue.x + rValue.x, lValue.y + rValue.y };
	}
}

SSB::DX2DObject::DX2DObject(Position2D center, float width, float height) : _center(center), _width(width), _height(height)
{
    //static UINT construct = 0;
    //++construct;
    //std::wstring str = L"Constructor : " + std::to_wstring(construct) + L"\n";
    //OutputDebugString(str.c_str());

    CreateVertexBuffer();
    CreateIndexBuffer();
}

void SSB::DX2DObject::Resize(float width, float height)
{
    _width = width;
    _height = height;
}

bool SSB::DX2DObject::CreateVertexBuffer()
{
    _vertexList.resize(4);

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
        assert(SUCCEEDED(hr));
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
        assert(SUCCEEDED(hr));
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
        _vertexList[i].pos.x = _parentCenter.x + _center.x + hWidth * dx[i];
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
    SimpleVertex2D center{ 0, 0 };
    for (int i = 0; i < ret.size(); ++i)
    {
        center.pos.x += _vertexList[i].pos.x;
        center.pos.y += _vertexList[i].pos.y;
    }
    center.pos.x /= 4.0f;
    center.pos.y /= 4.0f;

    for (int i = 0; i < ret.size(); ++i)
    {
        ret[i] = _vertexList[i];

        Rotate(ret[i], center);

        ret[i].pos.x = ret[i].pos.x / width;
        ret[i].pos.x *= 2;
        ret[i].pos.x -= 1;

        ret[i].pos.y = ret[i].pos.y / height;
        ret[i].pos.y *= 2;
        ret[i].pos.y -= 1;
        ret[i].pos.y = -ret[i].pos.y;
    }

    return ret;
}

void SSB::DX2DObject::Rotate(SimpleVertex2D& vertex, SimpleVertex2D center)
{
    RotateFromParent(vertex);

    SimpleVertex2D tmp = vertex;
    tmp.pos.x -= center.pos.x;
    tmp.pos.y -= center.pos.y;

    tmp.pos.x = (vertex.pos.x - center.pos.x) * cos(_radian) - (vertex.pos.y - center.pos.y) * sin(_radian);
    tmp.pos.y = (vertex.pos.x - center.pos.x) * sin(_radian) + (vertex.pos.y - center.pos.y) * cos(_radian);

    vertex.pos.x = tmp.pos.x + center.pos.x;
    vertex.pos.y = tmp.pos.y + center.pos.y;
}

void SSB::DX2DObject::RotateFromParent(SimpleVertex2D& vertex)
{
    SimpleVertex2D tmp = vertex;
    tmp.pos.x -= _parentCenter.x;
    tmp.pos.y -= _parentCenter.y;

    tmp.pos.x = (vertex.pos.x - _parentCenter.x) * cos(_parentRadian) - (vertex.pos.y - _parentCenter.y) * sin(_parentRadian);
    tmp.pos.y = (vertex.pos.x - _parentCenter.x) * sin(_parentRadian) + (vertex.pos.y - _parentCenter.y) * cos(_parentRadian);

    vertex.pos.x = tmp.pos.x + _parentCenter.x;
    vertex.pos.y = tmp.pos.y + _parentCenter.y;
}

void SSB::DX2DObject::RotateDegree(float degree)
{
    RotateRadian(DegreeToRadian(degree));
}

void SSB::DX2DObject::RotateRadian(float radian)
{
    _radian += radian;
}

bool SSB::DX2DObject::Init()
{
    //static int init = 0;
    //++init;
    //std::wstring str = L"Init : " + std::to_wstring(init) + L"\n";
    //OutputDebugString(str.c_str());

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
        dxObject->UpdateParentData(center, _radian + _parentRadian);
        dxObject->Frame();
    }

    return true;
}

bool SSB::DX2DObject::Render()
{
    g_dxWindow->AddDrawable(this);

    for (auto dxObject : _childObjectList)
    {
        dxObject->Render();
    }

    return true;
}

bool SSB::DX2DObject::Release()
{
    //static int release = 0;
    //++release;
    //std::wstring str = L"Release : " + std::to_wstring(release) + L"\n";
    //OutputDebugString(str.c_str());

    _vertexList.clear();
    _indexList.clear();

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

    _vs = nullptr;
    _ps = nullptr;

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
    dc->OMSetBlendState(DXStateManager::GetInstance().GetBlendState(DXStateManager::kDefaultBlend), 0, -1);
}
