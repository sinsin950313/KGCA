#pragma once

#include "DXDrawableInterface.h"
#include "Matrix.h"
#include "Model.h"
#include "Shader.h"

namespace SSB
{
	struct OBB
	{
		HMatrix44 Matrix;
		float Width;
		float Height;
		float Depth;
	};

	class DXObject : public DXDrawableInterface
	{
	private:
		struct ConstantData
		{
			Float44 World;
			Float44 View;
			Float44 Projection;
		};
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
		ID3D11Buffer* _constantBuffer;
		ConstantData _constantData;

	public:
		DXObject() { }
		virtual ~DXObject() { Release(); }

	private:
		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		bool CreateVertexLayout();
		bool CreateConstantBuffer();
		void UpdateConstantBuffer();

	protected:
		Model* GetModel() { return _model; }

	public:
		void SetModel(Model* model) { _model = model; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		HMatrix44 GetMatrix() { return _matrix; }
		void Move(Vector3 vec);
		void Rotate(float pitch, float yaw);
		OBB GetOBB();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		void UpdateParentData(Position2D parentCenter, float parentRadian) override { }
	};
}
