#pragma once

#include "CommonClass.h"
#include <map>
#include <string>

class TTexture;
class ID3D11Device;
class ID3D11DeviceContext;

class TTextureManager : public Common
{
private:
	std::map<std::wstring, TTexture*> _textureData;

private:
	static TTextureManager* _instance;
	TTextureManager();

public:
	~TTextureManager();

public:
	static TTextureManager& GetInstance();

public:
	TTexture* Load(std::wstring path);
	
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
