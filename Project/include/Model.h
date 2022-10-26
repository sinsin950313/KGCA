#pragma once

#include "Common.h"
#include <vector>
#include "Vector.h"
#include "Texture.h"
#include "TextureManager.h"

namespace SSB
{
	struct Vertex
	{
		Float4 position;
		Float4 color;
		Float2 texture;
	};

	class Model : public Common
	{
	protected:
		std::vector<Vertex> _vertexList;
		std::vector<DWORD> _indexList;
		Sprite* _sprite;

	public:
		Model() : _sprite(SpriteLoader::GetInstance().GetDefaultSprite()) { }
		~Model() { Release(); }

	public:
		virtual void Build() = 0;

	public:
		std::vector<Vertex>& GetVertexList() { return _vertexList; }
		std::vector<DWORD>& GetIndexList() { return _indexList; }
		void SetSprite(Sprite* sprite) { _sprite = sprite; }
		Sprite* GetSprite() { return _sprite; }

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

	public:
		void Build() override;
	};

	class Terrain : public Model
	{
	private:
		float _cellDistance = 1.0f;
		//float tileX = 10.0f;
		//float tileY = 10.0f;
		float tileX = 1.0f;
		float tileY = 1.0f;

	public:
		void Make(unsigned int widthVertexCount, unsigned int heightVertexCount);
		
	public:
		void Build() override { Make(16 + 1, 16 + 1); }
	};
}
