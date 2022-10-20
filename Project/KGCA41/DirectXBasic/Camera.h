#pragma once

#include "Common.h"
#include "Matrix.h"
#include "Vector.h"
#include "DXObject.h"

namespace SSB
{
	class Camera : public Common
	{
	private:
		float _fov;
		float _aspect;
		float _near;
		float _far;
		DXObject _vTarget;
		DXObject* _target;

	protected:
		HMatrix44 _matrix;

	public:
		Camera();

	public:
		HMatrix44 GetViewMatrix();
		HMatrix44 GetProjectionMatrix();
		//void LookAt(Vector3 target);
		//void LookAt(DXObject* target);
		//// Wait for Quaternion
		////void LookAt(float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f);
		void Move(Vector3 to);
		//void SetPosition(Vector3 position);
		DXObject* GetTarget() { return _target; }
		HMatrix44 GetMatrix() { return _matrix; }

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

	//class ModelViewCamera : public Camera
	//{
	//public:
	//	bool Init() override;
	//	bool Frame() override;
	//	bool Render() override;
	//	bool Release() override;
	//};
}
