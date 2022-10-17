#pragma once
#pragma comment(lib, "d3dcompiler.lib")

#include "DXWindow.h"
#include <d3dcompiler.h>
#include "Vector.h"
#include "Matrix.h"

using namespace SSB;

struct SimpleVertex
{
	Float4 position;
	Float4 color;
	Float2 texture;
};

class BoxDrawer : public DXWindow
{
public:
	BoxDrawer(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }

private:
	ID3D11Buffer* _vertexBuffer;
	ID3D11InputLayout* _inputLayout;
	ID3DBlob* _vsCode;
	ID3DBlob* _psCode;
	ID3D11VertexShader* _vs;
	ID3D11PixelShader* _ps;
	std::vector<SimpleVertex> _vertexList;
	std::vector<int> _indexList;
	ID3D11Buffer* _indexBuffer;

public:
	bool Init() override;
	bool Frame() override;
	bool Release() override;
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
