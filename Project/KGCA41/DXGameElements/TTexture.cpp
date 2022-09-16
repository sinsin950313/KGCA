#include "TTexture.h"

TTexture::TTexture(ID3D11Resource* textureResource, ID3D11ShaderResourceView* textureResourceView, ID3D11SamplerState* samplerState)
    : _textureResource(textureResource), _textureResourceView(textureResourceView), _samplerState(samplerState)
{
    static_cast<ID3D11Texture2D*>(_textureResource)->GetDesc(&_desc);
    _dTile = { 1, 1 };
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

void TTexture::RegisterTexturePartWithRelativeValue(std::string actionName, RECT size)
{
    RECT tmp;
    tmp.left = size.left;
    tmp.top = size.top;
    tmp.right = size.right + size.left;
    tmp.bottom = size.bottom + size.top;

    _actions.insert(std::make_pair(actionName, tmp));
}

void TTexture::RegisterTexturePartWithCoordinateValue(std::string actionName, RECT size)
{
    _actions.insert(std::make_pair(actionName, size));
}

TexturePart TTexture::GetCurrentTexturePart()
{
    TexturePart ret;
    ret.left = (((float)_currentAction.left / _desc.Width) + _dTexture.u) * _dTile.u;
    ret.top = (((float)_currentAction.top / _desc.Height) + _dTexture.v) * _dTile.v;
    ret.right = (((float)_currentAction.right / _desc.Width) + _dTexture.u) * _dTile.u;
    ret.bottom = (((float)_currentAction.bottom / _desc.Height) + _dTexture.v) * _dTile.v;

    return ret;
}

void TTexture::Scroll(float xRatio, float yRatio)
{
    _dTexture.u = xRatio;
    _dTexture.v = yRatio;
}

void TTexture::Tile(float xCoefficient, float yCoefficient)
{
    _dTile.u = xCoefficient;
    _dTile.v = yCoefficient;
}
