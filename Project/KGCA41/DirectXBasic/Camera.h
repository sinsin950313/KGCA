#pragma once

#include "Common.h"
#include "Matrix.h"
#include "Vector.h"
#include "DXObject.h"

namespace SSB
{
	enum class ECollideState { In, Cross, Out };
	class Camera : public Common
	{
	private:
		float _fov;
		float _aspect;
		float _near;
		float _far;

	protected:
		HMatrix44 _matrix;

	public:
		Camera();

	private:
		void GetPlane(Float4 ret[6]);

	public:
		HMatrix44 GetProjectionMatrix();
		//void LookAt(Vector3 target);
		//void LookAt(DXObject* target);
		//// Wait for Quaternion
		////void LookAt(float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f);
		void SetPosition(Vector3 position);
		HMatrix44 GetMatrix() { return _matrix; }
		bool IsRender(DXObject* object);
		ECollideState GetCollideState(OBB data);

	public:
		virtual HMatrix44 GetViewMatrix();
		virtual void Move(Vector3 to);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class DebugCamera : public Camera
	{
	public:
		void Move(float deltaZ, float deltaX);
		void Rotate(float yaw, float pitch = 0.0f);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class ModelViewCamera : public Camera
	{
	private:
		DXObject _vTarget;
		DXObject* _target;

		float _rotXTotal = 0;
		float _rotYTotal = 0;

	public:
		ModelViewCamera();

	public:
		//void Move(float deltaZ, float deltaX);
		//void Rotate(float yaw, float pitch = 0.0f);
		void SetTarget(DXObject* target);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Move(Vector3 to) override;
		HMatrix44 GetViewMatrix() override;
	};
}
