#pragma comment (lib, "d3dcompiler.lib")

#include "TShaderManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "TShader.h"
#include "TDXWindow.h"

TShaderManager* TShaderManager::_instance = nullptr;
extern TDXWindow* g_dxWindow;

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

TShader* TShaderManager::LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target)
{
    if (_vertexShaderData.find(fileName) == _vertexShaderData.end())
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

        ID3D11VertexShader* shader;
        hr = g_dxWindow->GetDevice()->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &shader);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TShader* shaderComp = new TShader(shader, code);
        _vertexShaderData.insert(std::make_pair(fileName, shaderComp));
    }
    return _vertexShaderData.find(fileName)->second;
}

TShader* TShaderManager::LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target)
{
    if (_pixelShaderData.find(fileName) == _pixelShaderData.end())
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

        ID3D11PixelShader* shader;
        hr = g_dxWindow->GetDevice()->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, &shader);
        if (FAILED(hr))
        {
            return nullptr;
        }

        TShader* shaderComp = new TShader(shader, code);
        _vertexShaderData.insert(std::make_pair(fileName, shaderComp));
    }
    return _vertexShaderData.find(fileName)->second;
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
