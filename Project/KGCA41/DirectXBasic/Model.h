#pragma once

#include "Common.h"
#include <vector>
#include "Vector.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Matrix.h"

namespace SSB
{
	struct Vertex_PCT
	{
		Float4 position;
		Float4 color;
		Float2 texture;
	};

	struct Vertex_PNCT
	{
		Float4 position;
		Float4 normal;
		Float4 color;
		Float2 texture;
	};

	class Model : public Common
	{
	protected:
		std::vector<Vertex_PNCT> _vertexList;
		std::vector<DWORD> _indexList;
		Sprite* _sprite;
		HMatrix44 _offset;

	public:
		Model() : _sprite(SpriteLoader::GetInstance().GetDefaultSprite()) { }
		virtual ~Model() { Release(); }

	public:
		virtual void Build() = 0;

	public:
		std::vector<Vertex_PNCT>& GetVertexList() { return _vertexList; }
		std::vector<DWORD>& GetIndexList() { return _indexList; }
		void SetSprite(Sprite* sprite) { _sprite = sprite; }
		Sprite* GetSprite() { return _sprite; }
		void SetModelOffset(HMatrix44 matrix);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class Direction : public Model
	{
	public:
		void Build() override;
	};

	class Triangle : public Model
	{
	private:

	public:
		void Build() override;
	};

	class Box : public Model
	{
	private:
		float _width;
		float _height;
		float _depth;

	public:
		Box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

	public:
		void Build() override;
	};

	//class Terrain : public Model
	//{
	//private:
	//	float _cellDistance = 1.0f;
	//	//float tileX = 10.0f;
	//	//float tileY = 10.0f;
	//	float tileX = 1.0f;
	//	float tileY = 1.0f;
	//	unsigned int _widthVertexCount = 16;
	//	unsigned int _heightVertexCount = 16;

	//private:
	//	void Make(unsigned int widthVertexCount, unsigned int heightVertexCount);

	//public:
	//	void SetSize(unsigned int widthVertexCount, unsigned int heightVertexCount) { _widthVertexCount = widthVertexCount; _heightVertexCount = heightVertexCount; }
	//	
	//public:
	//	void Build() override { Make(_widthVertexCount + 1, _heightVertexCount + 1); }
	//};
}
