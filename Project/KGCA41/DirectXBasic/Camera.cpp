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
	void Camera::GetPlane(Float4 ret[6])
	{
		//float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -100.0f, -100.0f, 100.0f, 100.0f };
		//float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f, -100.0f, 100.0f };
		//float dz[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 100.0f, 100.0f, 100.0f, 100.0f };

		float dx[8] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f };
		float dy[8] = { -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f };
		float dz[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };

		HMatrix44 projectionMatrix = GetProjectionMatrix();
		Matrix44* matrix = (Matrix44*)&projectionMatrix;
		Matrix44 invMatrix = matrix->Inverse();
		HMatrix44 invProjMatrix = *(HMatrix44*)&invMatrix;

		HVector4 frustum[8];
		for (int i = 0; i < 8; ++i)
		{
			frustum[i] = { dx[i], dy[i], dz[i] ,1.0f };
			frustum[i] = frustum[i] * invProjMatrix * GetViewMatrix().Inverse();
			frustum[i].Normalize();
			//frustum[i] = frustum[i] * GetViewMatrix().Inverse();
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
		{
			ret[0] = makePlane(frustum[0], frustum[1], frustum[2]);
			ret[1] = makePlane(frustum[4], frustum[5], frustum[0]);
			ret[2] = makePlane(frustum[6], frustum[7], frustum[4]);
			ret[3] = makePlane(frustum[2], frustum[3], frustum[6]);
			ret[4] = makePlane(frustum[1], frustum[5], frustum[3]);
			ret[5] = makePlane(frustum[4], frustum[0], frustum[6]);
		}
	}
	ECollideState Camera::GetCollideState(OBB data)
	{
		Float4 planes[6];
		GetPlane(planes);

		ECollideState state = ECollideState::In;
		for (int i = 0; i < 6; ++i)
		{
			float distance = 0.0f;
			Vector3 tmp = data.Matrix.GetRow(0);
			Vector3 dir = tmp * data.Width / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			tmp = data.Matrix.GetRow(1);
			dir = tmp * data.Height / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			tmp = data.Matrix.GetRow(2);
			dir = tmp * data.Depth / 2.0f;
			distance += abs(dir.GetX() * planes[i].x + dir.GetY() * planes[i].y + dir.GetZ() * planes[i].z);

			Vector3 center = data.Matrix.GetRow(3);
			float cDistance = center.GetX() * planes[i].x + center.GetY() * planes[i].y + center.GetZ() * planes[i].z + planes[i].w;

			if (cDistance < 0)
			{
				// In State
				if (cDistance + distance > 0)
				{
					state = ECollideState::Cross;
				}
			}
			else
			{
				// Out State
				if (cDistance - distance <= 0)
				{
					state = ECollideState::Cross;
				}
				else
				{
					return ECollideState::Out;
				}
			}
		}

		return state;
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
	void Camera::SetPosition(Vector3 position)
	{
		Matrix33 rot = _matrix;
		_matrix = HMatrix44(rot, position);
	}
	bool Camera::IsRender(DXObject* object)
	{
		OBB obbData = object->GetOBB();
		if (GetCollideState(obbData) == ECollideState::Out)
		{
			return false;
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
		float rotCoeff = 0.0001f;
		if (InputManager::GetInstance().GetKeyState(VK_SPACE) == EKeyState::KEY_HOLD)
		{
			coeff *= 100;
		}
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
        if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
        {
			rotY += (InputManager::GetInstance().GetDeltaPosition().x * rotCoeff * 10.0f);
			rotX += (InputManager::GetInstance().GetDeltaPosition().y * rotCoeff * 10.0f);
        }
		if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
		{
			rotY += 10.0f * rotCoeff;
		}
		if (InputManager::GetInstance().GetKeyState('E') == EKeyState::KEY_HOLD)
		{
			rotY -= 10.0f * rotCoeff;
		}
		if (InputManager::GetInstance().GetKeyState('Z') == EKeyState::KEY_HOLD)
		{
			rotX += 10.0f * rotCoeff;
		}
		if (InputManager::GetInstance().GetKeyState('X') == EKeyState::KEY_HOLD)
		{
			rotX -= 10.0f * rotCoeff;
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
