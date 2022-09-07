#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "DirectXTK.lib")

#include "TTextureManager.h"
#include "TTexture.h"
#include <d3d11.h>
#include "WICTextureLoader.h"
#include "TDXWindow.h"

TTextureManager* TTextureManager::_instance = nullptr;
extern TDXWindow* g_dxWindow;

TTextureManager::TTextureManager()
{
}

TTextureManager::~TTextureManager()
{
    Release();

    delete _instance;
}

TTextureManager& TTextureManager::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new TTextureManager();
    }
    return *_instance;
}

TTexture* TTextureManager::Load(std::wstring fileName)
{
    if (_textureData.find(fileName) == _textureData.end())
    {
        ID3D11Resource* textureResource = nullptr;
        ID3D11ShaderResourceView* textureResourceView = nullptr;
        auto path = GetPath(fileName);
        HRESULT hr = DirectX::CreateWICTextureFromFile(g_dxWindow->GetDevice(), g_dxWindow->GetDeviceContext(), path.c_str(), &textureResource, &textureResourceView);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TTexture* texture = new TTexture(textureResource, textureResourceView, LoadSampler(L"Default"));
        _textureData.insert(make_pair(fileName, texture));
    }

    return _textureData.find(fileName)->second;
}

TTexture* TTextureManager::Load(std::wstring fileName, std::wstring alphaFileName)
{
    TTexture* texture = Load(fileName);

    return _textureData.find(fileName)->second;
}

ID3D11SamplerState* TTextureManager::LoadSampler(std::wstring stateName)
{
    if (_samplerData.find(stateName) == _samplerData.end())
    {
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		ID3D11SamplerState* samplerState;
		g_dxWindow->GetDevice()->CreateSamplerState(&samplerDesc, &samplerState);

        _samplerData.insert(std::make_pair(stateName, samplerState));
    }
    return _samplerData.find(stateName)->second;
}

bool TTextureManager::Init()
{
    return true;
}

bool TTextureManager::Frame()
{
    return true;
}

bool TTextureManager::Render()
{
    return true;
}

bool TTextureManager::Release()
{
    for (auto iter : _textureData)
    {
        iter.second->Release();
        delete iter.second;
    }
    _textureData.clear();

    for (auto iter : _samplerData)
    {
        iter.second->Release();
    }
    _samplerData.clear();


    return true;
}
