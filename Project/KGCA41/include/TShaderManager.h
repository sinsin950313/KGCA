#pragma once

#include "CommonClass.h"
#include <string>
#include <map>

class TShader;
class ID3D11Device;

class TShaderManager : public Common
{
private:
	std::map<std::wstring, TShader*> _vertexShaderData;
	std::map<std::wstring, TShader*> _pixelShaderData;

private:
	static TShaderManager* _instance;
	TShaderManager();

public:
	~TShaderManager();

private:
	ID3D11Device* _device;

public:
	static TShaderManager& GetInstance();

public:
	void Set(ID3D11Device* device) { _device = device; }
	TShader* LoadVertexShader(std::wstring path, std::string entryPoint, std::string target);
	TShader* LoadPixelShader(std::wstring path, std::string entryPoint, std::string target);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
