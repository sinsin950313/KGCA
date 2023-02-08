#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Shader.h"
#include "Matrix.h"
#include "DXObject.h"
#include "Camera.h"

namespace SSB
{
	class Map : public DXDrawableInterface
	{
	private:
		class Node : public Common
		{
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
			ID3D11Buffer* GetIndexBuffer() { return _indexBuffer; }
			std::vector<int> GetIndexList() { return _indexList; }

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};
		std::vector<Vertex_PNCT> _vertexList;
		std::vector<int> _indexList;
		Sprite* _sprite;
		ID3D11Buffer* _vertexBuffer;
		Shader* _vs;
		Shader* _ps;
		ID3D11InputLayout* _vertexLayout;
		HMatrix44 _matrix;
		ID3D11Buffer* _constantBuffer;
		ConstantData _constantData;

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
		Map(int layerDepth = 4) : _layerDepth(layerDepth) { }
		virtual ~Map() { Release(); }

	private:
		void CreateVertex();
		bool CreateVertexBuffer();
		bool CreateVertexLayout();
		bool CreateConstantBuffer();
		void UpdateConstantBuffer();
		Vector3 CalculateFaceNormal(UINT i0, UINT i1, UINT i2);
		void CalculateVertexNormal();
		float GetCoordinateHeight(int x, int z);
		float Lerp(float start, float end, float param);

	public:
		void SetSize(unsigned int widthVertexCount, unsigned int heightVertexCount) { _widthVertexCount = widthVertexCount + 1; _heightVertexCount = heightVertexCount + 1; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		HMatrix44 GetMatrix() { return _matrix; }
		void Move(Vector3 vec);
		void SetSprite(Sprite* sprite) { _sprite = sprite; }
		void SetHeightMap(std::wstring fileName);
		float GetHeight(float x, float z);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;

	private:
		friend class Node;
	};
}
