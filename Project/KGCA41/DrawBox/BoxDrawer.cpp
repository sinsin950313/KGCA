#include "BoxDrawer.h"
#include <cassert>
#include "InputManager.h"
#include "HCCalculator.h"

bool BoxDrawer::Init()
{
    if (!DXWindow::Init())
    {
        return false;
    }

    InputManager::GetInstance().Init();

    // »ó´Ü
      // 5    6
      // 1    2
      // ÇÏ´Ü
      // 4    7
      // 0    3  
      // ¾Õ¸é

    //_vertexList.resize(3);
    //_vertexList[0] = SimpleVertex{ Float4{+0.0f, +0.5f, 0.5f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float2(0, 0) };
    //_vertexList[1] = SimpleVertex{ Float4{+0.5f, -0.5f, 0.5f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float2(0, 0) };
    //_vertexList[2] = SimpleVertex{ Float4{-0.5f, -0.5f, 0.5f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0, 0) };

    // over c++17
    _vertexList.resize(24);
    _vertexList[0] = SimpleVertex{Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[1] = SimpleVertex{Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[2] = SimpleVertex{Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[3] = SimpleVertex{Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.5f}};
    // µÞ¸é
    _vertexList[4] = SimpleVertex{Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[5] = SimpleVertex{Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[6] = SimpleVertex{Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[7] = SimpleVertex{Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.5f}};

    // ¿À¸¥ÂÊ
    _vertexList[8] = SimpleVertex{Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[9] = SimpleVertex{Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[10] = SimpleVertex{Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[11] = SimpleVertex{Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.0f, 0.5f}};

    // ¿ÞÂÊ
    _vertexList[12] = SimpleVertex{Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[13] = SimpleVertex{Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[14] = SimpleVertex{Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[15] = SimpleVertex{Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.5f}};

    // À­¸é
    _vertexList[16] = SimpleVertex{Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[17] = SimpleVertex{Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[18] = SimpleVertex{Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[19] = SimpleVertex{Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.5f}};

    // ¾Æ·§¸é
    _vertexList[20] = SimpleVertex{Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.0f}};
    _vertexList[21] = SimpleVertex{Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.0f}};
    _vertexList[22] = SimpleVertex{Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.5f}};
    _vertexList[23] = SimpleVertex{Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.5f}};

    HRESULT hr;
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = sizeof(SimpleVertex) * _vertexList.size();
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
        sd.pSysMem = &_vertexList.at(0);
        HRESULT hr = GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer);
        if (FAILED(hr))
        {
            assert(SUCCEEDED(hr));
            return false;
        }
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
		{ "Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
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

    //_indexList.resize(3);
    //int iIndex = 0;
    //_indexList[iIndex++] = 0;
    //_indexList[iIndex++] = 1;
    //_indexList[iIndex++] = 2;

    _indexList.resize(36);
    int iIndex = 0;
    _indexList[iIndex++] = 0; 	_indexList[iIndex++] = 1; 	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 0;	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 3;
    _indexList[iIndex++] = 4; 	_indexList[iIndex++] = 5; 	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 4;	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 7;
    _indexList[iIndex++] = 8; 	_indexList[iIndex++] = 9; 	_indexList[iIndex++] = 10; _indexList[iIndex++] = 8;	_indexList[iIndex++] = 10; _indexList[iIndex++] = 11;
    _indexList[iIndex++] = 12; _indexList[iIndex++] = 13; _indexList[iIndex++] = 14; _indexList[iIndex++] = 12;	_indexList[iIndex++] = 14; _indexList[iIndex++] = 15;
    _indexList[iIndex++] = 16; _indexList[iIndex++] = 17; _indexList[iIndex++] = 18; _indexList[iIndex++] = 16;	_indexList[iIndex++] = 18; _indexList[iIndex++] = 19;
    _indexList[iIndex++] = 20; _indexList[iIndex++] = 21; _indexList[iIndex++] = 22; _indexList[iIndex++] = 20;	_indexList[iIndex++] = 22; _indexList[iIndex++] = 23;

    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = sizeof(DWORD) * _indexList.size();
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
        sd.pSysMem = &_indexList.at(0);
        HRESULT hr = GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer);
        if (FAILED(hr))
        {
            assert(SUCCEEDED(hr));
            return false;
        }
    }

    GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // DepthStencil Test
    {
        _vertexList1.resize(24);
        _vertexList1[0] = SimpleVertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[1] = SimpleVertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[2] = SimpleVertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[3] = SimpleVertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.5f} };
        // µÞ¸é
        _vertexList1[4] = SimpleVertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[5] = SimpleVertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[6] = SimpleVertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[7] = SimpleVertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.5f} };

        // ¿À¸¥ÂÊ
        _vertexList1[8] = SimpleVertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[9] = SimpleVertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[10] = SimpleVertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[11] = SimpleVertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 0.5f}, Float2{0.0f, 0.5f} };

        // ¿ÞÂÊ
        _vertexList1[12] = SimpleVertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[13] = SimpleVertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[14] = SimpleVertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[15] = SimpleVertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 0.5f}, Float2{0.0f, 0.5f} };

        // À­¸é
        _vertexList1[16] = SimpleVertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[17] = SimpleVertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[18] = SimpleVertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[19] = SimpleVertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.5f} };

        // ¾Æ·§¸é
        _vertexList1[20] = SimpleVertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.0f} };
        _vertexList1[21] = SimpleVertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.0f} };
        _vertexList1[22] = SimpleVertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.5f, 0.5f} };
        _vertexList1[23] = SimpleVertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 0.5f}, Float2{0.0f, 0.5f} };

        HRESULT hr;
        {
            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.ByteWidth = sizeof(SimpleVertex) * _vertexList1.size();
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
            sd.pSysMem = &_vertexList1.at(0);
            HRESULT hr = GetDevice()->CreateBuffer(&bd, &sd, &_vertexBuffer1);
            if (FAILED(hr))
            {
                assert(SUCCEEDED(hr));
                return false;
            }
        }

        _indexList1.resize(36);
        int iIndex = 0;
        _indexList1[iIndex++] = 0; 	_indexList1[iIndex++] = 1; 	_indexList1[iIndex++] = 2; 	_indexList1[iIndex++] = 0;	_indexList1[iIndex++] = 2; 	_indexList1[iIndex++] = 3;
        _indexList1[iIndex++] = 4; 	_indexList1[iIndex++] = 5; 	_indexList1[iIndex++] = 6; 	_indexList1[iIndex++] = 4;	_indexList1[iIndex++] = 6; 	_indexList1[iIndex++] = 7;
        _indexList1[iIndex++] = 8; 	_indexList1[iIndex++] = 9; 	_indexList1[iIndex++] = 10; _indexList1[iIndex++] = 8;	_indexList1[iIndex++] = 10; _indexList1[iIndex++] = 11;
        _indexList1[iIndex++] = 12; _indexList1[iIndex++] = 13; _indexList1[iIndex++] = 14; _indexList1[iIndex++] = 12;	_indexList1[iIndex++] = 14; _indexList1[iIndex++] = 15;
        _indexList1[iIndex++] = 16; _indexList1[iIndex++] = 17; _indexList1[iIndex++] = 18; _indexList1[iIndex++] = 16;	_indexList1[iIndex++] = 18; _indexList1[iIndex++] = 19;
        _indexList1[iIndex++] = 20; _indexList1[iIndex++] = 21; _indexList1[iIndex++] = 22; _indexList1[iIndex++] = 20;	_indexList1[iIndex++] = 22; _indexList1[iIndex++] = 23;

        {
            D3D11_BUFFER_DESC bd;
            ZeroMemory(&bd, sizeof(bd));
            bd.ByteWidth = sizeof(DWORD) * _indexList1.size();
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
            sd.pSysMem = &_indexList1.at(0);
            HRESULT hr = GetDevice()->CreateBuffer(&bd, &sd, &_indexBuffer1);
            if (FAILED(hr))
            {
                assert(SUCCEEDED(hr));
                return false;
            }
        }
    }

    return true;
}

