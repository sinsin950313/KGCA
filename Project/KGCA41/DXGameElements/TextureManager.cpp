#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "DirectXTK.lib")

#include "TextureManager.h"
#include "Texture.h"
#include <d3d11.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "DXWindow.h"
#include "DXStateManager.h"

namespace SSB
{
    TextureManager* TextureManager::_instance = nullptr;
    extern DXWindow* g_dxWindow;

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        Release();

        delete _instance;
        _instance = nullptr;
    }

    TextureManager& TextureManager::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new TextureManager();
        }
        return *_instance;
    }

    Texture* TextureManager::Load(std::wstring fileName, std::string samplerName)
    {
        if (_textureData.find(fileName) == _textureData.end())
        {
            ID3D11Resource* textureResource = nullptr;
            ID3D11ShaderResourceView* textureResourceView = nullptr;
            auto path = GetPath(fileName);
            HRESULT hr = DirectX::CreateWICTextureFromFile(g_dxWindow->GetDevice(), g_dxWindow->GetDeviceContext(), path.c_str(), &textureResource, &textureResourceView);
            if (FAILED(hr))
            {
                hr = DirectX::CreateDDSTextureFromFile(g_dxWindow->GetDevice(), g_dxWindow->GetDeviceContext(), path.c_str(), &textureResource, &textureResourceView);
                if (FAILED(hr))
                {
                    return nullptr;
                }
            }

            Texture* texture = new Texture(textureResource, textureResourceView, DXStateManager::GetInstance().GetSamplerState(samplerName));
            _textureData.insert(make_pair(fileName, texture));
        }

        return _textureData.find(fileName)->second;
    }

    bool TextureManager::Init()
    {
        return true;
    }

    bool TextureManager::Frame()
    {
        return true;
    }

    bool TextureManager::Render()
    {
        return true;
    }

    bool TextureManager::Release()
    {
        for (auto iter : _textureData)
        {
            iter.second->Release();
            delete iter.second;
        }
        _textureData.clear();

        return true;
    }
}
