#include "Camera.h"
#include "BasicWindow.h"
#include "InputManager.h"
#include "HCCalculator.h"

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
		float fFarPlane = 1000.0f;
		float fovy = 3.141592f * 0.25;
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
		return true;
	}
	bool Camera::Frame()
	{
		return true;
	}
	bool Camera::Render()
	{
		return false;
	}
	bool Camera::Release()
	{
		return false;
	}
	bool Camera::IsRender(DXObject* object)
	{
		float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -50.0f, -50.0f, 50.0f, 50.0f };
		float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -50.0f, 50.0f, -50.0f, 50.0f };
		float dz[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 100.0f, 100.0f, 100.0f, 100.0f };
		//float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
		//float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f };
		//float dz[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		HVector4 frustum[8];
		for (int i = 0; i < 8; ++i)
		{
			frustum[i] = { dx[i], dy[i], dz[i] ,1.0f };
			//frustum[i] = frustum[i] * GetProjectionMatrix().Inverse() * GetViewMatrix().Inverse();
			frustum[i] = frustum[i] * GetViewMatrix().Inverse();
		}

		auto makePlane = [](HVector4 a, HVector4 b, HVector4 c) -> Float4
		{
			Vector3 v1 = { b.GetX() - a.GetX(), b.GetY() - a.GetY(), b.GetZ() - a.GetZ() };
			v1.Normalize();
			Vector3 v2 = { c.GetX() - a.GetX(), c.GetY() - a.GetY(), c.GetZ() - a.GetZ() };
			v2.Normalize();
			Vector3 normal = v1.Cross(v2);
			normal.Normalize();
			float d = -(normal.GetX() * a.GetX() + normal.GetY() * a.GetY() + normal.GetZ() * a.GetZ());
			return { normal.GetX(), normal.GetY(), normal.GetZ(), d };
		};
		Float4 planes[6];
		{
			planes[0] = makePlane(frustum[0], frustum[1], frustum[2]);
			planes[1] = makePlane(frustum[4], frustum[5], frustum[0]);
			planes[2] = makePlane(frustum[6], frustum[7], frustum[4]);
			planes[3] = makePlane(frustum[2], frustum[3], frustum[6]);
			planes[4] = makePlane(frustum[1], frustum[5], frustum[3]);
			planes[5] = makePlane(frustum[4], frustum[0], frustum[6]);
		}

		OBB obbData = object->GetOBB();
		for (int i = 0; i < 6; ++i)
		{
			float distance = 0.0f;
			Vector3 tmp = obbData.Matrix.GetRow(0);
			Vector3 dir = tmp * obbData.Width / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			tmp = obbData.Matrix.GetRow(1);
			dir = tmp * obbData.Height / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			tmp = obbData.Matrix.GetRow(2);
			dir = tmp * obbData.Depth / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			Vector3 center = obbData.Matrix.GetRow(3);
			float cDistance = center.GetX() * planes[i].x + center.GetY() * planes[i].y + center.GetZ() * planes[i].z + planes[i].w;

			if (cDistance - distance > 0)
			{
				return false;
			}
		}

		return true;
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
		Camera::Init();
		return false;
	}
	bool DebugCamera::Frame()
	{
		Camera::Frame();
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
		Camera::Render();
		return false;
	}
	bool DebugCamera::Release()
	{
		Camera::Release();
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
		Camera::Init();
		return false;
	}
	bool ModelViewCamera::Frame()
	{
		Camera::Frame();
        float rotX = 0;
        float rotY = 0;
		float coeff = 0.0001f;
		//if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		//{
		//	rotX += 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		//{
		//	rotX -= 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		//{
		//	rotY -= 10.0f * coeff;
		//}
		//if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		//{
		//	rotY += 10.0f * coeff;
		//}
		if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
		{
			rotY += InputManager::GetInstance().GetDeltaPosition().x * coeff * 10;
			//rotX += InputManager::GetInstance().GetDeltaPosition().y * coeff * 10;
		}
		if (rotX != 0 || rotY != 0)
		{
			Vector3 rotVector = HVector4{ 0, 0, -1 } * HMatrix44::RotateFromYAxis(rotY) * HMatrix44::RotateFromXAxis(rotX);
			Quaternion quat = Quaternion::GetRotateQuaternion({ 0, 0, -1 }, rotVector);
			Matrix33 mat = quat.GetRotateMatrix();
			_matrix = _matrix * HMatrix44{ mat, Vector3{0, 0, 0} };
		}
		//Rotate(rotY, rotX);
		return false;
	}
	bool ModelViewCamera::Render()
	{
		Camera::Render();
		return false;
	}
	bool ModelViewCamera::Release()
	{
		Camera::Release();
		return false;
	}
}
