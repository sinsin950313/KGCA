#pragma once

#include "Common.h"
#include "DX2DObject.h"
#include "Object.h"
#include "Rectangle.h"

namespace SSB
{
	enum class EAireplaneFlightState { STRAIGHT = 0, TOP, BOTTOM, LEFT, RIGHT, LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM };

	constexpr int hitboxCount = 9;
	struct HitboxPosition
	{
		int layer;
		Rectangle rectangle;
	};

	class DX2DGameObject : public Common
	{
	private:
		DX2DObject* _dxObject;
		Object2D* _physicsObject;

	public:
		DX2DGameObject(Position2D center, float width, float height, float mass);
		~DX2DGameObject();

	public:
		DX2DObject* GetDXObject() { return _dxObject; }
		Object2D* GetPhysicsObject() { return _physicsObject; }
		Vector2D GetCenter() { return _physicsObject->GetVolume()->GetCenter(); }
		void Move(float x, float y);
		void Move(Vector2D center);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	private:
		int GetHitboxIndex(EAireplaneFlightState flightState);
	};

	class DX2DHitBox : public DX2DGameObject
	{
	private:
		DX2DGameObject* _parent;
		HitboxPosition* _relativePosition;

	public:
		DX2DHitBox(Position2D center, float width, float height, float mass);
		~DX2DHitBox();

	public:
		void SetRelativePosition(HitboxPosition* position);
		void SetParent(DX2DGameObject* parent);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class DX2DInGameObject : public DX2DGameObject
	{
	private:
		int _currentLayer;
		EAireplaneFlightState _currentFlightState = EAireplaneFlightState::STRAIGHT;
		const DWORD _stateTransitionRequiredTime = 100;
		EAireplaneFlightState _flightStateChangeOrder = EAireplaneFlightState::STRAIGHT;
		DWORD _stateTransitionLastTime;

		DX2DHitBox* _hitBox[hitboxCount];
		HitboxPosition* _hitBoxData[9][hitboxCount];

	public:
		DX2DInGameObject(Position2D center, float width, float height, float mass);

	public:
		void SetCurrentLayer(int layer) { _currentLayer = layer; }
		int GetCurrentMapLayer() { return _currentLayer; }
		void FlightStateChangeOrder(EAireplaneFlightState state);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
