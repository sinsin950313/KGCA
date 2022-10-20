#pragma once

#include "Common.h"
#include <vector>
#include "Vector.h"
#include "Texture.h"

namespace SSB
{
	struct Vertex
	{
		Float4 position;
		Float4 color;
		Float2 texture;
	};

	class Model/* : public Common*/
	{
	protected:
		std::vector<Vertex> _vertexList;
		std::vector<DWORD> _indexList;
		Sprite* _sprite;

	public:
		virtual void Build() = 0;
		std::vector<Vertex>& GetVertexList() { return _vertexList; }
		std::vector<DWORD>& GetIndexList() { return _indexList; }
		Sprite* GetSprite() { return _sprite; }

	//public:
	//	bool Init() override;
	//	bool Frame() override;
	//	bool Render() override;
	//	bool Release() override;
	};

	class Triangle : public Model
	{
	private:

	public:
		void Build();
	};

	class Box : public Model
	{
	private:

	public:
		void Build();
	};

	class Terrain : public Model
	{
	private:
		float _cellDistance = 1.0f;
		float tileX = 10.0f;
		float tileY = 10.0f;
		//std::vector<Vertex> _vertexList;
		//std::vector<int> _indexList;

	public:
		void Make(unsigned int widthVertexCount, unsigned int heightVertexCount);
		
	public:
		void Build() override { Make(16 + 1, 16 + 1); }
	};
}
