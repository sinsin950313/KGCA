#pragma once
#pragma comment (lib, "DirectXBasic.lib")

#include "TDXWindow.h"
#include <vector>

class TTexture;
class TShader;

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
	TTexture* _texture;
	TShader* _vertexShader;
	TShader* _pixelShader;
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
