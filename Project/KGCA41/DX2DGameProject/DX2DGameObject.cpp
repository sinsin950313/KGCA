#include "DX2DGameObject.h"
#include "Rectangle.h"

DX2DGameObject::DX2DGameObject(Position2D center, float width, float height, float mass)
{
	_physicsObject = new Object2D(new Custom::Rectangle(center.x, center.y, width, height), Rigidbody2D(mass));
	_dxObject = new TDX2DObject(center, width, height);
}

DX2DGameObject::~DX2DGameObject()
{
	Release();
}

void DX2DGameObject::Move(float x, float y)
{
	Vector2D pos(Vector2DData{x, y});
	Move(pos);
}

void DX2DGameObject::Move(Vector2D center)
{
	_physicsObject->GetVolume()->Reposition(center);
}

bool DX2DGameObject::Init()
{
	return true;
}

bool DX2DGameObject::Frame()
{
	return true;
}

bool DX2DGameObject::Render()
{
	_dxObject->Render();

	return true;
}

bool DX2DGameObject::Release()
{
	delete _dxObject;
	_dxObject = nullptr;

	delete _physicsObject;
	_physicsObject = nullptr;

	return true;
}
