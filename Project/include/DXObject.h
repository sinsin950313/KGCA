#pragma once

#include "DXDrawableInterface.h"
#include "Matrix.h"
#include "Model.h"
#include "Shader.h"
#include "Quaternion.h"

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
		Vector3 Translate;
		Vector3 Scale;
		Quaternion Rotate;
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

	public:
		std::vector<AnimationInfo> _animationInfos;
		int _currentAnimationFrame = 0;
		Timer _animationTimer;

		Model* _currentDrawModel;
		ID3D11Buffer* _currentDrawVertexBuffer;
		ID3D11Buffer* _currentDrawIndexBuffer;

	public:
		DXObject() { }
		virtual ~DXObject() { Release(); }

	protected:
		virtual bool CreateVertexBuffer();
		virtual bool CreateIndexBuffer();
		virtual bool CreateConstantBuffer();
		virtual void UpdateConstantBuffer();
		virtual void SetVertexLayoutDesc(D3D11_INPUT_ELEMENT_DESC** desc, int& count);
		virtual void DeviceContextSettingBeforeDraw(ID3D11DeviceContext* dc);

	private:
		bool CreateVertexLayout();

	protected:
		std::vector<Model*> GetModel() { return _models; }

	public:
		void SetAdditionalModel(Model* model) { _models.push_back(model); }
		void SetAdditionalChildObject(DXObject* child) { _childObjectList.push_back(child); child->_parent = this; }
		void SetAdditionalAnimation(AnimationInfo info);
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		HMatrix44 GetMatrix();
		void Move(Vector3 vec);
		void Rotate(float pitch, float yaw);
		OBB GetOBB();
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
