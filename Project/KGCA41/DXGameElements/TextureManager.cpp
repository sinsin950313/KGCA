#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "DirectXTK.lib")

#include "TextureManager.h"
#include "Texture.h"
#include <d3d11.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "DXWindow.h"
#include "DXStateManager.h"
#include "CommonUtility.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

    TextureResourceManager* TextureResourceManager::_instance = nullptr;

    TextureResourceManager::~TextureResourceManager()
    {
        Release();

        if (_instance) delete _instance;
        _instance = nullptr;
    }

    TextureResourceManager& TextureResourceManager::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new TextureResourceManager();
        }
        return *_instance;
    }

    TextureResource* TextureResourceManager::Load(std::wstring fileName)
    {
        if (_resourceData.find(fileName) == _resourceData.end())
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

            TextureResource* resource = new TextureResource(textureResource, textureResourceView);
            resource->Init();
            _resourceData.insert(make_pair(fileName, resource));
        }

        return _resourceData.find(fileName)->second;
    }

    bool TextureResourceManager::Init()
    {
        return true;
    }

    bool TextureResourceManager::Frame()
    {
        return true;
    }

    bool TextureResourceManager::Render()
    {
        return true;
    }

    bool TextureResourceManager::Release()
    {
        for (auto iter : _resourceData)
        {
            iter.second->Release();
            delete iter.second;
        }
        _resourceData.clear();

        return true;
    }

    TextureLoader* TextureLoader::_instance = nullptr;

    TextureLoader& TextureLoader::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new TextureLoader();
        }
        return *_instance;
    }

    TextureLoader::~TextureLoader()
    {
        Release();

        if (_instance) delete _instance;
        _instance = nullptr;
    }

    void TextureLoader::RegisterTexturePartWithRelativeValue(std::wstring fileName, std::wstring partName, TexturePartRelative part)
    {
        if (_textureDatas.find(fileName) == _textureDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(fileName);

            TextureData data;
            data.resource = resource;
            _textureDatas.insert(std::make_pair(fileName, data));
        }

        _textureDatas.find(fileName)->second.textureParts.insert(std::make_pair(wtm(partName), part));
    }

    void TextureLoader::RegisterTexturePartWithCoordinateValue(std::wstring fileName, std::wstring partName, TexturePartCoordinate part)
    {
        RegisterTexturePartWithRelativeValue(fileName, partName, CtR(part));
    }

    void TextureLoader::RegisterTexturePartFromFile(std::wstring infoFileName)
    {
        // Need to update
    }

    Texture* TextureLoader::Load(std::wstring fileName, std::wstring partName, std::string samplerName)
    {
        if (_textureDatas.find(fileName) == _textureDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(fileName);

            TextureData data;
            data.resource = resource;
            _textureDatas.insert(std::make_pair(fileName, data));
        }

        auto textureParts = _textureDatas.find(fileName)->second.textureParts;
        if (textureParts.find(wtm(partName)) == textureParts.end())
        {
            RegisterTexturePartFromFile(fileName);
        }

        auto iter = _textureDatas.find(fileName);
        TextureResource* resource = iter->second.resource;
        TexturePartRelative relative = iter->second.textureParts.find(wtm(partName))->second;
        TexturePartCoordinate coord = RtC(relative);
        Texture* texture = new Texture(resource, coord, DXStateManager::GetInstance().GetSamplerState(samplerName));

        return texture;
    }

    //TexturePartRelative TextureLoader::GetTexturePart(std::wstring fileName, std::wstring partName)
    //{
    //    if (_textureDatas.find(fileName) == _textureDatas.end())
    //    {
    //        TextureResource* resource = TextureResourceManager::GetInstance().Load(fileName);

    //        TextureData data;
    //        data.resource = resource;
    //        _textureDatas.insert(std::make_pair(fileName, data));
    //    }

    //    auto textureParts = _textureDatas.find(fileName)->second.textureParts;
    //    if (textureParts.find(wtm(partName)) == textureParts.end())
    //    {
    //        RegisterTexturePartFromFile(fileName);
    //    }

    //    auto iter = _textureDatas.find(fileName);
    //    return iter->second.textureParts.find(wtm(partName))->second;
    //}

    bool TextureLoader::Init()
    {
        return false;
    }

    bool TextureLoader::Frame()
    {
        return false;
    }

    bool TextureLoader::Render()
    {
        return false;
    }

    bool TextureLoader::Release()
    {
        _textureDatas.clear();
        return false;
    }

    //SpriteLoader& SpriteLoader::GetInstance()
    //{
    //    if (_instance == nullptr)
    //    {
    //        _instance = new SpriteLoader();
    //    }
    //    return *_instance;
    //}

    //SpriteLoader::~SpriteLoader()
    //{
    //}

    //Sprite* SpriteLoader::Load(Texture* resource, std::string samplerName, std::wstring infoFileName, std::string actionName)
    //{
    //    return nullptr;
    //}

    //Sprite* SpriteLoader::Load(Texture* resource, std::wstring fileName, std::string actionName)
    //{
    //    return nullptr;
    //}

    //std::wstring SpriteLoader::GetActionName(Texture* resource, std::string actionName)
    //{
    //    return std::wstring();
    //}

    //void SpriteLoader::ParseSpriteData(std::wstring infoFileName)
    //{
    //    TCHAR pBuffer[256] = { 0 };
    //    TCHAR pTemp[256] = { 0 };

    //    int iNumSprite = 0;
    //    FILE* fp_src;
    //    _wfopen_s(&fp_src, pszLoad, _T("rt"));
    //    if (fp_src == NULL) return false;

    //    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    //    _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
    //    m_rtSpriteList.resize(iNumSprite);

    //    for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
    //    {
    //        int iNumFrame = 0;
    //        _fgetts(pBuffer, _countof(pBuffer), fp_src);
    //        _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
    //        //m_rtSpriteList[iCnt].resize(iNumFrame);

    //        RECT rt;
    //        for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
    //        {
    //            _fgetts(pBuffer, _countof(pBuffer), fp_src);
    //            _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
    //                &rt.left, &rt.top, &rt.right, &rt.bottom);
    //            m_rtSpriteList[iCnt].push_back(rt);
    //        }
    //    }
    //    fclose(fp_src);
    //    return true;
    //}
    //bool SpriteLoader::Init()
    //{
    //    return false;
    //}
    //bool SpriteLoader::Frame()
    //{
    //    return false;
    //}
    //bool SpriteLoader::Render()
    //{
    //    return false;
    //}
    //bool SpriteLoader::Release()
    //{
    //    return false;
    //}
}
