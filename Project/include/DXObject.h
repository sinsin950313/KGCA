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
	struct ConstantData
	{
		Float44 World;
		Float44 View;
		Float44 Projection;
	};
	struct AnimationInfo
	{
		int StartFrame;
		int EndFrame;
		float TickPerFrame = 160;
		float FrameSpeed = 30;
		int CurrentFrame;
		HMatrix44 Matrix;
	};

	class DXObject : public DXDrawableInterface
	{
	private:
		//Model* _direction;
		//ID3D11Buffer* _directionVertexBuffer;
		//ID3D11Buffer* _directionIndexBuffer;

		std::vector<Model*> _models;
		std::vector<ID3D11Buffer*> _vertexBuffers;
		std::vector<ID3D11Buffer*> _indexBuffers;
		Shader* _vs;
		Shader* _ps;
		ID3D11InputLayout* _vertexLayout;
		HMatrix44 _matrix;
		ID3D11Buffer* _constantBuffer;
		ConstantData _constantData;

		DXObject* _parent = nullptr;
		std::vector<DXObject*> _childObjectList;

		std::vector<AnimationInfo> _animationInfos;
		int _currentAnimationFrame = 0;
		Timer _animationTimer;

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
		std::vector<Model*> GetModel() { return _models; }

	public:
		void SetAdditionalModel(Model* model) { _models.push_back(model); }
		void SetAdditionalChildObject(DXObject* child) { _childObjectList.push_back(child); child->_parent = this; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		HMatrix44 GetMatrix();
		void Move(Vector3 vec);
		void Rotate(float pitch, float yaw);
		OBB GetOBB();
		void AddAnimation(AnimationInfo info);
		HMatrix44 GetInterpolate(AnimationInfo info);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		void UpdateParentData(Position2D parentCenter, float parentRadian) override { }
	};
}
