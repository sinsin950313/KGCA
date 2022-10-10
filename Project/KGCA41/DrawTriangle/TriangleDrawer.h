#pragma once
#pragma comment(lib, "d3dcompiler.lib")

#include "DXWindow.h"
#include <d3dcompiler.h>

using namespace SSB;

struct SimpleVertex
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};

class TriangleDrawer : public DXWindow
{
public:
	TriangleDrawer(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }
private:
	ID3D11Buffer* _vertexBuffer;
	ID3D11InputLayout* _inputLayout;
	ID3DBlob* _vsCode;
	ID3DBlob* _psCode;
	ID3D11VertexShader* _vs;
	ID3D11PixelShader* _ps;

public:
	bool Init() override;
	bool Release() override;
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
