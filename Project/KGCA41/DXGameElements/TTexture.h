#pragma once

#include <d3d11.h>
#include "CommonClass.h"
#include <map>
#include <string>

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

class TTexture : public Common
{
private:
	ID3D11Resource* _textureResource;
	D3D11_TEXTURE2D_DESC _desc;
	ID3D11ShaderResourceView* _textureResourceView;
	ID3D11SamplerState* _samplerState;
	std::map<std::string, RECT> _actions;
	RECT _currentAction;
	TextureParam _dTexture;
	TextureParam _dTile;

public:
	TTexture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState);

public:
	void SetSamplerState(ID3D11SamplerState* samplerState);
	ID3D11Resource* GetResource() const { return _textureResource; }
	ID3D11ShaderResourceView** GetShaderResourceView() { return &_textureResourceView; }
	ID3D11SamplerState* GetSamplerState() { return _samplerState; }
	// left, top, width, height
	void RegisterTexturePartWithRelativeValue(std::string actionName, RECT size);
	/// left, top, right, bottom
	void RegisterTexturePartWithCoordinateValue(std::string actionName, RECT size);
	void SetCurrentTexturePart(std::string action) { _currentAction= _actions.find(action)->second; }
	TexturePart GetCurrentTexturePart();
	void Scroll(float xRatio, float yRatio);
	void Tile(float xCoefficient, float yCoefficient);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
