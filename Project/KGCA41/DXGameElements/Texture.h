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
		float left;
		float top;
		float right;
		float bottom;
	};

	struct TexturePartRelative
	{
		float left;
		float top;
		float width;
		float height;
	};

	TexturePartCoordinate RtC(TexturePartRelative rel);
	TexturePartRelative CtR(TexturePartCoordinate coord);

	struct TextureParam
	{
		float u;
		float v;
	};

	class Texture : public Common
	{
	private:
		TextureResource* _resource;
		ID3D11SamplerState* _samplerState;
		TexturePartCoordinate _currentTexturePart;
		TextureParam _dTexture;
		TextureParam _dTile;

	public:
		Texture(TextureResource* resource, TexturePartCoordinate texturePart, ID3D11SamplerState* samplerState);

	public:
		TextureResource* GetResource() { return _resource; }
		void SetSamplerState(ID3D11SamplerState* samplerState);
		ID3D11SamplerState* GetSamplerState() { return _samplerState; }
		TexturePartCoordinate GetCurrentTexturePart();
		void SetCurrentTexturePart(TexturePartCoordinate part) { _currentTexturePart = part; }
		void SetCurrentTexturePart(TexturePartRelative part);
		void Scroll(float xRatio, float yRatio);
		void Tile(float xCoefficient, float yCoefficient);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class Sprite : public Texture
	{
	private:
		std::vector<TexturePartCoordinate> _actionSequence;
		bool _loop;
		Timer _timer;
		float _interval;
		int _currentActionIndex;
		float _lastTime;

	public:
		Sprite(TextureResource* resource, std::vector<TexturePartCoordinate> actionSequence, ID3D11SamplerState* samplerState);

	public:
		void SetLoop(bool loop) { _loop = loop; }
		void SetInterval(float interval) { _interval = interval; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
