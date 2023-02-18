#pragma comment (lib, "d3dcompiler.lib")

#include "ShaderManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Shader.h"
#include "DXWindow.h"
#include <cassert>

namespace SSB
{
    ShaderManager ShaderManager::_instance;
    extern DXWindow* g_dxWindow;

    ShaderManager::ShaderManager()
    {
    }

    ShaderManager::~ShaderManager()
    {
        Release();
    }

    ShaderManager& ShaderManager::GetInstance()
    {
        return _instance;
    }

	template<typename ShaderCreater>
    Shader* ShaderManager::LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, Shader*>& data, ShaderCreater createrFunction, ShaderFactory* factory)
    {
        std::wstring key = GetKey(fileName, entryPoint);
        if (data.find(key) == data.end())
        {
            HRESULT hr;

            DWORD shaderFlag = D3DCOMPILE_SKIP_OPTIMIZATION;
#if defined(_DEBUG)
            shaderFlag |= D3DCOMPILE_DEBUG;
#endif

            auto path = GetPath(fileName);
            ID3DBlob* code = nullptr;
            ID3DBlob* errorCode = nullptr;
            hr = D3DCompileFromFile(path.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), target.c_str(), shaderFlag, 0, &code, &errorCode);
            if (FAILED(hr))
            {
                if (errorCode != nullptr)
                {
                    OutputDebugStringA((char*)errorCode->GetBufferPointer());
                    errorCode->Release();
                }
                assert(SUCCEEDED(hr));
                return nullptr;
            }

            ID3D11DeviceChild* shader;
            hr = createrFunction(code, &shader);
            if (FAILED(hr))
            {
                assert(SUCCEEDED(hr));
                return nullptr;
            }

            factory->SetShader(shader);
            factory->SetCode(code);
            Shader* shaderComp = factory->New();
            shaderComp->Init();
            data.insert(std::make_pair(key, shaderComp));
        }
        return data.find(key)->second;
    }

    std::wstring ShaderManager::GetKey(std::wstring fileName, std::string entryPoint)
    {
        std::wstring wEntryPoint;
        wEntryPoint.assign(entryPoint.begin(), entryPoint.end());

        return fileName + wEntryPoint;
    }

    VertexShader* ShaderManager::LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target)
    {
        auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
        {
            return g_dxWindow->GetDevice()->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11VertexShader**)shader);
        };
        class VertexShaderFactory : public ShaderFactory
        {
        public:
            Shader* New() override
            {
                return new VertexShader(_shader, _code);
            }
        };
        VertexShaderFactory factory;

        return (VertexShader*)LoadShader(fileName, entryPoint, target, _vertexShaderData, createShader, &factory);
    }

    PixelShader* ShaderManager::LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target)
    {
        auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
        {
            return g_dxWindow->GetDevice()->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11PixelShader**)shader);
        };
        class PixelShaderFactory : public ShaderFactory
        {
        public:
            Shader* New()
            {
                return new PixelShader(_shader, _code);
            }
        };
        PixelShaderFactory factory;

        return (PixelShader*)LoadShader(fileName, entryPoint, target, _pixelShaderData, createShader, &factory);
    }

    bool ShaderManager::Init()
    {
        return true;
    }

    bool ShaderManager::Frame()
    {
        return true;
    }

    bool ShaderManager::Render()
    {
        return true;
    }

    bool ShaderManager::Release()
    {
        for (auto iter : _vertexShaderData)
        {
            iter.second->Release();
            delete iter.second;
        }
        _vertexShaderData.clear();

        for (auto iter : _pixelShaderData)
        {
            iter.second->Release();
            delete iter.second;
        }
        _pixelShaderData.clear();

        return true;
    }
    void ShaderManager::ShaderFactory::SetShader(ID3D11DeviceChild* shader)
    {
        _shader = shader;
    }
    void ShaderManager::ShaderFactory::SetCode(ID3DBlob* code)
    {
        _code = code;
    }
}
