#include "Camera.h"
#include "BasicWindow.h"

namespace SSB
{
	extern BasicWindow* g_Window;

	Camera::Camera()
	{
	}
	HMatrix44 Camera::GetViewMatrix()
	{
		//return HMatrix44::LookAtMatrix({ 0, 0, -10 }, { 0, 0, 0, }, { 0, 1, 0 }).Inverse();
		return _matrix.Inverse();
	}
	HMatrix44 Camera::GetProjectionMatrix()
	{
		HMatrix44 perspective;
		{
			float    h, w, Q;
			float fNearPlane = 1.0f;
			float fFarPlane = 100.0f;
			float fovy = 3.141592f * 0.5f;
			float Aspect = ((float)g_Window->GetClientWidth()) / g_Window->GetClientHeight();

			h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
			w = h / Aspect;

			Q = fFarPlane / (fFarPlane - fNearPlane);

			HMatrix44 ret
			{
				w, 0, 0, 0,
				0, h, 0, 0,
				0, 0, Q, 1,
				0, 0, -Q * fNearPlane, 0
			};

			memcpy(&perspective, &ret, sizeof(HMatrix44));
		}
		return perspective;
	}
	void Camera::Move(Vector3 to)
	{
		_matrix = _matrix * HMatrix44(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			to.GetX(), to.GetY(), to.GetZ(), 1
		);
	}
	bool Camera::Init()
	{
		return false;
	}
	bool Camera::Frame()
	{
		return false;
	}
	bool Camera::Render()
	{
		return false;
	}
	bool Camera::Release()
	{
		return false;
	}

	void DebugCamera::Move(float deltaZ, float deltaX)
	{
		Camera::Move(Vector3(deltaX, 0, deltaZ));
	}
	void DebugCamera::Rotate(float yaw, float pitch)
	{
		_matrix = _matrix * HMatrix44::RotateFromYAxis(yaw);
	}
	bool DebugCamera::Init()
	{
		return false;
	}
	bool DebugCamera::Frame()
	{
		return false;
	}
	bool DebugCamera::Render()
	{
		return false;
	}
	bool DebugCamera::Release()
	{
		return false;
	}
}
