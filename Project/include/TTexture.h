#pragma once

#include <d3d11.h>
#include "CommonClass.h"

class TTexture : public Common
{
private:
	ID3D11Resource* _textureResource;
	ID3D11ShaderResourceView* _textureResourceView;
	ID3D11SamplerState* _samplerState;

public:
	TTexture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState);

public:
	void SetSamplerState(ID3D11SamplerState* samplerState);
	ID3D11Resource* GetResource() const { return _textureResource; }
	ID3D11ShaderResourceView** GetShaderResourceView() { return &_textureResourceView; }
	ID3D11SamplerState* GetSamplerState() { return _samplerState; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
