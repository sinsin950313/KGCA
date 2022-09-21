#pragma once

#include <d3d11.h>
#include "Common.h"
#include <map>
#include <string>
#include "Timer.h"
#include <vector>

namespace SSB
{
	class TextureResource : public Common
	{
	private:
		ID3D11Resource* _textureResource;
		D3D11_TEXTURE2D_DESC _desc;
		ID3D11ShaderResourceView* _textureResourceView;

	public:
		TextureResource(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView);

	public:
		ID3D11Resource* GetResource() const { return _textureResource; }
		ID3D11ShaderResourceView** GetShaderResourceView() { return &_textureResourceView; }
		UINT GetWidth() { return _desc.Width; }
		UINT GetHeight() { return _desc.Height; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	struct TexturePartCoordinate
	{
		UINT left;
		UINT top;
		UINT right;
		UINT bottom;
	};

	struct TexturePartCoordinateRatio
	{
		float left;
		float top;
		float right;
		float bottom;
	};

	struct TexturePartRelative
	{
		UINT left;
		UINT top;
		UINT width;
		UINT height;
	};

	TexturePartCoordinate RtC(TexturePartRelative rel);
	TexturePartRelative CtR(TexturePartCoordinate coord);

	struct TextureParam
	{
		float u;
		float v;
	};

	class Sprite : public Common
	{
	private:
		TextureResource* _resource;
		TextureResource* _maskResource = nullptr;
		ID3D11SamplerState* _samplerState;
		TexturePartCoordinate _currentTexturePart;
		TextureParam _dTexture;
		TextureParam _dTile;

	public:
		Sprite(TextureResource* resource, TextureResource* maskResource = nullptr);

	public:
		TextureResource* GetResource() { return _resource; }
		TextureResource* GetMaskResource() { return _maskResource; }
		void SetSamplerState(ID3D11SamplerState* samplerState);
		ID3D11SamplerState* GetSamplerState() { return _samplerState; }
		TexturePartCoordinateRatio GetCurrentTexturePart();
		void SetCurrentSprite(TexturePartCoordinate part) { _currentTexturePart = part; }
		void SetCurrentSprite(TexturePartRelative part);
		void Scroll(float xRatio, float yRatio);
		void Tile(float xCoefficient, float yCoefficient);
		bool HasMaskResource() { return _maskResource != nullptr; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class SpriteAction : public Sprite
	{
	private:
		std::vector<TexturePartCoordinate> _actionSequence;
		bool _finished = false;
		bool _loop;
		Timer _timer;
		float _interval;
		int _currentActionIndex;
		float _lastTime;

	public:
		SpriteAction(TextureResource* resource, TextureResource* maskResource = nullptr);

	public:
		void SetLoop(bool loop) { _loop = loop; }
		void SetInterval(float interval) { _interval = interval; }
		bool IsFinished() { return _finished; }
		void SetSpriteAction(std::vector<TexturePartCoordinate> actionSequence);
		void SetSpriteAction(std::vector<TexturePartRelative> actionSequence);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
