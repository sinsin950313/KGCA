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

private:
	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _deviceContext = nullptr;

public:
	~TTextureManager();

public:
	static TTextureManager& GetInstance();

public:
	void Set(ID3D11Device* device, ID3D11DeviceContext* deviceContext) { _device = device, _deviceContext = deviceContext; }
	TTexture* Load(std::wstring path);
	
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
