#include "Camera.h"
#include "BasicWindow.h"
#include "InputManager.h"

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
		float    h, w, Q;
		float fNearPlane = 1.0f;
		float fFarPlane = 100.0f;
		float fovy = 3.141592f * 0.5f;
		float Aspect = ((float)g_Window->GetClientWidth()) / g_Window->GetClientHeight();

		h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
		w = h / Aspect;

		Q = fFarPlane / (fFarPlane - fNearPlane);

		HMatrix44 perspective
		{
			w, 0, 0, 0,
			0, h, 0, 0,
			0, 0, Q, 1,
			0, 0, -Q * fNearPlane, 0
		};
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
		Vector3 xVector = _matrix.GetRow(0);
		Vector3 zVector = _matrix.GetRow(2);
		auto dir = (xVector * deltaX) + (zVector * deltaZ);
		Camera::Move(dir);
	}
	void DebugCamera::Rotate(float yaw, float pitch)
	{
		static float sYaw = 0.0f;

		HMatrix44 tMatrix;
		tMatrix = tMatrix.Translate(_matrix.GetRow(3));
		_matrix = _matrix * tMatrix.Inverse() * HMatrix44::RotateFromYAxis(-sYaw) * HMatrix44::RotateFromXAxis(pitch) * HMatrix44::RotateFromYAxis(sYaw) * tMatrix;

		sYaw += yaw;
		_matrix = _matrix * tMatrix.Inverse() * HMatrix44::RotateFromYAxis(yaw) * tMatrix;
	}
	bool DebugCamera::Init()
	{
		return false;
	}
	bool DebugCamera::Frame()
	{
		Float3 vPos{ 0, 10, 0 };
        float rotX = 0;
        float rotY = 0;
		float coeff = 0.0001f;
		if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			vPos.z += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			vPos.z -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			vPos.x -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			vPos.x += 10.0f * coeff;
		}
   //     if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
   //     {
   //         POINT delta = InputManager::GetInstance().GetDeltaPosition();
			//rotX += ((float)delta.x * 0.01f);
   //         rotY += ((float)delta.y * 0.01f);

			//static float cDx = 0.0f;
			//cDx += delta.x;
			//OutputDebugString((L"cDx : " + std::to_wstring(cDx) + L"\n").c_str());
   //     }
		if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
		{
			rotY += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('E') == EKeyState::KEY_HOLD)
		{
			rotY -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('Z') == EKeyState::KEY_HOLD)
		{
			rotX += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('X') == EKeyState::KEY_HOLD)
		{
			rotX -= 10.0f * coeff;
		}

        Move(vPos.z, vPos.x);
        Rotate(rotY, rotX);
        //Rotate(0.0001f, rotX);

		return true;
	}
	bool DebugCamera::Render()
	{
		return false;
	}
	bool DebugCamera::Release()
	{
		return false;
	}

	ModelViewCamera::ModelViewCamera()
	{
		_matrix = _matrix * HMatrix44{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, -1, 1
		};
	}
	void ModelViewCamera::Move(Vector3 to)
	{
		_matrix = HMatrix44::LookAtMatrix(to, { 0, 0, 0 }, { 0, 1, 0 });
	}
	//void ModelViewCamera::Move(float deltaZ, float deltaX)
	//{
	//	Vector3 xVector = _matrix.GetRow(0);
	//	Vector3 zVector = _matrix.GetRow(2);
	//	auto dir = (xVector * deltaX) + (zVector * deltaZ);
	//	Camera::Move(dir);
	//}
	void ModelViewCamera::Rotate(float yaw, float pitch)
	{
		static float sYaw = 0.0f;

		_matrix = _matrix * HMatrix44::RotateFromYAxis(-sYaw) * HMatrix44::RotateFromXAxis(pitch) * HMatrix44::RotateFromYAxis(sYaw) * HMatrix44::RotateFromYAxis(yaw);

		sYaw += yaw;
	}
	void ModelViewCamera::SetTarget(DXObject* target)
	{
		_target = target;
	}
	HMatrix44 ModelViewCamera::GetViewMatrix()
	{
		return _target->GetMatrix().Inverse() * _matrix.Inverse();
	}
	bool ModelViewCamera::Init()
	{
		return false;
	}
	bool ModelViewCamera::Frame()
	{
        float rotX = 0;
        float rotY = 0;
		float coeff = 0.0001f;
		if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			rotX += 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			rotX -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			rotY -= 10.0f * coeff;
		}
		if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			rotY += 10.0f * coeff;
		}
		Rotate(rotY, rotX);
		return false;
	}
	bool ModelViewCamera::Render()
	{
		return false;
	}
	bool ModelViewCamera::Release()
	{
		return false;
	}
}
