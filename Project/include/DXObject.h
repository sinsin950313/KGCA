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
	struct ActionFrameInfo
	{
		HMatrix44 Matrix;
		Vector3 Translate;
		Vector3 Scale;
		Quaternion Rotate;
	};
	struct ActionInfo
	{
		UINT EndFrame;
		std::vector<ActionFrameInfo> FrameInfoList;
	};

	class Animation : public Common
	{
	private:
		static ActionInfo DefaultAction;

	private:
		float _tickPerFrame = 160;
		float _frameSpeed = 30;
		Timer _animationTimer;

		std::map<std::string, ActionInfo> _actionList;
		ActionInfo* _currentAction;
		int _currentFrame;

	public:
		~Animation() { Release(); }

	public:
		void SetAdditionalAction(std::string name, ActionInfo info);
		HMatrix44 GetInterpolate();
		void UpdateCurrentAction(std::string name);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class DXObject : public DXDrawableInterface
	{
	private:
		Animation DefaultAnimation;

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

		Animation* _animation;

		Model* _currentDrawModel;
		ID3D11Buffer* _currentDrawVertexBuffer;
		ID3D11Buffer* _currentDrawIndexBuffer;

	public:
		DXObject();
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
		HMatrix44 GetInterpolate() { return _animation->GetInterpolate(); }

	public:
		void SetAdditionalModel(Model* model) { _models.push_back(model); }
		void SetAdditionalChildObject(DXObject* child) { _childObjectList.push_back(child); child->_parent = this; }
		void SetAnimation(Animation* animation) { _animation = animation; }
		void SetVertexShader(Shader* shader) { _vs = shader; }
		void SetPixelShader(Shader* shader) { _ps = shader; }
		void UpdateCurrentAnimation(std::string name);
		HMatrix44 GetMatrix();
		void UpdatePosition(Vector3 vec);
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
