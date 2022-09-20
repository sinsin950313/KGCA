#include "Texture.h"

namespace SSB
{
    TextureResource::TextureResource(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView)
        : _textureResource(textureResource), _textureResourceView(textureResourceView)
    {
        static_cast<ID3D11Texture2D*>(_textureResource)->GetDesc(&_desc);
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

        return true;
    }

    Texture::Texture(TextureResource* resource, TexturePartCoordinate texturePart, ID3D11SamplerState* samplerState) 
        : _resource(resource), _currentTexturePart(texturePart), _samplerState(samplerState)
    {
        _dTile = { 1, 1 };
        _dTexture = { 0, 0 };
    }

    void Texture::SetSamplerState(ID3D11SamplerState* samplerState)
    {
        _samplerState = samplerState;
    }

    TexturePartCoordinate Texture::GetCurrentTexturePart()
    {
        TexturePartCoordinate ret;
        ret.left = (((float)_currentTexturePart.left / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.top = (((float)_currentTexturePart.top / _resource->GetHeight()) + _dTexture.v) * _dTile.v;
        ret.right = (((float)_currentTexturePart.right / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.bottom = (((float)_currentTexturePart.bottom / _resource->GetHeight()) + _dTexture.v) * _dTile.v;

        return ret;
    }

    void Texture::SetCurrentTexturePart(TexturePartRelative part)
    {
        SetCurrentTexturePart(RtC(part));
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
        _samplerState = nullptr;
        return false;
    }

    TexturePartCoordinate RtC(TexturePartRelative rel)
	{
		TexturePartCoordinate coord;
		coord.left = rel.left;
		coord.top = rel.top;
		coord.right = rel.left + rel.width;
		coord.bottom = rel.top + rel.height;
		return coord;
	}

    TexturePartRelative CtR(TexturePartCoordinate coord)
	{
		TexturePartRelative rel;
		rel.left = coord.left;
		rel.top = coord.top;
		rel.width = coord.right - coord.left;
		rel.height = coord.bottom - coord.top;
		return rel;
	}

    //	bool SSB::Sprite::Init()
//	{
//		_timer.Init();
//		_timer.Start();
//		_lastTime = _timer.GetElapseTime();
//
//		return true;
//	}
//
//	bool SSB::Sprite::Frame()
//	{
//		if (_interval <= _timer.GetElapseTime() - _lastTime)
//		{
//			++_currentActionIndex;
//			if (_currentActionIndex == _actionSequence.size())
//			{
//				_currentActionIndex = 0;
//			}
//		}
//		_lastTime = _timer.GetElapseTime();
//
//		return true;
//	}
//
//	bool SSB::Sprite::Render()
//	{
//		return true;
//	}
//
//	bool SSB::Sprite::Release()
//	{
//		_texture = nullptr;
//		return true;
//	}
}
