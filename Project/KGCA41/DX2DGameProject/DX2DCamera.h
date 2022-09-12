#pragma once

#include "DX2DGameObject.h"
#include "PhysicsVector.h"

class DX2DCamera : public DX2DGameObject
{
public:
	Position2D PhysicsToDisplay(Vector2D pos);
};

