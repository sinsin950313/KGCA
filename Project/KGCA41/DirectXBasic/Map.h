#pragma once

#include "Common.h"
#include "DXDrawableInterface.h"
#include <vector>
#include "Shader.h"
#include "Matrix.h"
#include "DXObject.h"

namespace SSB
{
	class Map : public DXDrawableInterface, public Common
	{
	private:
		class Node : public Common
		{
		private:
			std::vector<Node*> _nodes;
			ID3D11Buffer* _indexBuffer;
			std::vector<int> _indexList;

		public:
			Node(Map& map, int lt, int lb, int rt, int rb, int depth);

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
		std::vector<Vertex> _vertexList;
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
		//float tileX = 10.0f;
		//float tileY = 10.0f;
		float tileX = 1.0f;
		float tileY = 1.0f;
		unsigned int _widthVertexCount = 16;
		unsigned int _heightVertexCount = 16;

		Node* _root;
		int _depth = 3;
		std::vector<Node*> _drawingNodeList;

	public:
		Map(int depth = 3) : _depth(depth) { }
		virtual ~Map() { Release(); }

	private:
		void CreateVertex();
		bool CreateVertexBuffer();
		bool CreateVertexLayout();
		bool CreateConstantBuffer();
		void UpdateConstantBuffer();

	public:
		void SetSize(unsigned int widthVertexCount, unsigned int heightVertexCount) { _widthVertexCount = widthVertexCount + 1; _heightVertexCount = heightVertexCount + 1; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		HMatrix44 GetMatrix() { return _matrix; }
		void Move(Vector3 vec);
		OBB GetOBB();
		void SetSprite(Sprite* sprite) { _sprite = sprite; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		void UpdateParentData(Position2D parentCenter, float parentRadian) override { }

	private:
		friend class Node;
	};
}
