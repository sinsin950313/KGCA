#include "DX2DGameObject.h"
#include "Rectangle.h"
#include "TextureManager.h"
#include "ShaderManager.h"

namespace SSB
{
	DX2DGameObject::DX2DGameObject(Position2D center, float width, float height, float mass)
	{
		_physicsObject = new Object2D(new Rectangle(center.x, center.y, width, height), Rigidbody2D(mass));
		_dxObject = new DX2DObject(center, width, height);
	}

	DX2DGameObject::~DX2DGameObject()
	{
		Release();
	}

	void DX2DGameObject::Move(float x, float y)
	{
		Vector2D pos(Vector2DData{ x, y });
		Move(pos);
	}

	void DX2DGameObject::Move(Vector2D center)
	{
		_physicsObject->GetVolume()->Reposition(center);
	}

	bool DX2DGameObject::Init()
	{
		_dxObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
		_dxObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
		_dxObject->SetTexture(TextureManager::GetInstance().Load(L"bitmap1.bmp"));
		_dxObject->SetMaskTexture(TextureManager::GetInstance().Load(L"bitmap2.bmp"));
		_dxObject->Init();
		return true;
	}

	bool DX2DGameObject::Frame()
	{
		_dxObject->Frame();

		return true;
	}

	bool DX2DGameObject::Render()
	{
		_dxObject->Render();

		return true;
	}

	bool DX2DGameObject::Release()
	{
		if (_dxObject)
		{
			_dxObject->Release();
			delete _dxObject;
			_dxObject = nullptr;
		}

		if (_physicsObject)
		{
			delete _physicsObject;
			_physicsObject = nullptr;
		}

		return true;
	}
}
