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
	std::wstring _path = L"../../Shader/";

private:
	static TShaderManager* _instance;
	TShaderManager();

public:
	~TShaderManager();

public:
	static TShaderManager& GetInstance();

private:
	template<typename func> TShader* LoadShader(std::wstring fileName, std::string entryPoint, std::string target, std::map<std::wstring, TShader*>& data, func);
	std::wstring GetPath(std::wstring fileName) { return _path + fileName; }
	std::wstring GetKey(std::wstring fileName, std::string entryPoint);

public:
	void SetPath(std::wstring path) { _path = path; }
	TShader* LoadVertexShader(std::wstring fileName, std::string entryPoint, std::string target);
	TShader* LoadPixelShader(std::wstring fileName, std::string entryPoint, std::string target);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
