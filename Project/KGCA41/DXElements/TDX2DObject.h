#pragma once

#include "Object.h"
#include "CommonClass.h"
#include "TDXDrawableInterface.h"
#include "Rectangle.h"

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

class TDX2DObject : public Object2D, Common, TDXDrawableInterface
{
private:
	std::vector<SimpleVertex> _vertice;
	ID3D11Buffer* _vertexBuffer;
	TTexture* _texture;
	TShader* _vs;
	TShader* _ps;
	ID3D11InputLayout* _vertexLayout;

public:
	TDX2DObject(Custom::Rectangle* rect) : Object2D(rect, Rigidbody2D()) { }

private:
	ID3D11Device* _device;
	ID3D11DeviceContext* _deviceContext;

public:
	void Set(ID3D11Device* device, ID3D11DeviceContext* deviceContext) { _device = device; _deviceContext = deviceContext; }
	void SetTexture(TTexture* texture) { _texture = texture; }
	void SetVertexShader(TShader* shader) { _vs = shader; }
	void SetPixelShader(TShader* shader) { _ps = shader; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	void Draw(ID3D11DeviceContext* dc) override;
};
