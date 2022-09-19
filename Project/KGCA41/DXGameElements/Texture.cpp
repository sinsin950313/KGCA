#include "Texture.h"

namespace SSB
{
    TextureResource::TextureResource(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState)
        : _textureResource(textureResource), _textureResourceView(textureResourceView), _samplerState(samplerState)
    {
        static_cast<ID3D11Texture2D*>(_textureResource)->GetDesc(&_desc);
    }

    void TextureResource::SetSamplerState(ID3D11SamplerState* samplerState)
    {
        _samplerState = samplerState;
    }

    bool TextureResource::Init()
    {
        return true;
    }

    bool TextureResource::Frame()
    {
        return true;
    }

    bool TextureResource::Render()
    {
        return true;
    }

    bool TextureResource::Release()
    {
        if (_textureResource) _textureResource->Release();
        if (_textureResourceView)_textureResourceView->Release();

        _textureResource = nullptr;
        _textureResourceView = nullptr;
        _samplerState = nullptr;

        return true;
    }

    void TextureResource::RegisterTexturePartWithRelativeValue(std::string actionName, RECT size)
    {
        RECT tmp;
        tmp.left = size.left;
        tmp.top = size.top;
        tmp.right = size.right + size.left;
        tmp.bottom = size.bottom + size.top;

        _textureParts.insert(std::make_pair(actionName, tmp));
    }

    void TextureResource::RegisterTexturePartWithCoordinateValue(std::string actionName, RECT size)
    {
        _textureParts.insert(std::make_pair(actionName, size));
    }

    Texture::Texture(TextureResource* resource) : _resource(resource)
    {
        _dTile = { 1, 1 };
    }

    TexturePart Texture::GetCurrentTexturePart()
    {
        TexturePart ret;
        ret.left = (((float)_currentTexturePart.left / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.top = (((float)_currentTexturePart.top / _resource->GetHeight()) + _dTexture.v) * _dTile.v;
        ret.right = (((float)_currentTexturePart.right / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.bottom = (((float)_currentTexturePart.bottom / _resource->GetHeight()) + _dTexture.v) * _dTile.v;

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
    bool Texture::Init()
    {
        return false;
    }
    bool Texture::Frame()
    {
        return false;
    }
    bool Texture::Render()
    {
        return false;
    }
    bool Texture::Release()
    {
        return false;
    }

	bool SSB::Sprite::Init()
	{
		_timer.Init();
		_timer.Start();
		_lastTime = _timer.GetElapseTime();

		return true;
	}

	bool SSB::Sprite::Frame()
	{
		if (_interval <= _timer.GetElapseTime() - _lastTime)
		{
			++_currentActionIndex;
			if (_currentActionIndex == _actionSequence.size())
			{
				_currentActionIndex = 0;
			}
		}
		_lastTime = _timer.GetElapseTime();

		return true;
	}

	bool SSB::Sprite::Render()
	{
		return true;
	}

	bool SSB::Sprite::Release()
	{
		_texture = nullptr;
		return true;
	}
}
