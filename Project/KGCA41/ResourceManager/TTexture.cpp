#include "TTexture.h"

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
    _textureResource->Release();
    _textureResourceView->Release();
    return true;
}
