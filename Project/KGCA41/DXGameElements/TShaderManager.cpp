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

template<typename func>
TShader* TShaderManager::LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, TShader*>& data, func CreateShader)
{
	std::wstring key = GetKey(fileName, entryPoint);
    if(data.find(key) == data.end())
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

        TShader* shaderComp = new TShader(shader, code);
        data.insert(std::make_pair(key, shaderComp));
    }
    return data.find(key)->second;
}

std::wstring TShaderManager::GetKey(std::wstring fileName, std::string entryPoint)
{
	std::wstring wEntryPoint;
	wEntryPoint.assign(entryPoint.begin(), entryPoint.end());

    return fileName + wEntryPoint;
}

TShader* TShaderManager::LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target)
{
	auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
	{
		return g_dxWindow->GetDevice()->CreateVertexShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11VertexShader**)shader);
	};
    return LoadShader(fileName, entryPoint, target, _vertexShaderData, createShader);
}

TShader* TShaderManager::LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target)
{
	auto createShader = [](ID3DBlob* code, ID3D11DeviceChild** shader)->HRESULT
	{
		return g_dxWindow->GetDevice()->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(), NULL, (ID3D11PixelShader**)shader);
	};
    return LoadShader(fileName, entryPoint, target, _pixelShaderData, createShader);
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
