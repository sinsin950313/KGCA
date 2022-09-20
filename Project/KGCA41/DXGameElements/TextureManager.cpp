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

    TextureResource* TextureResourceManager::Load(std::wstring resourceFileName)
    {
        if (_resourceData.find(resourceFileName) == _resourceData.end())
        {
            ID3D11Resource* textureResource = nullptr;
            ID3D11ShaderResourceView* textureResourceView = nullptr;
            auto path = GetPath(resourceFileName);
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
            _resourceData.insert(make_pair(resourceFileName, resource));
        }

        return _resourceData.find(resourceFileName)->second;
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

    void TextureLoader::RegisterTexturePartWithRelativeValue(std::wstring resourceFileName, std::wstring partName, TexturePartRelative part)
    {
        if (_textureDatas.find(resourceFileName) == _textureDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            TextureData data;
            data.resource = resource;
            _textureDatas.insert(std::make_pair(resourceFileName, data));
        }

        _textureDatas.find(resourceFileName)->second.textureParts.insert(std::make_pair(wtm(partName), part));
    }

    void TextureLoader::RegisterTexturePartWithCoordinateValue(std::wstring resourceFileName, std::wstring partName, TexturePartCoordinate part)
    {
        RegisterTexturePartWithRelativeValue(resourceFileName, partName, CtR(part));
    }

    void TextureLoader::RegisterTexturePartFromFile(std::wstring resourceFileName, std::wstring infoFileName)
    {
        // Need to update
    }

    Texture* TextureLoader::Load(std::wstring resourceFileName, std::wstring partName, std::string samplerName)
    {
        if (_textureDatas.find(resourceFileName) == _textureDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            TextureData data;
            data.resource = resource;
            _textureDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto textureParts = _textureDatas.find(resourceFileName)->second.textureParts;
        if (textureParts.find(wtm(partName)) == textureParts.end())
        {
            std::wstring textureInfoFile = SplitPath(resourceFileName)[2];
            RegisterTexturePartFromFile(resourceFileName, textureInfoFile);
        }

        auto iter = _textureDatas.find(resourceFileName);
        TextureResource* resource = iter->second.resource;
        TexturePartRelative relative = iter->second.textureParts.find(wtm(partName))->second;
        TexturePartCoordinate coord = RtC(relative);
        Texture* texture = new Texture(resource, coord, DXStateManager::GetInstance().GetSamplerState(samplerName));

        return texture;
    }

    //TexturePartRelative TextureLoader::GetTexturePart(std::wstring resourceFileName, std::wstring partName)
    //{
    //    if (_textureDatas.find(resourceFileName) == _textureDatas.end())
    //    {
    //        TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

    //        TextureData data;
    //        data.resource = resource;
    //        _textureDatas.insert(std::make_pair(resourceFileName, data));
    //    }

    //    auto textureParts = _textureDatas.find(resourceFileName)->second.textureParts;
    //    if (textureParts.find(wtm(partName)) == textureParts.end())
    //    {
    //        RegisterTexturePartFromFile(resourceFileName);
    //    }

    //    auto iter = _textureDatas.find(resourceFileName);
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

    SpriteLoader* SpriteLoader::_instance = nullptr;

    SpriteLoader& SpriteLoader::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new SpriteLoader();
        }
        return *_instance;
    }

    SpriteLoader::~SpriteLoader()
    {
        Release();

        if (_instance) delete _instance;
		_instance = nullptr;
    }

    void SpriteLoader::RegisterSpriteFromFile(std::wstring resourceFileName, std::wstring infoFileName)
    {
        // Need to update
    }

    void SpriteLoader::RegisterSpriteWithRelativeValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartRelative> sequenceRel)
    {
        if (_spriteDatas.find(resourceFileName) == _spriteDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteData data;
            data.resource = resource;
            _spriteDatas.insert(std::make_pair(resourceFileName, data));
        }

        _spriteDatas.find(resourceFileName)->second.sequenceDatas.insert(std::make_pair(wtm(actionName), sequenceRel));
    }

    void SpriteLoader::RegisterSpriteWithCoordinateValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartCoordinate> sequenceCoord)
    {
        std::vector<TexturePartRelative> sequenceRel;
        for (auto coor : sequenceCoord)
        {
            sequenceRel.push_back(CtR(coor));
        }
        RegisterSpriteWithRelativeValue(resourceFileName, actionName, sequenceRel);
    }

    Sprite* SpriteLoader::Load(std::wstring resourceFileName, std::wstring actionName, std::string samplerName)
    {
        if (_spriteDatas.find(resourceFileName) == _spriteDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteData data;
            data.resource = resource;
            _spriteDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto spriteData = _spriteDatas.find(resourceFileName)->second.sequenceDatas;
        if (spriteData.find(wtm(actionName)) == spriteData.end())
        {
            std::wstring spriteInfoFile = SplitPath(resourceFileName)[2];
            RegisterSpriteFromFile(resourceFileName, spriteInfoFile);
        }

        auto iter = _spriteDatas.find(resourceFileName);
        TextureResource* resource = iter->second.resource;
        std::vector<TexturePartRelative> relative = iter->second.sequenceDatas.find(wtm(actionName))->second;
        std::vector<TexturePartCoordinate> sequenceCoord;
        for (auto rel : relative)
        {
            sequenceCoord.push_back(RtC(rel));
        }
        Sprite* sprite = new Sprite(resource, sequenceCoord, DXStateManager::GetInstance().GetSamplerState(samplerName));

        return sprite;
    }

    void SpriteLoader::ParseSpriteData(std::wstring infoFileName)
    {
        //TCHAR pBuffer[256] = { 0 };
        //TCHAR pTemp[256] = { 0 };

        //int iNumSprite = 0;
        //FILE* fp_src;
        //_wfopen_s(&fp_src, pszLoad, _T("rt"));
        //if (fp_src == NULL) return false;

        //_fgetts(pBuffer, _countof(pBuffer), fp_src);
        //_stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
        //m_rtSpriteList.resize(iNumSprite);

        //for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
        //{
        //    int iNumFrame = 0;
        //    _fgetts(pBuffer, _countof(pBuffer), fp_src);
        //    _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
        //    //m_rtSpriteList[iCnt].resize(iNumFrame);

        //    RECT rt;
        //    for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
        //    {
        //        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        //        _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
        //            &rt.left, &rt.top, &rt.right, &rt.bottom);
        //        m_rtSpriteList[iCnt].push_back(rt);
        //    }
        //}
        //fclose(fp_src);
        //return true;
    }
    bool SpriteLoader::Init()
    {
        return true;
    }
    bool SpriteLoader::Frame()
    {
        return true;
    }
    bool SpriteLoader::Render()
    {
        return true;
    }
    bool SpriteLoader::Release()
    {
        _spriteDatas.clear();
        return true;
    }
}
