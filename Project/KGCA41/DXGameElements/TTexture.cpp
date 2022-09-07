#include "TTexture.h"

TTexture::TTexture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState)
    : _textureResource(textureResource), _textureResourceView(textureResourceView), _samplerState(samplerState)
{

}

void TTexture::SetSamplerState(ID3D11SamplerState* samplerState)
{
	_samplerState = samplerState;
}

bool TTexture::Init()
{
    return true;
}

bool TTexture::Frame()
{
    return true;
}

bool TTexture::Render()
{
    return true;
}

bool TTexture::Release()
{
    if (_textureResource) _textureResource->Release();
    if (_textureResourceView)_textureResourceView->Release();

    _textureResource = nullptr;
    _textureResourceView = nullptr;
	_samplerState = nullptr;

    return true;
}
