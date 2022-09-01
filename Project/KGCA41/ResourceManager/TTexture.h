#pragma once

#include <d3d11.h>
#include "CommonClass.h"

class TTexture : public Common
{
private:
	ID3D11Resource* _textureResource;
	ID3D11ShaderResourceView* _textureResourceView;

public:
	TTexture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView) : _textureResource(textureResource), _textureResourceView(textureResourceView) { }
	ID3D11Resource* GetResource() const { return _textureResource; }
	ID3D11ShaderResourceView** GetShaderResourceView() { return &_textureResourceView; }

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};
