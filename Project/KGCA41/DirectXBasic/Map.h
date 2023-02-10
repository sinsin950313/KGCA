#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Shader.h"
#include "Matrix.h"
#include "DXObject.h"
#include "Camera.h"
#include "CollisionDetector.h"
#include "Box1.h"

namespace SSB
{
	class Map : public Common
	{
	private:
		class MapModel : public Model
		{
			float _widthVertexCount;
			float _heightVertexCount;
			Map* _map;

		public:
			MapModel(Map* map);

		private:
			Vector3 CalculateFaceNormal(UINT i0, UINT i1, UINT i2);
			void CalculateVertexNormal();

		public:
			float Lerp(float start, float end, float param);

		private:
			void Build() override;

		public:
			void Set(float widthVertexCount, float heightVertexCount);
			void SetHeightMap(std::wstring fileName);
			float GetCoordinateHeight(int x, int z);

		public:
			std::vector<Vertex_PNCT> GetVertice();
		};

	private:
		class Node : public Common
		{
		private:
			class NodeVolume : public Box1Volume
			{
			public:
				std::vector<TriangleData> GetWorldBaseTriangles() override;
			};

		private:
			std::vector<Node*> _nodes;
			ID3D11Buffer* _indexBuffer;
			std::vector<int> _indexList;

			Map& _map;
			int _leftTop;
			int _leftBottom;
			int _rightTop;
			int _rightBottom;
			int _center;
			int _layerDepth;

			float _width;
			float _height;
			float _depth;

			HMatrix44 _matrix;
			DXObject* _debugBox;

		public:
			Node(Map& map, int leftTop, int rightTop, int leftBottom, int rightBottom, int depth);

		public:
			bool CreateIndexBuffer();
			void Check(std::vector<Node*>& drawingNodeList, Camera* camera);
			ID3D11Buffer* GetIndexBuffer();
			std::vector<int> GetIndexList();

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};

		MapModel _model;
		ID3D11Buffer* _constantBuffer;
		ConstantData _constantData;

		HMatrix44 _matrix;

		float _cellDistance = 1.0f;
		float _heightScale = 100;
		float tileX = 1.0f;
		float tileY = 1.0f;
		unsigned int _widthVertexCount = 256 + 1u;
		unsigned int _heightVertexCount = 256 + 1u;

		Node* _root;
		int _layerDepth = 3;
		std::vector<Node*> _drawingNodeList;

		ID3D11Texture2D* _heightTexture;

		std::vector<float> _heightData;
		float _height = 0;

		bool _bDebug = false;

	public:
		Map(int layerDepth = 4);
		virtual ~Map();

	private:
		bool CreateConstantBuffer();
		void UpdateConstantBuffer();
		float GetCoordinateHeight(int x, int z);

	public:
		void SetSize(unsigned int widthVertexCount, unsigned int heightVertexCount);
		void SetPosition(Vector3 vec);
		void SetSprite(Sprite* sprite);
		void SetHeightMap(std::wstring fileName);
		void SetVertexShader(Shader* shader);
		void SetPixelShader(Shader* shader);
		float GetHeight(float x, float z);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
