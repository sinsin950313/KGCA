#include "Model.h"

namespace SSB
{
	void Terrain::Make(unsigned int widthVertexCount, unsigned int heightVertexCount)
	{
		int hWidthVertexCount = widthVertexCount / 2;
		int hHeightVertexCount = heightVertexCount / 2;

		// z x-->
		// |
		// |
		// v
		_vertexList.resize(widthVertexCount * heightVertexCount);
		for (int row = 0; row < heightVertexCount; ++row)
		{
			for (int col = 0; col < widthVertexCount; ++col)
			{
				int index = row * widthVertexCount + col;
				_vertexList[index].position = { (float)(col - hWidthVertexCount) * _cellDistance, 0.0f, (float)(hHeightVertexCount - row) * _cellDistance, 1.0f };
				_vertexList[index].color = { 1.0f, 1.0f, 1.0f, 1.0f };
				_vertexList[index].texture = { ((float)col / (float)(widthVertexCount - 1.0f)) * tileX, ((float)row / (float)(heightVertexCount - 1.0f)) * tileY };
			}
		}

		// index-- -- -
		//   |  / | /|
		//   | /  |/ |
		//    ---- -- -
		_indexList.resize((widthVertexCount - 1) * (heightVertexCount - 1) * 2 * 3);
		unsigned int index = 0;
		for (int row = 0; row < heightVertexCount; ++row)
		{
			for (int col = 0; col < widthVertexCount; ++col)
			{
				int vIndex = row * widthVertexCount + col;
				_indexList[index + 0] = vIndex;
				_indexList[index + 1] = vIndex + 1;
				_indexList[index + 2] = vIndex + widthVertexCount;

				_indexList[index + 3] = vIndex + widthVertexCount;
				_indexList[index + 4] = vIndex + 1;
				_indexList[index + 5] = vIndex + widthVertexCount + 1;

				index += 6;
			}
		}
	}
}