bool BoxDrawer::Frame()
{
    DXWindow::Frame();

    InputManager::GetInstance().Frame();
    static Float3 vPos{ 0, 0, 0 };
    static Float3 vTarget{ 0, 0, 0 };
    float coeff = 0.0001f;
    if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
    {
        vPos.z += 10.0f * coeff;
        vTarget.z += 10.0f * coeff;
    }
    if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
    {
        vPos.z -= 10.0f * coeff;
        vTarget.z -= 10.0f * coeff;
    }
    if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
    {
        vPos.x -= 10.0f * coeff;
        vTarget.x -= 10.0f * coeff;
    }
    if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
    {
        vPos.x += 10.0f * coeff;
        vTarget.x += 10.0f * coeff;
    }
    if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
    {
        vPos.y += 10.0f * coeff;
        vTarget.y += 10.0f * coeff;
    }
    if (InputManager::GetInstance().GetKeyState('E') == EKeyState::KEY_HOLD)
    {
        vPos.y -= 10.0f * coeff;
        vTarget.y -= 10.0f * coeff;
    }

    Vector3 up{ 0, 1, 0 };
    Vector3 pos{ vPos.x, vPos.y, vPos.z - 10 };
    Vector3 target{ vTarget.x, vTarget.y, vTarget.z };
    //Vector3 target{ 0, 0, 0 };
    HMatrix44 view = HMatrix44::LookAtMatrix(pos, target, up);
    view = view.Inverse();

    HMatrix44 perspective;
    {
        float    h, w, Q;
        float fNearPlane = 1.0f;
        float fFarPlane = 100.0f;
        float fovy = 3.141592f * 0.5f;
        float Aspect = 800.0f / 600.0f;

        h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
        w = h / Aspect;

        Q = fFarPlane / (fFarPlane - fNearPlane);

        HMatrix44 ret
        {
            w, 0, 0, 0,
            0, h, 0, 0,
            0, 0, Q, 1,
            0, 0, -Q * fNearPlane, 0
        };

        memcpy(&perspective, &ret, sizeof(HMatrix44));
    }

    std::vector<SimpleVertex> update;
    for (int i = 0; i < _vertexList.size(); ++i)
    {
        HVector4 position {_vertexList[i].position, 1.0f};
        position = position * view;
        position = position * perspective;
        position.Normalize();

        SimpleVertex vertex = _vertexList[i];
        memcpy(&vertex.position, &position, sizeof(Float4));
        update.push_back(vertex);
    }
    GetDeviceContext()->UpdateSubresource(_vertexBuffer, NULL, NULL, &update.at(0), 0, 0);

    {
        std::vector<SimpleVertex> update1;
        for (int i = 0; i < _vertexList1.size(); ++i)
        {
			HVector4 position{ _vertexList1[i].position, 1.0f };
			position = position * HMatrix44(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 1, 5, 1
			);
			position = position * view;
			position = position * perspective;
			position.Normalize();

			SimpleVertex vertex = _vertexList1[i];
			memcpy(&vertex.position, &position, sizeof(Float4));
			update1.push_back(vertex);
        }
        GetDeviceContext()->UpdateSubresource(_vertexBuffer1, NULL, NULL, &update1.at(0), 0, 0);
    }

    return true;
}

