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

public:
	static TShaderManager& GetInstance();

public:
	TShader* LoadVertexShader(std::wstring path, std::string entryPoint, std::string target);
	TShader* LoadPixelShader(std::wstring path, std::string entryPoint, std::string target);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
