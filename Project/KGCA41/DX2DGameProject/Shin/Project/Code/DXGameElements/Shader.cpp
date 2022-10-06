#include "Shader.h"
#include <d3d11.h>

namespace SSB
{
    bool Shader::Init()
    {
        return true;
    }

    bool Shader::Frame()
    {
        return true;
    }

    bool Shader::Render()
    {
        return true;
    }

    bool Shader::Release()
    {
        if (_shader)_shader->Release();
        if (_code)_code->Release();

        _shader = nullptr;
        _code = nullptr;

        return true;
    }
}
