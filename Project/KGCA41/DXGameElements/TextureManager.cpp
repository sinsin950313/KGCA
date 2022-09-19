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

    void SpriteLoader::ParseSpriteData(std::wstring fileName)
    {
        TCHAR pBuffer[256] = { 0 };
        TCHAR pTemp[256] = { 0 };

        int iNumSprite = 0;
        FILE* fp_src;
        _wfopen_s(&fp_src, pszLoad, _T("rt"));
        if (fp_src == NULL) return false;

        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
        m_rtSpriteList.resize(iNumSprite);

        for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
        {
            int iNumFrame = 0;
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
            //m_rtSpriteList[iCnt].resize(iNumFrame);

            RECT rt;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                    &rt.left, &rt.top, &rt.right, &rt.bottom);
                m_rtSpriteList[iCnt].push_back(rt);
            }
        }
        fclose(fp_src);
        return true;
    }
}
