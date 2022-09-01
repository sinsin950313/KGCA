#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "DirectXTK.lib")

#include "RMTestWindow.h"
#include "TTextureManager.h"
#include "TTexture.h"
#include "TShaderManager.h"
#include "TShader.h"

bool RMTestWindow::Init()
{
    TDXWindow::Init();

    TTextureManager::GetInstance().Set(GetDevice(), GetDeviceContext());
    TShaderManager::GetInstance().Set(GetDevice());

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

    _texture = TTextureManager::GetInstance().Load(L"../../Resource/KGCABK.bmp");
    _vertexShader = TShaderManager::GetInstance().LoadVertexShader(L"VertexShader.hlsl", "main", "vs_5_0");
    _pixelShader = TShaderManager::GetInstance().LoadPixelShader(L"PixelShader.hlsl", "main", "ps_5_0");

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT iedCount = sizeof(ied) / sizeof(ied[0]);
    hr = GetDevice()->CreateInputLayout(ied, iedCount, _vertexShader->GetCode()->GetBufferPointer(), _vertexShader->GetCode()->GetBufferSize(), &_vertexLayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool RMTestWindow::Frame()
{
    TDXWindow::Frame();
    return true;
}

bool RMTestWindow::Render()
{
    TDXWindow::Render();
    return true;
}

bool RMTestWindow::Release()
{
    TDXWindow::Release();

    if (_vertexBuffer) _vertexBuffer->Release();
    //if (_texture) _texture->Release();
    //if (_vertexShader) _vertexShader->Release();
    //if (_pixelShader) _pixelShader->Release();
    if (_vertexLayout) _vertexLayout->Release();

    return true;
}

bool RMTestWindow::PreRender()
{
    TDXWindow::PreRender();
    return true;
}

bool RMTestWindow::MainRender()
{
    TDXWindow::MainRender();

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    GetDeviceContext()->IASetInputLayout(_vertexLayout);
    GetDeviceContext()->VSSetShader((ID3D11VertexShader*)_vertexShader->GetShader(), NULL, 0);
    GetDeviceContext()->PSSetShader((ID3D11PixelShader*)_pixelShader->GetShader(), NULL, 0);
    GetDeviceContext()->PSSetShaderResources(0, 1, _texture->GetShaderResourceView());
    GetDeviceContext()->Draw(_vertice.size(), 0);

    return true;
}

bool RMTestWindow::PostRender()
{
    TDXWindow::PostRender();
    return true;
}
