#pragma comment (lib, "d3d11.lib")

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

TTexture* TTextureManager::Load(std::wstring path)
{
    if (_textureData.find(path) == _textureData.end())
    {
        ID3D11Resource* textureResource = nullptr;
        ID3D11ShaderResourceView* textureResourceView = nullptr;
        HRESULT hr = DirectX::CreateWICTextureFromFile(g_dxWindow->GetDevice(), g_dxWindow->GetDeviceContext(), path.c_str(), &textureResource, &textureResourceView);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TTexture* texture = new TTexture(textureResource, textureResourceView);
        _textureData.insert(make_pair(path, texture));
    }

    return _textureData.find(path)->second;
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
        delete iter.second;
    }
    _textureData.clear();

    return true;
}
