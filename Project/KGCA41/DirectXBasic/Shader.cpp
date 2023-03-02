#include "Shader.h"
#include <d3d11.h>
#include "DXWindow.h"

namespace SSB
{
    extern DXWindow* g_dxWindow;

    std::string Shader::GetFileName()
    {
        return _fileName;
    }

    Shader::Shader(ID3D11DeviceChild* shader, ID3DBlob* code, std::string fileName) : _shader(shader), _code(code), _fileName(fileName)
    {
    }
    Shader::~Shader()
    {
        Release();
    }
    bool Shader::Init()
    {
        return true;
    }

    bool Shader::Frame()
    {
        return true;
    }

    bool Shader::Release()
    {
        if (_shader)
        {
            _shader->Release();
			_shader = nullptr;
        }

        if (_code)
        {
            _code->Release();
            _code = nullptr;
        }

        return true;
    }
    VertexShader::VertexShader(ID3D11DeviceChild* shader, ID3DBlob* code, std::string fileName) : Shader(shader, code, fileName)
    {
    }
    bool VertexShader::Render()
    {
		g_dxWindow->GetDeviceContext()->VSSetShader((ID3D11VertexShader*)GetShader(), NULL, 0);
        return true;
    }
    PixelShader::PixelShader(ID3D11DeviceChild* shader, ID3DBlob* code, std::string fileName) : Shader(shader, code, fileName)
    {
    }
    bool PixelShader::Render()
    {
		g_dxWindow->GetDeviceContext()->PSSetShader((ID3D11PixelShader*)GetShader(), NULL, 0);
        return true;
    }
}
