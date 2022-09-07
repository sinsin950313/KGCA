#pragma once

#include "CommonClass.h"
#include <map>
#include <string>

class TTexture;
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11SamplerState;

class TTextureManager : public Common
{
private:
	std::map<std::wstring, TTexture*> _textureData;
	std::map<std::wstring, ID3D11SamplerState*> _samplerData;

private:
	static TTextureManager* _instance;
	TTextureManager();

public:
	~TTextureManager();

public:
	static TTextureManager& GetInstance();

public:
	TTexture* Load(std::wstring fileName, std::wstring alphaFileName = nullptr);
	ID3D11SamplerState* LoadSampler(std::wstring stateName);

private:
	std::wstring GetPath(std::wstring fileName) { return L"../../Resource/" + fileName; }
	
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
