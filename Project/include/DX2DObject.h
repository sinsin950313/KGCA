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

	Position2D operator+(Position2D& lValue, Position2D& rValue);

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
		Position2D _parentCenter{ 0, 0 };
		float _width;
		float _height;
		std::vector<DX2DObject*> _childObjectList;

	private:
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		Sprite* _sprite;
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
		void SetSprite(Sprite* resource) { _sprite = resource; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		void Resize(float width, float height);
		void Move(Position2D centerPosition) { _center = centerPosition; }
		void SetCenter(Position2D center) { _center = center; }
		void UpdateParentCenter(Position2D parentCenter) { _parentCenter = parentCenter; }
		Sprite* GetSprite() { return _sprite; }
		float GetWidth() { return _width; }
		float GetHeight() { return _height; }
		Position2D GetCenter() { return _center + _parentCenter; }
		// don't Init before AddChild.
		void AddChild(DX2DObject* child) { _childObjectList.push_back(child); }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
	};
}
