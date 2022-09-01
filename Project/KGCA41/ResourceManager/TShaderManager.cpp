#pragma comment (lib, "d3dcompiler.lib")

#include "TShaderManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "TShader.h"

TShaderManager* TShaderManager::_instance = nullptr;

TShaderManager::TShaderManager()
{
}

TShaderManager::~TShaderManager()
{
    Release();

    delete _instance;
}

TShaderManager& TShaderManager::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new TShaderManager();
    }
    return *_instance;
}

TShader* TShaderManager::LoadVertexShader(std::wstring path, std::string entryPoint, std::string target)
{
    if (_vertexShaderData.find(path) == _vertexShaderData.end())
    {
        HRESULT hr;

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

        ID3D11VertexShader* shader;
        hr = _device->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &shader);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TShader* shaderComp = new TShader(shader, code);
        _vertexShaderData.insert(std::make_pair(path, shaderComp));
    }
    return _vertexShaderData.find(path)->second;
}

TShader* TShaderManager::LoadPixelShader(std::wstring path, std::string entryPoint, std::string target)
{
    if (_pixelShaderData.find(path) == _pixelShaderData.end())
    {
        HRESULT hr;

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

        ID3D11PixelShader* shader;
        hr = _device->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &shader);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TShader* shaderComp = new TShader(shader, code);
        _vertexShaderData.insert(std::make_pair(path, shaderComp));
    }
    return _vertexShaderData.find(path)->second;
}

bool TShaderManager::Init()
{
    return true;
}

bool TShaderManager::Frame()
{
    return true;
}

bool TShaderManager::Render()
{
    return true;
}

bool TShaderManager::Release()
{
    for (auto iter : _vertexShaderData)
    {
        delete iter.second;
    }
    _vertexShaderData.clear();

    for (auto iter : _pixelShaderData)
    {
        delete iter.second;
    }
    _pixelShaderData.clear();

    return true;
}
