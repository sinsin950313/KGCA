#pragma comment (lib, "d3dcompiler.lib")

#include "ShaderManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Shader.h"
#include "DXWindow.h"

namespace SSB
{
    ShaderManager* ShaderManager::_instance = nullptr;
    extern DXWindow* g_dxWindow;

    ShaderManager::ShaderManager()
    {
    }

    ShaderManager::~ShaderManager()
    {
        Release();

        delete _instance;
        _instance = nullptr;
    }

    ShaderManager& ShaderManager::GetInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new ShaderManager();
        }
        return *_instance;
    }

    template<typename func>
    Shader* ShaderManager::LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, Shader*>& data, func CreateShader)
    {
        std::wstring key = GetKey(fileName, entryPoint);
        if (data.find(key) == data.end())
        {
            HRESULT hr;

            auto path = GetPath(fileName);
            ID3DBlob* code = nullptr;
            ID3DBlob* errorCode = nullptr;
            hr = D3DCompileFromFile(path.c_str(), NULL, NULL, entryPoint.c_str(), target.c_str(), 0, 0, &code, &errorCode);
            if (FAILED(hr))
            {
                if (errorCode != nullptr)
                {
                    OutputDebugStringA((char*)errorCode->GetBufferPointer());
                    errorCode->Release();
                }
                return nullptr;
            }

            ID3D11DeviceChild* shader;
            hr = CreateShader(code, &shader);
            if (FAILED(hr))
            {
                return nullptr;
            }

            Shader* shaderComp = new Shader(shader, code);
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

    Shader* ShaderManager::LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target)
    {
        auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
        {
            return g_dxWindow->GetDevice()->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11VertexShader**)shader);
        };
        return LoadShader(fileName, entryPoint, target, _vertexShaderData, createShader);
    }

    Shader* ShaderManager::LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target)
    {
        auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
        {
            return g_dxWindow->GetDevice()->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11PixelShader**)shader);
        };
        return LoadShader(fileName, entryPoint, target, _pixelShaderData, createShader);
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
}
