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
	DX2DGameObject();
	~DX2DGameObject();

public:
	TDX2DObject* GetDXObject() { return _dxObject; }
	Object2D* GetPhysicsObject() { return _physicsObject; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
