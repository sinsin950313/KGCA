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

    void SpriteLoader::RegisterSpriteWithRelativeValue(std::wstring resourceFileName, std::wstring spriteName, TexturePartRelative part)
    {
        if (_spriteDatas.find(resourceFileName) == _spriteDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteData data;
            data.resource = resource;
            _spriteDatas.insert(std::make_pair(resourceFileName, data));
        }

        _spriteDatas.find(resourceFileName)->second.textureParts.insert(std::make_pair(wtm(spriteName), part));
    }

    void SpriteLoader::RegisterSpriteWithCoordinateValue(std::wstring resourceFileName, std::wstring spriteName, TexturePartCoordinate part)
    {
        RegisterSpriteWithRelativeValue(resourceFileName, spriteName, CtR(part));
    }

    void SpriteLoader::RegisterSpriteFromFile(std::wstring resourceFileName, std::wstring infoFileName)
    {
        TCHAR pBuffer[256] = { 0 };
        TCHAR pTemp[256] = { 0 };

        int iNumSprite = 0;
        FILE* fp_src;
        _wfopen_s(&fp_src, GetPath(infoFileName).c_str(), _T("rt"));
        if (fp_src == NULL) return;

        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
        auto spriteData = _spriteDatas.find(resourceFileName);

        for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
        {
            int iNumFrame = 0;
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            TexturePartRelative texturePart;
            _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
				&texturePart.left, &texturePart.top, &texturePart.width, &texturePart.height);
			spriteData->second.textureParts.insert(std::make_pair(wtm(pTemp), texturePart));
        }
        fclose(fp_src);
    }

    Sprite* SpriteLoader::Load(std::wstring resourceFileName, std::wstring spriteName, std::string samplerName)
    {
        if (_spriteDatas.find(resourceFileName) == _spriteDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteData data;
            data.resource = resource;
            _spriteDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto textureParts = _spriteDatas.find(resourceFileName)->second.textureParts;
        if (textureParts.find(wtm(spriteName)) == textureParts.end())
        {
            std::wstring textureInfoFile = SplitPath(resourceFileName)[2];
            RegisterSpriteFromFile(resourceFileName, textureInfoFile);
        }

        auto iter = _spriteDatas.find(resourceFileName);
        TextureResource* resource = iter->second.resource;
        TexturePartRelative relative = iter->second.textureParts.find(wtm(spriteName))->second;
        TexturePartCoordinate coord = RtC(relative);
        Sprite* sprite = new Sprite(resource, coord, DXStateManager::GetInstance().GetSamplerState(samplerName));

        return sprite;
    }

    TexturePartRelative SpriteLoader::GetTexturePart(std::wstring resourceFileName, std::wstring spriteName)
    {
        if (_spriteDatas.find(resourceFileName) == _spriteDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteData data;
            data.resource = resource;
            _spriteDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto textureParts = _spriteDatas.find(resourceFileName)->second.textureParts;
        if (textureParts.find(wtm(spriteName)) == textureParts.end())
        {
            RegisterSpriteFromFile(resourceFileName, resourceFileName);
        }

        auto iter = _spriteDatas.find(resourceFileName);
        return iter->second.textureParts.find(wtm(spriteName))->second;
    }

    bool SpriteLoader::Init()
    {
        return false;
    }

    bool SpriteLoader::Frame()
    {
        return false;
    }

    bool SpriteLoader::Render()
    {
        return false;
    }

    bool SpriteLoader::Release()
    {
        _spriteDatas.clear();
        return false;
    }

    SpriteActionLoader* SpriteActionLoader::_instance = nullptr;

    SpriteActionLoader& SpriteActionLoader::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new SpriteActionLoader();
        }
        return *_instance;
    }

    SpriteActionLoader::~SpriteActionLoader()
    {
        Release();

        if (_instance) delete _instance;
		_instance = nullptr;
    }

    void SpriteActionLoader::RegisterSpriteActionFromFile(std::wstring resourceFileName, std::wstring infoFileName)
    {
        TCHAR pBuffer[256] = { 0 };
        TCHAR pTemp[256] = { 0 };

        int iNumSprite = 0;
        FILE* fp_src;
        _wfopen_s(&fp_src, GetPath(infoFileName).c_str(), _T("rt"));
        if (fp_src == NULL) return;

        _fgetts(pBuffer, _countof(pBuffer), fp_src);
        _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
        auto spriteData = _spriteActionDatas.find(resourceFileName);

        for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
        {
            int iNumFrame = 0;
            _fgetts(pBuffer, _countof(pBuffer), fp_src);
            _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);

            std::vector<TexturePartRelative> sequence;
            for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
            {
				TexturePartRelative texturePart;
                _fgetts(pBuffer, _countof(pBuffer), fp_src);
                _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
                    &texturePart.left, &texturePart.top, &texturePart.width, &texturePart.height);
                sequence.push_back(texturePart);
            }
			spriteData->second.sequenceDatas.insert(std::make_pair(wtm(pTemp), sequence));
        }
        fclose(fp_src);
    }

    void SpriteActionLoader::RegisterSpriteActionWithRelativeValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartRelative> sequenceRel)
    {
        if (_spriteActionDatas.find(resourceFileName) == _spriteActionDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteActionData data;
            data.resource = resource;
            _spriteActionDatas.insert(std::make_pair(resourceFileName, data));
        }

        _spriteActionDatas.find(resourceFileName)->second.sequenceDatas.insert(std::make_pair(wtm(actionName), sequenceRel));
    }

    void SpriteActionLoader::RegisterSpriteActionWithCoordinateValue(std::wstring resourceFileName, std::wstring actionName, std::vector<TexturePartCoordinate> sequenceCoord)
    {
        std::vector<TexturePartRelative> sequenceRel;
        for (auto coor : sequenceCoord)
        {
            sequenceRel.push_back(CtR(coor));
        }
        RegisterSpriteActionWithRelativeValue(resourceFileName, actionName, sequenceRel);
    }

    SpriteAction* SpriteActionLoader::Load(std::wstring resourceFileName, std::wstring actionName, std::string samplerName)
    {
        if (_spriteActionDatas.find(resourceFileName) == _spriteActionDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteActionData data;
            data.resource = resource;
            _spriteActionDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto spriteData = _spriteActionDatas.find(resourceFileName)->second.sequenceDatas;
        if (spriteData.find(wtm(actionName)) == spriteData.end())
        {
            std::wstring spriteInfoFile = SplitPath(resourceFileName)[2];
            RegisterSpriteActionFromFile(resourceFileName, spriteInfoFile);
        }

        auto iter = _spriteActionDatas.find(resourceFileName);
        TextureResource* resource = iter->second.resource;
        std::vector<TexturePartRelative> relative = iter->second.sequenceDatas.find(wtm(actionName))->second;
        std::vector<TexturePartCoordinate> sequenceCoord;
        for (auto rel : relative)
        {
            sequenceCoord.push_back(RtC(rel));
        }
        SpriteAction* spriteAction = new SpriteAction(resource, sequenceCoord, DXStateManager::GetInstance().GetSamplerState(samplerName));

        return spriteAction;
    }

    std::vector<TexturePartRelative> SpriteActionLoader::GetSpriteAction(std::wstring resourceFileName, std::wstring actionName)
    {
        if (_spriteActionDatas.find(resourceFileName) == _spriteActionDatas.end())
        {
            TextureResource* resource = TextureResourceManager::GetInstance().Load(resourceFileName);

            SpriteActionData data;
            data.resource = resource;
            _spriteActionDatas.insert(std::make_pair(resourceFileName, data));
        }

        auto actionData = _spriteActionDatas.find(resourceFileName)->second.sequenceDatas;
        if (actionData.find(wtm(actionName)) == actionData.end())
        {
            RegisterSpriteActionFromFile(resourceFileName, resourceFileName);
        }

        auto actionSequence = actionData.find(wtm(actionName));
        std::vector<TexturePartRelative> ret;
        for (auto action : actionSequence->second)
        {
            ret.push_back(action);
        }
        return ret;
    }

    bool SpriteActionLoader::Init()
    {
        return true;
    }

    bool SpriteActionLoader::Frame()
    {
        return true;
    }

    bool SpriteActionLoader::Render()
    {
        return true;
    }

    bool SpriteActionLoader::Release()
    {
        _spriteActionDatas.clear();
        return true;
    }
}
