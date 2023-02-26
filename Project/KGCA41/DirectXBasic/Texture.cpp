#include "Texture.h"
#pragma comment (lib, "WindowUtility.lib")

namespace SSB
{
    TextureResource::TextureResource(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView)
        : _textureResource(textureResource), _textureResourceView(textureResourceView)
    {
        if (_textureResource != nullptr)
        {
            static_cast<ID3D11Texture2D*>(_textureResource)->GetDesc(&_desc);
        }
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
        if (_textureResource)
        {
            _textureResource->Release();
			_textureResource = nullptr;
        }

        if (_textureResourceView)
        {
            _textureResourceView->Release();
            _textureResourceView = nullptr;
        }

        return true;
    }

    Sprite::Sprite(TextureResource* resource, TextureResource* maskResource) 
        : _resource(resource), _maskResource(maskResource)
    {
        _dTile = { 1, 1 };
        _dTexture = { 0, 0 };
    }

    void Sprite::SetSamplerState(ID3D11SamplerState* samplerState)
    {
        _samplerState = samplerState;
    }

    TexturePartCoordinateRatio Sprite::GetCurrentTexturePart()
    {
        TexturePartCoordinateRatio ret;
        ret.left = (((float)_currentTexturePart.left / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.top = (((float)_currentTexturePart.top / _resource->GetHeight()) + _dTexture.v) * _dTile.v;
        ret.right = (((float)_currentTexturePart.right / _resource->GetWidth()) + _dTexture.u) * _dTile.u;
        ret.bottom = (((float)_currentTexturePart.bottom / _resource->GetHeight()) + _dTexture.v) * _dTile.v;

        return ret;
    }

    void Sprite::SetCurrentSprite(TexturePartRelative part)
    {
        SetCurrentSprite(RtC(part));
    }

    void Sprite::Scroll(float xRatio, float yRatio)
    {
        _dTexture.u = xRatio;
        _dTexture.v = yRatio;
    }

    void Sprite::Tile(float xCoefficient, float yCoefficient)
    {
        _dTile.u = xCoefficient;
        _dTile.v = yCoefficient;
    }
    bool Sprite::Init()
    {
        return true;
    }

    bool Sprite::Frame()
    {
        return true;
    }

    bool Sprite::Render()
    {
        return true;
    }

    bool Sprite::Release()
    {
        _resource = nullptr;
        _maskResource = nullptr;
        _samplerState = nullptr;

        return true;
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

    SpriteAction::SpriteAction(TextureResource* resource, TextureResource* maskResource) 
        : Sprite(resource, maskResource)
    {
        _loop = false;
        _interval = 1.0f;
    }

    void SpriteAction::SetSpriteAction(std::vector<TexturePartCoordinate> actionSequence)
    {
        _actionSequence = actionSequence;
    }

    void SpriteAction::SetSpriteAction(std::vector<TexturePartRelative> actionSequence)
    {
        _actionSequence.clear();
        for (auto action : actionSequence)
        {
            _actionSequence.push_back(RtC(action));
        }
    }

    bool SSB::SpriteAction::Init()
	{
		_currentActionIndex = 0;

		_timer.Init();
		_timer.Start();
		_lastTime = _timer.GetElapseTime();

		return true;
	}

	bool SSB::SpriteAction::Frame()
	{
        if (!_finished)
        {
            _timer.Frame();

            if (_interval <= _timer.GetElapseTime() - _lastTime)
            {
                if (_currentActionIndex < _actionSequence.size() - 1)
                {
					++_currentActionIndex;
                }
                else
				{
                    if (_loop)
                    {
                        ResetAction();
                    }
                    else
                    {
                        _finished = true;
                    }
                }
                _lastTime = _timer.GetElapseTime();
            }
            Sprite::SetCurrentSprite(_actionSequence[_currentActionIndex]);
        }

		return true;
	}

	bool SSB::SpriteAction::Render()
	{
		return true;
	}

	bool SSB::SpriteAction::Release()
	{
        _actionSequence.clear();
        Sprite::Release();
		return true;
	}
    Texture::Texture(TextureResource* resource, ID3D11SamplerState* samplerState) : _resource(resource), _samplerState(samplerState)
    {
    }
    Texture::~Texture()
    {
        Release();
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
        _resource = nullptr;
        _samplerState = nullptr;
        return true;
    }
}
