#pragma once

#include <d3d11.h>
#include "Common.h"
#include <map>
#include <string>

namespace SSB
{
	class TextureResource : public Common
	{
	private:
		ID3D11Resource* _textureResource;
		D3D11_TEXTURE2D_DESC _desc;
		ID3D11ShaderResourceView* _textureResourceView;
		std::map<std::string, RECT> _textureParts;

	public:
		TextureResource(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView);

	public:
		void SetSamplerState(ID3D11SamplerState* samplerState);
		ID3D11Resource* GetResource() const { return _textureResource; }
		ID3D11ShaderResourceView** GetShaderResourceView() { return &_textureResourceView; }
		ID3D11SamplerState* GetSamplerState() { return _samplerState; }
		// left, top, width, height
		void RegisterTexturePartWithRelativeValue(std::string actionName, RECT size);
		/// left, top, right, bottom
		void RegisterTexturePartWithCoordinateValue(std::string actionName, RECT size);
		RECT GetTexturePart(std::string partName) { return _textureParts.find(partName)->second; }
		UINT GetWidth() { return _desc.Width; }
		UINT GetHeight() { return _desc.Height; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	struct TexturePart
	{
		float left;
		float top;
		float right;
		float bottom;
	};

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
		RECT _currentTexturePart;
		TextureParam _dTexture;
		TextureParam _dTile;

	public:
		Texture(TextureResource* resource, ID3D11SamplerState* samplerState);

	public:
		void SetCurrentTexturePart(std::string partName) { _currentTexturePart = _resource->GetTexturePart(partName); }
		TexturePart GetCurrentTexturePart();
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
		Texture* _texture;
		ID3D11SamplerState* _samplerState;
		std::vector<RECT> _actionSequence;
		bool _loop;
		Timer _timer;
		float _interval;
		int _currentActionIndex;
		float _lastTime;

	public:
		Sprite(Texture* resource, std::vector<RECT> actionSequence, bool loop, float interval, ID3D11SamplerState* samplerState);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
