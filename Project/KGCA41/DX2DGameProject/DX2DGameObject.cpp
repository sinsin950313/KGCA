#include "DX2DGameObject.h"
#include "Rectangle.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "DXCore.h"

namespace SSB
{
	extern DXCore* g_DXCore;

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

	void DX2DGameObject::RiseUp()
	{
		if (_flightStatus != EFlightStatus::RISE)
		{
			_flightStatus = EFlightStatus::RISE;
			_lastRiseTime = g_DXCore->GetGlobalTime();
		}
	}

	void DX2DGameObject::ParallelTranslation()
	{
		_flightStatus = EFlightStatus::NONE;
	}

	void DX2DGameObject::FallDown()
	{
		if (_flightStatus != EFlightStatus::FALL)
		{
			_flightStatus = EFlightStatus::FALL;
			_lastFallTime = g_DXCore->GetGlobalTime();
		}
	}

	bool DX2DGameObject::Init()
	{
		_dxObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "main", "vs_5_0"));
		_dxObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "withMask", "ps_5_0"));
		//_dxObject->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"bitmap1", DXStateManager::kDefaultSolidRasterizer));
		//_dxObject->SetMaskSprite(TextureResourceManager::GetInstance().Load(L"bitmap2.bmp"));
		_dxObject->Init();

		return true;
	}

	bool DX2DGameObject::Frame()
	{
		_dxObject->Frame();

		if (_flightStatus == EFlightStatus::RISE)
		{
			if (_elevationTravelTime < g_DXCore->GetGlobalTime() - _lastRiseTime)
			{
				++_currentLayer;
				_lastRiseTime = g_DXCore->GetGlobalTime();
			}
		}
		if (_flightStatus == EFlightStatus::FALL)
		{
			if (_elevationTravelTime < g_DXCore->GetGlobalTime() - _lastFallTime)
			{
				--_currentLayer;
				_lastFallTime = g_DXCore->GetGlobalTime();
			}
		}

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
