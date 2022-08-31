#include "TriangleDrawer.h"

bool TriangleDrawer::Init()
{
    if (!TDXWindow::Init())
    {
        return false;
    }

    SimpleVertex vertices[] =
    {
        +0.0f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
    bufferDesc.ByteWidth = sizeof(SimpleVertex) * 3;
    bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA subresourceData;
    ZeroMemory(&subresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    subresourceData.pSysMem = vertices;;

    HRESULT hr = GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &_vertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", 0, 0, &_vsCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
    }

    hr = GetDevice()->CreateVertexShader(_vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), NULL, &_vs);
    if (FAILED(hr))
    {
        return false;
    }

	D3D11_INPUT_ELEMENT_DESC inputElementDescs[] = 
    {
        { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
        { "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT elementCount = sizeof(inputElementDescs) / sizeof(inputElementDescs[0]);
    GetDevice()->CreateInputLayout(inputElementDescs, elementCount, _vsCode->GetBufferPointer(), _vsCode->GetBufferSize(), &_inputLayout);

    hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "ps_5_0", 0, 0, &_psCode, &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
    }
    hr = GetDevice()->CreatePixelShader(_psCode->GetBufferPointer(), _psCode->GetBufferSize(), NULL, &_ps);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool TriangleDrawer::Release()
{
    if (!TDXWindow::Release())
    {
        return false;
    }
    Common::Release(_vertexBuffer);
    Common::Release(_inputLayout);
    Common::Release(_vsCode);
    Common::Release(_psCode);
    Common::Release(_vs);
    Common::Release(_ps);

    return true;
}

bool TriangleDrawer::PreRender()
{
    if (!TDXWindow::PreRender())
    {
        return false;
    }
    return true;
}

bool TriangleDrawer::MainRender()
{
    if (!TDXWindow::MainRender())
    {
        return false;
    }

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    GetDeviceContext()->IASetInputLayout(_inputLayout);
    GetDeviceContext()->VSSetShader(_vs, NULL, 0);
    GetDeviceContext()->PSSetShader(_ps, NULL, 0);

    GetDeviceContext()->Draw(3, 0);
    return true;
}

bool TriangleDrawer::PostRender()
{
    if (!TDXWindow::PostRender())
    {
        return false;
    }
    return true;
}
