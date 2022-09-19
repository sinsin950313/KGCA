#include "Texture.h"

namespace SSB
{
    Texture::Texture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState)
        : _textureResource(textureResource), _textureResourceView(textureResourceView), _samplerState(samplerState)
    {
        static_cast<ID3D11Texture2D*>(_textureResource)->GetDesc(&_desc);
        _dTile = { 1, 1 };
    }

    void Texture::SetSamplerState(ID3D11SamplerState* samplerState)
    {
        _samplerState = samplerState;
    }

    bool Texture::Init()
    {
        return true;
    }

    bool Texture::Frame()
    {
        return true;
    }

    bool Texture::Render()
    {
        return true;
    }

    bool Texture::Release()
    {
        if (_textureResource) _textureResource->Release();
        if (_textureResourceView)_textureResourceView->Release();

        _textureResource = nullptr;
        _textureResourceView = nullptr;
        _samplerState = nullptr;

        return true;
    }

    void Texture::RegisterTexturePartWithRelativeValue(std::string actionName, RECT size)
    {
        RECT tmp;
        tmp.left = size.left;
        tmp.top = size.top;
        tmp.right = size.right + size.left;
        tmp.bottom = size.bottom + size.top;

        _textureParts.insert(std::make_pair(actionName, tmp));
    }

    void Texture::RegisterTexturePartWithCoordinateValue(std::string actionName, RECT size)
    {
        _textureParts.insert(std::make_pair(actionName, size));
    }

    TexturePart Texture::GetCurrentTexturePart()
    {
        TexturePart ret;
        ret.left = (((float)_currentTexturePart.left / _desc.Width) + _dTexture.u) * _dTile.u;
        ret.top = (((float)_currentTexturePart.top / _desc.Height) + _dTexture.v) * _dTile.v;
        ret.right = (((float)_currentTexturePart.right / _desc.Width) + _dTexture.u) * _dTile.u;
        ret.bottom = (((float)_currentTexturePart.bottom / _desc.Height) + _dTexture.v) * _dTile.v;

        return ret;
    }

    void Texture::Scroll(float xRatio, float yRatio)
    {
        _dTexture.u = xRatio;
        _dTexture.v = yRatio;
    }

    void Texture::Tile(float xCoefficient, float yCoefficient)
    {
        _dTile.u = xCoefficient;
        _dTile.v = yCoefficient;
    }
}
