#include "Model.h"

namespace SSB
{
	//void Terrain::Make(unsigned int widthVertexCount, unsigned int heightVertexCount)
	//{
	//	int hWidthVertexCount = widthVertexCount / 2;
	//	int hHeightVertexCount = heightVertexCount / 2;

	//	// z x-->
	//	// |
	//	// |
	//	// v
	//	_vertexList.resize(widthVertexCount * heightVertexCount);
	//	for (int row = 0; row < heightVertexCount; ++row)
	//	{
	//		for (int col = 0; col < widthVertexCount; ++col)
	//		{
	//			int index = row * widthVertexCount + col;
	//			_vertexList[index].position = { (float)(col - hWidthVertexCount) * _cellDistance, 0.0f, (float)(hHeightVertexCount - row) * _cellDistance, 1.0f };
	//			_vertexList[index].color = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f };
	//			_vertexList[index].texture = { ((float)col / (float)(widthVertexCount - 1.0f)) * tileX, ((float)row / (float)(heightVertexCount - 1.0f)) * tileY };
	//		}
	//	}

	//	// index-- -- -
	//	//   |  / | /|
	//	//   | /  |/ |
	//	//    ---- -- -
	//	_indexList.resize((widthVertexCount - 1) * (heightVertexCount - 1) * 2 * 3);
	//	unsigned int index = 0;
	//	for (int row = 0; row < heightVertexCount - 1; ++row)
	//	{
	//		for (int col = 0; col < widthVertexCount - 1; ++col)
	//		{
	//			int vIndex = row * widthVertexCount + col;
	//			_indexList[index + 0] = vIndex;
	//			_indexList[index + 1] = vIndex + 1;
	//			_indexList[index + 2] = vIndex + widthVertexCount;

	//			_indexList[index + 3] = vIndex + widthVertexCount;
	//			_indexList[index + 4] = vIndex + 1;
	//			_indexList[index + 5] = vIndex + widthVertexCount + 1;

	//			index += 6;
	//		}
	//	}
	//}
	void Box::Build()
	{
		_vertexList.resize(24);
		_vertexList[0] = Vertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[1] = Vertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[2] = Vertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[3] = Vertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };
		// µÞ¸é
		_vertexList[4] = Vertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[5] = Vertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[6] = Vertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[7] = Vertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿À¸¥ÂÊ
		_vertexList[8] = Vertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[9] = Vertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[10] = Vertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[11] = Vertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.0f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¿ÞÂÊ
		_vertexList[12] = Vertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[13] = Vertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[14] = Vertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[15] = Vertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.0f, 1.0f}, Float2{0.0f, 0.5f} };

		// À­¸é
		_vertexList[16] = Vertex{ Float4{-0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[17] = Vertex{ Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[18] = Vertex{ Float4{0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[19] = Vertex{ Float4{-0.5f, 0.5f, -0.5f, 1.0f}, Float4{0.5f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		// ¾Æ·§¸é
		_vertexList[20] = Vertex{ Float4{-0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.0f} };
		_vertexList[21] = Vertex{ Float4{0.5f, -0.5f, -0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.0f} };
		_vertexList[22] = Vertex{ Float4{0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.5f, 0.5f} };
		_vertexList[23] = Vertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.5f, 0.5f, 1.0f}, Float2{0.0f, 0.5f} };

		_indexList.resize(36);
		int iIndex = 0;
		_indexList[iIndex++] = 0; 	_indexList[iIndex++] = 1; 	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 0;	_indexList[iIndex++] = 2; 	_indexList[iIndex++] = 3;
		_indexList[iIndex++] = 4; 	_indexList[iIndex++] = 5; 	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 4;	_indexList[iIndex++] = 6; 	_indexList[iIndex++] = 7;
		_indexList[iIndex++] = 8; 	_indexList[iIndex++] = 9; 	_indexList[iIndex++] = 10; _indexList[iIndex++] = 8;	_indexList[iIndex++] = 10; _indexList[iIndex++] = 11;
		_indexList[iIndex++] = 12; _indexList[iIndex++] = 13; _indexList[iIndex++] = 14; _indexList[iIndex++] = 12;	_indexList[iIndex++] = 14; _indexList[iIndex++] = 15;
		_indexList[iIndex++] = 16; _indexList[iIndex++] = 17; _indexList[iIndex++] = 18; _indexList[iIndex++] = 16;	_indexList[iIndex++] = 18; _indexList[iIndex++] = 19;
		_indexList[iIndex++] = 20; _indexList[iIndex++] = 21; _indexList[iIndex++] = 22; _indexList[iIndex++] = 20;	_indexList[iIndex++] = 22; _indexList[iIndex++] = 23;
	}
	void Triangle::Build()
	{
		_vertexList.resize(3);
		_vertexList[0] = Vertex{ Float4{+0.0f, +0.5f, 0.5f, 1.0f}, Float4{1.0f, 0.0f, 0.0f, 0.0f}, Float2{0, 0} };
		_vertexList[1] = Vertex{ Float4{+0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 1.0f, 0.0f, 0.0f}, Float2{0, 0} };
		_vertexList[2] = Vertex{ Float4{-0.5f, -0.5f, 0.5f, 1.0f}, Float4{0.0f, 0.0f, 1.0f, 0.0f}, Float4{0, 0} };

		_indexList.resize(3);
		int iIndex = 0;
		_indexList[iIndex++] = 0;
		_indexList[iIndex++] = 1;
		_indexList[iIndex++] = 2;
	}
	bool Model::Init()
	{
		Build();
		return false;
	}
	bool Model::Frame()
	{
		return false;
	}
	bool Model::Render()
	{
		return false;
	}
	bool Model::Release()
	{
		_vertexList.clear();
		_indexList.clear();
		if (_sprite)
		{
			_sprite = nullptr;
		}
		return false;
	}
}