bool BoxDrawer::Release()
{
    if (!DXWindow::Release())
    {
        return false;
    }
    Common::Release(_vertexBuffer);
    Common::Release(_inputLayout);
    Common::Release(_vsCode);
    Common::Release(_psCode);
    Common::Release(_vs);
    Common::Release(_ps);
    Common::Release(_indexBuffer);

    Common::Release(_vertexBuffer1);
    Common::Release(_indexBuffer1);

    return true;
}

bool BoxDrawer::PreRender()
{
    if (!DXWindow::PreRender())
    {
        return false;
    }

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	GetDeviceContext()->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    GetDeviceContext()->IASetInputLayout(_inputLayout);
    GetDeviceContext()->VSSetShader(_vs, NULL, 0);
    GetDeviceContext()->PSSetShader(_ps, NULL, 0);
    //GetDeviceContext()->Draw(_vertexList.size(), 0);
	GetDeviceContext()->DrawIndexed(_indexList.size(), 0, 0);

    {
        GetDeviceContext()->IASetVertexBuffers(0, 1, &_vertexBuffer1, &stride, &offset);
        GetDeviceContext()->IASetIndexBuffer(_indexBuffer1, DXGI_FORMAT_R32_UINT, 0);
        GetDeviceContext()->IASetInputLayout(_inputLayout);
        GetDeviceContext()->VSSetShader(_vs, NULL, 0);
        GetDeviceContext()->PSSetShader(_ps, NULL, 0);
        GetDeviceContext()->DrawIndexed(_indexList.size(), 0, 0);
    }

    return true;
}

bool BoxDrawer::MainRender()
{
    if (!DXWindow::MainRender())
    {
        return false;
    }
    return true;
}

bool BoxDrawer::PostRender()
{
    if (!DXWindow::PostRender())
    {
        return false;
    }
    return true;
}
