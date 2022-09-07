#pragma once
#pragma comment (lib, "d3dcompiler.lib")

#include "CommonClass.h"
#include <d3dcompiler.h>

class ID3D11DeviceChild;

class TShader : public Common
{
private:
	ID3D11DeviceChild* _shader;
	ID3DBlob* _code;

public:
	TShader(ID3D11DeviceChild* shader, ID3DBlob* code) : _shader(shader), _code(code) { }
	ID3D11DeviceChild* GetShader() { return _shader; }
	ID3DBlob* GetCode() { return _code; }

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};
