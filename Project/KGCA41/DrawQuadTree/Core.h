#pragma once
#pragma comment(lib, "d3d11.lib")

#include "CommonClass.h"
#include "CollisionTree.h"
#include <d3d11.h>
#include <map>

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

class Core : public Common
{
private:
	QuadTree _qt;
	int _mapWidth = 100;
	int _mapHeight = 100;
	std::vector<Object2D*> _staticObjects;
	std::vector<Object2D*> _dynamicObjects;
	Object2D* _player = nullptr;

private:
	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _deviceContext = nullptr;
	std::map<Object2D*, ID3D11Buffer*> _buffers;
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;
	ID3DBlob* _vsCode;
	ID3DBlob* _psCode;
	std::map<Object2D*, std::vector<SimpleVertex>> _verticeList;
	ID3D11InputLayout* _vertexLayout;

public:
	Core() : _qt(100, 100, 3) { }

private:
	HRESULT CreateVertexBuffer(Object2D* object);
	HRESULT CreateVertexShader();
	HRESULT CreatePixelShader();
	HRESULT CreateVertexLayout();
	SimpleVertex GetSimpleVertex(Object2D* object, Vector2D center, Vector2D* vertex);
	void UpdateVertex(Object2D* object);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	void Run();
	void SetDevice(ID3D11Device* device, ID3D11DeviceContext* deviceContext) { _device = device; _deviceContext = deviceContext; }
};
