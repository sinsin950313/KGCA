#pragma once

#include "CommonClass.h"
#include "TDX2DObject.h"
#include "Object.h"

class DX2DGameObject : public Common
{
private:
	TDX2DObject* _dxObject;
	Object2D* _physicsObject;

public:
	DX2DGameObject(Position2D center, float width, float height, float mass);
	~DX2DGameObject();

public:
	TDX2DObject* GetDXObject() { return _dxObject; }
	Object2D* GetPhysicsObject() { return _physicsObject; }
	Vector2D GetCenter() { return _physicsObject->GetVolume()->GetCenter(); }
	void Move(float x, float y);
	void Move(Vector2D center);

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
