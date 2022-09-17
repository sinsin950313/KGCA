#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Texture.h"

namespace SSB
{
	class Shader;

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

	struct SimpleVertex2D
	{
		Position2D pos;
		ColorRGBA col;
		TextureParam texParam;
	};

	class DX2DObject : public Common, public DXDrawableInterface
	{
	private:
		// 0---1
		// |   |
		// 2---3
		std::vector<SimpleVertex2D> _vertexList;
		std::vector<DWORD> _indexList;
		Position2D _center;
		float _width;
		float _height;

	private:
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		Texture* _texture;
		Texture* _maskTexture;
		Shader* _vs;
		Shader* _ps;
		ID3D11InputLayout* _vertexLayout;

	public:
		DX2DObject(Position2D center, float width, float height) : _center(center), _width(width), _height(height) { }

	private:
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		void UpdateBoundary();
		std::vector<SimpleVertex2D> GetNDCBoundary();

	public:
		void SetTexture(Texture* texture) { _texture = texture; }
		void SetMaskTexture(Texture* alpha) { _maskTexture = alpha; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		void Resize(float width, float height);
		void Move(Position2D centerPosition) { _center = centerPosition; }
		void SetCenter(Position2D center) { _center = center; }
		Texture* GetTexture() { return _texture; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
	};
}
