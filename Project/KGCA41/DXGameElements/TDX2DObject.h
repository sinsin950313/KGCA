#pragma once

#include "CommonClass.h"
#include "TDXDrawableInterface.h"
#include <vector>

class TTexture;
class TShader;

struct Position2D
{
	float x;
	float y;
};

struct ColorRGBA
{
	float r;
	float g;
	float b;
	float a;
};

struct TextureParam
{
	float u;
	float v;
};

struct SimpleVertex2D
{
	Position2D pos;
	ColorRGBA col;
	TextureParam texParam;
};

class TDX2DObject : public Common, public TDXDrawableInterface
{
private:
	// 0---1
	// |   |
	// 2---3
	std::vector<SimpleVertex2D> _boundaryVertice;
	Position2D _center;
	float _width;
	float _height;

private:
	std::vector<SimpleVertex2D> _orderedBoundaryVertice;
	ID3D11Buffer* _vertexBuffer;
	TTexture* _texture;
	TShader* _vs;
	TShader* _ps;
	ID3D11InputLayout* _vertexLayout;

public:
	TDX2DObject(Position2D center, float width, float height) : _center(center), _width(width), _height(height) { }

public:
	void Move(Position2D centerPosition) { _center = centerPosition; }

private:
	void UpdateBoundary();
	std::vector<SimpleVertex2D> GetNDCBoundary();

public:
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
