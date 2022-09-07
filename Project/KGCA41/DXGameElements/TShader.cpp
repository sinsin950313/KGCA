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
    if (_shader)_shader->Release();
    if (_code)_code->Release();

    _shader = nullptr;
    _code = nullptr;

    return true;
}
