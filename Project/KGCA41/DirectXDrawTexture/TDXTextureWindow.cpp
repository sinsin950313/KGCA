#pragma comment (lib, "d3dcompiler.lib")

#include "TDXTextureWindow.h"
#include "d3dcompiler.h"

using namespace SSB;

bool TDXTextureWindow::Init()
{
    DXWindow::Init();

    HRESULT hr;

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

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &_vertice.at(0);
    hr = GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    hr = DirectX::CreateWICTextureFromFile(GetDevice(), GetDeviceContext(), L"../../Resource/Texture/TextureResource/KGCABK.bmp", &_textureResource, &_textureShaderResourceView);
    if (FAILED(hr))
    {
        return false;
    }

    ID3DBlob* errorCode;

    hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_vsCode, &errorCode);
    if (FAILED(hr))
    {
        if (errorCode != nullptr)
        {
            OutputDebugStringA((char*)errorCode->GetBufferPointer());
            errorCode->Release();
        }
        return false;
    }
    hr = GetDevice()->CreateVertexShader(_vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), NULL, &_vs);
    if (FAILED(hr))
    {
        return false;
    }

    hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "ps_5_0", 0, 0, &_psCode, &errorCode);
    if (FAILED(hr))
    {
        if (errorCode != nullptr)
        {
            OutputDebugStringA((char*)errorCode->GetBufferPointer());
            errorCode->Release();
        }
        return false;
    }
    hr = GetDevice()->CreatePixelShader(_psCode->GetBufferPointer(), _psCode->GetBufferSize(), NULL, &_ps);
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT iedCount = sizeof(ied) / sizeof(ied[0]);
    hr = GetDevice()->CreateInputLayout(ied, iedCount, _vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), &_vertexLayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool TDXTextureWindow::Frame()
{
    DXWindow::Frame();

    return true;
}

bool TDXTextureWindow::Release()
{
    DXWindow::Release();

    if (_vertexBuffer) _vertexBuffer->Release();
    if (_textureResource) _textureResource->Release();
    if (_textureShaderResourceView) _textureShaderResourceView->Release();
    if (_vs) _vs->Release();
    if (_ps) _ps->Release();
    if (_vsCode) _vsCode->Release();
    if (_psCode) _psCode->Release();
    if (_vertexLayout) _vertexLayout->Release();

    return true;
}

bool TDXTextureWindow::PreRender()
{
    DXWindow::PreRender();

    return true;
}

bool TDXTextureWindow::MainRender()
{
    DXWindow::MainRender();

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    GetDeviceContext()->IASetInputLayout(_vertexLayout);
    GetDeviceContext()->VSSetShader(_vs, NULL, 0);
    GetDeviceContext()->PSSetShader(_ps, NULL, 0);
    GetDeviceContext()->PSSetShaderResources(0, 1, &_textureShaderResourceView);
    GetDeviceContext()->Draw(_vertice.size(), 0);

    return true;
}

bool TDXTextureWindow::PostRender()
{
    DXWindow::PostRender();

    return true;
}
