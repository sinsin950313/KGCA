#pragma once

#include "DXDrawableInterface.h"
#include "Matrix.h"
#include "Model.h"
#include "Shader.h"

namespace SSB
{
	class DXObject : public DXDrawableInterface
	{
	private:
		//Model* _direction;
		//ID3D11Buffer* _directionVertexBuffer;
		//ID3D11Buffer* _directionIndexBuffer;

		Model* _model;
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		Shader* _vs;
		Shader* _ps;
		ID3D11InputLayout* _vertexLayout;
		HMatrix44 _matrix;

	public:
		DXObject() { }

	private:
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		bool CreateVertexLayout();

	public:
		void SetModel(Model* model) { _model = model; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		void UpdateParentData(Position2D parentCenter, float parentRadian) override { }
	};
}
