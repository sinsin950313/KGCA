#pragma once

#include <vector>
#include "Vector.h"

namespace SSB
{
	struct Vertex
	{
		Float3 position;
		Float4 color;
		Float2 texture;
	};

	class Terrain
	{
	private:
		float _cellDistance = 1.0f;
		float tileX = 10.0f;
		float tileY = 10.0f;
		std::vector<Vertex> _vertexList;
		std::vector<int> _indexList;

	public:
		void Make(unsigned int widthVertexCount, unsigned int heightVertexCount);
	};
}
