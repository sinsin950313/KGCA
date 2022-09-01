#include "TShader.h"
#include <d3d11.h>

bool TShader::Init()
{
    return true;
}

bool TShader::Frame()
{
    return true;
}

bool TShader::Render()
{
    return true;
}

bool TShader::Release()
{
    _shader->Release();
    _code->Release();
    return true;
}
