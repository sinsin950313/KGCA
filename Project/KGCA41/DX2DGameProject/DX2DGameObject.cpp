#include "DX2DGameObject.h"
#include "Rectangle.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DXStateManager.h"
#include "DXCore.h"
#include "DX2DCamera.h"

namespace SSB
{
	extern DXCore* g_DXCore;
	extern DXWindow* g_dxWindow;
	extern DX2DCamera* g_Camera;
	extern bool g_Debug;

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
		_dxObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		_dxObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));
		//_dxObject->SetSprite(SpriteLoader::GetInstance().Load(L"bitmap1.bmp", L"bitmap1", DXStateManager::kDefaultSolidRasterizer));
		//_dxObject->SetMaskSprite(TextureResourceManager::GetInstance().Load(L"bitmap2.bmp"));
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
		g_dxWindow->AddDrawable(GetDXObject());

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

	int DX2DGameObject::GetHitboxIndex(EAireplaneFlightState flightState)
	{
		return (int)flightState;
	}

	DX2DHitBox::DX2DHitBox(Position2D center, float width, float height, float mass) : DX2DGameObject(center, width, height, mass)
	{
	}

	DX2DHitBox::~DX2DHitBox()
	{
	}

	void DX2DHitBox::SetRelativePosition(HitboxPosition* position)
	{
		_relativePosition = position;
	}

	void DX2DHitBox::SetParent(DX2DGameObject* parent)
	{
		_parent = parent;
	}

	bool DX2DHitBox::Init()
	{
		GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"HitBoxDebug.hlsl", "Debug", "ps_5_0"));
		SpriteLoader::GetInstance().RegisterSpriteFromFile(L"Target.bmp", L"Target");
		GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"Target.bmp", L"Target1", DXStateManager::kDefaultWrapSample));
		GetDXObject()->Init();

		return true;
	}

	bool DX2DHitBox::Frame()
	{
		DX2DGameObject::Frame();
		Vector2D position = _parent->GetCenter() + _relativePosition->rectangle.GetCenter();
		GetPhysicsObject()->GetVolume()->Reposition(position);
		g_Camera->MontageForFilm(this);

		return true;
	}

	bool DX2DHitBox::Render()
	{
		if (g_Debug)
		{
			DX2DGameObject::Render();
		}

		return true;
	}

	bool DX2DHitBox::Release()
	{
		_parent = nullptr;
		_relativePosition = nullptr;

		return true;
	}

	DX2DInGameObject::DX2DInGameObject(Position2D center, float width, float height, float mass) : DX2DGameObject(center, width, height, mass)
	{
		for (int i = 0; i < hitboxCount; ++i)
		{
			_hitBox[i] = new DX2DHitBox(center, width / 2, height / 2, mass);
		}

		int layerIndex[9]{ 0, 1, -1, 0, 0, 1, -1, 1, -1 };
		int horizontalDirectionIndex[9]{ 0, 0, 0, -1, 1, -1, -1, 1, 1 };

		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < hitboxCount; ++j)
			{
				_hitBoxData[i][j] = new HitboxPosition{ layerIndex[i] * (j / 3), Rectangle(horizontalDirectionIndex[i] * (width / 2 * (j / 3) + (width / 2 / 2)), height / 2 * (j + 1) + (height / 2 / 2), width / 2, height / 2)};
			}
		}

		_dxTargetedObject = new DX2DObject(center, width, height);
	}

	void DX2DInGameObject::FlightStateChangeOrder(EAireplaneFlightState state)
	{
		if (_flightStateChangeOrder != state)
		{
			_flightStateChangeOrder = state;
			_stateTransitionLastTime = g_DXCore->GetGlobalTime();
		}
	}

	void DX2DInGameObject::Targeted()
	{
		if (!_targeted)
		{
			_targeted = true;
			_lastTargetedTime = g_DXCore->GetGlobalTime();
		}
	}

	bool DX2DInGameObject::IsHit()
	{
		if (_targeted && _aimmingTime < g_DXCore->GetGlobalTime() - _lastTargetedTime)
		{
			_lastTargetedTime = g_DXCore->GetGlobalTime();
			return true;
		}
		return false;
	}

	bool DX2DInGameObject::Init()
	{
		DX2DGameObject::Init();

		for (int i = 0; i < hitboxCount; ++i)
		{
			_hitBox[i]->SetParent(this);
			_hitBox[i]->Init();
		}

		_dxTargetedObject->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		_dxTargetedObject->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"HitBoxDebug.hlsl", "Main", "ps_5_0"));
		SpriteLoader::GetInstance().RegisterSpriteFromFile(L"Target.bmp", L"Target");
		_dxTargetedObject->SetSprite(SpriteLoader::GetInstance().Load(L"Target.bmp", L"Target1", DXStateManager::kDefaultWrapSample));
		_dxTargetedObject->Init();

		return true;
	}

	bool DX2DInGameObject::Frame()
	{
		DX2DGameObject::Frame();

		if (_currentFlightState != _flightStateChangeOrder)
		{
			if (_stateTransitionRequiredTime < g_DXCore->GetGlobalTime() - _stateTransitionLastTime)
			{
				_currentFlightState = _flightStateChangeOrder;
			}
		}

		if (_currentFlightState == _flightStateChangeOrder)
		{
			if (_stateTransitionRequiredTime < g_DXCore->GetGlobalTime() - _stateTransitionLastTime)
			{
				_stateTransitionLastTime = g_DXCore->GetGlobalTime();

				if ((_currentFlightState == EAireplaneFlightState::TOP)
					|| (_currentFlightState == EAireplaneFlightState::LEFT_TOP)
					|| (_currentFlightState == EAireplaneFlightState::RIGHT_TOP))
				{
					++_currentLayer;
				}

				if ((_currentFlightState == EAireplaneFlightState::BOTTOM)
					|| (_currentFlightState == EAireplaneFlightState::LEFT_BOTTOM)
					|| (_currentFlightState == EAireplaneFlightState::RIGHT_BOTTOM))
				{
					--_currentLayer;
				}
			}
		}
		
		for (int i = 0; i < hitboxCount; ++i)
		{
			_hitBox[i]->SetRelativePosition(_hitBoxData[(int)_currentFlightState][i]);
			_hitBox[i]->Frame();
		}

		_dxTargetedObject->Move(GetDXObject()->GetCenter());
		_dxTargetedObject->Resize(GetDXObject()->GetWidth(), GetDXObject()->GetHeight());
		_dxTargetedObject->Frame();

		return true;
	}

	bool DX2DInGameObject::Render()
	{
		DX2DGameObject::Render();

		for (int i = 0; i < hitboxCount; ++i)
		{
			_hitBox[i]->Render();
		}

		if (_targeted)
		{
			g_dxWindow->AddDrawable(_dxTargetedObject);
		}

		return true;
	}

	bool DX2DInGameObject::Release()
	{
		DX2DGameObject::Release();

		for (int i = 0; i < hitboxCount; ++i)
		{
			_hitBox[i]->Release();
			delete _hitBox[i];
		}

		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < hitboxCount; ++j)
			{
				delete _hitBoxData[i][j];
				_hitBoxData[i][j] = nullptr;
			}
		}

		if (_dxTargetedObject)
		{
			_dxTargetedObject->Release();
			delete _dxTargetedObject;
			_dxTargetedObject = nullptr;
		}

		return true;
	}
}
