#include "TDX2DObject.h"
#include "TShader.h"
#include "TTexture.h"
#include "TTextureManager.h"
#include "TShaderManager.h"

bool TDX2DObject::Init()
{
    _vertice.resize(6);
    _vertice[0] = { -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    _vertice[1] = { 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    _vertice[2] = { 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
    _vertice[3] = { 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
    _vertice[4] = { -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    _vertice[5] = { -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * _vertice.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    HRESULT hr;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &_vertice.at(0);
    hr = _device->CreateBuffer(&bd, &sd, &_vertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    _texture = TTextureManager::GetInstance().Load(L"../../Resource/KGCABK.bmp");
    _vs = TShaderManager::GetInstance().LoadVertexShader(L"VertexShader.hlsl", "main", "vs_5_0");
    _ps = TShaderManager::GetInstance().LoadPixelShader(L"PixelShader.hlsl", "main", "ps_5_0");

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT iedCount = sizeof(ied) / sizeof(ied[0]);
    hr = _device->CreateInputLayout(ied, iedCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool TDX2DObject::Frame()
{
    return true;
}

bool TDX2DObject::Render()
{
    return true;
}

bool TDX2DObject::Release()
{
    return true;
}

void TDX2DObject::Draw(ID3D11DeviceContext* dc)
{
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    dc->IASetInputLayout(_vertexLayout);
    dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
    dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
    dc->PSSetShaderResources(0, 1, _texture->GetShaderResourceView());
    dc->Draw(_vertice.size(), 0);
}
