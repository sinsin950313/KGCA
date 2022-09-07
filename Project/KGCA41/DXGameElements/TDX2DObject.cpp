#include "TDX2DObject.h"
#include "TShader.h"
#include "TTexture.h"
#include "TTextureManager.h"
#include "TShaderManager.h"
#include "TDXWindow.h"

extern TDXWindow* g_dxWindow;
extern TBasicWindow* g_Window;

void TDX2DObject::UpdateBoundary()
{
    float dx[4]{ -1, 1, -1, 1 };
    float dy[4]{ 1, 1, -1, -1 };
    float texU[4]{ 0, 1, 0, 1 };
    float texV[4]{ 0, 0, 1, 1 };

    float hWidth = _width / 2;
    float hHeight = _height / 2;

    for (int i = 0; i < 4; ++i)
    {
        _boundaryVertice[i].pos.x = _center.x + hWidth* dx[i];
        _boundaryVertice[i].pos.y = _center.y + hHeight * dy[i];
        _boundaryVertice[i].col = { 0.0f, 0.0f, 0.0f, 1.0f };
        _boundaryVertice[i].texParam.u = texU[i];
        _boundaryVertice[i].texParam.v = texV[i];
    }

    _orderedBoundaryVertice[0] = _boundaryVertice[0];
    _orderedBoundaryVertice[1] = _boundaryVertice[1];
    _orderedBoundaryVertice[2] = _boundaryVertice[2];
    _orderedBoundaryVertice[3] = _boundaryVertice[2];
    _orderedBoundaryVertice[4] = _boundaryVertice[1];
    _orderedBoundaryVertice[5] = _boundaryVertice[3];
}

std::vector<SimpleVertex2D> TDX2DObject::GetNDCBoundary()
{
    float width = g_Window->GetClientWidth();
    float height = g_Window->GetClientWidth();

    std::vector<SimpleVertex2D> ret;
    ret.resize(_orderedBoundaryVertice.size());
    for (int i = 0; i < ret.size(); ++i)
    {
        ret[i] = _orderedBoundaryVertice[i];

        ret[i].pos.x = _orderedBoundaryVertice[i].pos.x / width;
        ret[i].pos.x *= 2;
        ret[i].pos.x -= 1;

        ret[i].pos.y = _orderedBoundaryVertice[i].pos.y / height;
        ret[i].pos.y *= 2;
        ret[i].pos.y -= 1;
    }

    return ret;
}

bool TDX2DObject::Init()
{
    _boundaryVertice.resize(4);
    _orderedBoundaryVertice.resize(6);
    UpdateBoundary();

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex2D) * _orderedBoundaryVertice.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    HRESULT hr;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    auto ndcBoundary = GetNDCBoundary();
    sd.pSysMem = &ndcBoundary.at(0);
    hr = g_dxWindow->GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
    if (FAILED(hr))
    {
        return false;
    }

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT iedCount = sizeof(ied) / sizeof(ied[0]);
	hr = g_dxWindow->GetDevice()->CreateInputLayout(ied, iedCount, _vs->GetCode()->GetBufferPointer(), _vs->GetCode()->GetBufferSize(), &_vertexLayout);
	if (FAILED(hr))
	{
		return false;
	}

    g_dxWindow->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return true;
}

bool TDX2DObject::Frame()
{
    UpdateBoundary();
    auto ndcBoundary = GetNDCBoundary();
    g_dxWindow->GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &ndcBoundary.at(0), 0, 0);

    return true;
}

bool TDX2DObject::Render()
{
    Draw(g_dxWindow->GetDeviceContext());
    return true;
}

bool TDX2DObject::Release()
{
    if (_vertexBuffer) _vertexBuffer->Release();
    if (_vertexLayout) _vertexLayout->Release();

    return true;
}

void TDX2DObject::Draw(ID3D11DeviceContext* dc)
{
    UINT stride = sizeof(SimpleVertex2D);
    UINT offset = 0;

    dc->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    dc->IASetInputLayout(_vertexLayout);
    dc->VSSetShader((ID3D11VertexShader*)_vs->GetShader(), NULL, 0);
    dc->PSSetShader((ID3D11PixelShader*)_ps->GetShader(), NULL, 0);
    dc->PSSetShaderResources(0, 1, _texture->GetShaderResourceView());
    ID3D11SamplerState* ss = _texture->GetSamplerState();
    dc->PSSetSamplers(0, 1, &ss);
    dc->Draw(_orderedBoundaryVertice.size(), 0);
}
