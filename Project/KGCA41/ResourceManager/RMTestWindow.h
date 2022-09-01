#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "TDXWindow.h"
#include <vector>

class TTexture;

struct SimpleVertex
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
	float u;
	float v;
};

class RMTestWindow : public TDXWindow
{
private:
	std::vector<SimpleVertex> _vertice;
	ID3D11Buffer* _vertexBuffer;
	//ID3D11Resource* _textureResource;
	//ID3D11ShaderResourceView* _textureShaderResourceView;
	TTexture* _texture;
	ID3D11VertexShader* _vs;
	ID3D11PixelShader* _ps;
	ID3DBlob* _vsCode;
	ID3DBlob* _psCode;
	ID3D11InputLayout* _vertexLayout;

public:
	RMTestWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TDXWindow(name, hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

protected:
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};

