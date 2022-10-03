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

	protected:
		virtual void PreInit() { }
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
		int GetRelativeLayer() { return _relativePosition->layer; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	enum class EXAxis { STEADY = 0, LEFT, RIGHT };
	enum class EYAxis { STEADY = 0, TOP, BOTTOM};
	enum class EZAxis { STEADY = 0, ACCELERATE, DECELERATE };

	class DX2DInGameObject : public DX2DGameObject
	{
	private:
		int _currentLayer;
		EAireplaneFlightState _flightStateChangeOrder = EAireplaneFlightState::STRAIGHT;
		EAireplaneFlightState _currentFlightState = EAireplaneFlightState::STRAIGHT;
		const DWORD _stateTransitionRequiredTime = 300;
		DWORD _stateTransitionLastTime;

		DX2DHitBox* _hitBox[hitboxCount];
		HitboxPosition* _hitBoxData[9][hitboxCount];
		DX2DObject* _dxTargetedObject;
		bool _targeted = false;
		const DWORD _aimmingTime = 100;
		DWORD _lastTargetedTime;

		EXAxis _xAxis;
		EYAxis _yAxis;
		EZAxis _zAxis;
		float _velocity = 0.1f;

	public:
		DX2DInGameObject(Position2D center, float width, float height, float mass);

	private:
		void FlightStateChangeOrder(EXAxis xAxis, EYAxis yAxis, EZAxis zAxis);
		void FlightStateChangeOrder(EAireplaneFlightState state);

	public:
		void FlightAccelerateDirection(EXAxis xAxis, EYAxis yAxis, EZAxis zAxis);
		void SetCurrentLayer(int layer) { _currentLayer = layer; }
		int GetCurrentMapLayer() { return _currentLayer; }
		void Targeted();
		void UnTargeted() { _targeted = false; }
		bool IsHit();
		DX2DHitBox** GetHitBoxData() { return _hitBox; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void PreInit() override;
	};

	//class DX2DHitEffect : public DX2DGameObject
	//{
	//public:
	//	DX2DHitEffect(Position2D center, float width, float height);

	//public:
	//	void Action();

	//public:
	//	bool Init() override;
	//	bool Frame() override;
	//	bool Render() override;
	//	bool Release() override;
	//	void PreInit() override;
	//};
}
