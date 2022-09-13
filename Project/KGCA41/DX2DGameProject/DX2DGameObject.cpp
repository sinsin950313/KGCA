#include "DX2DGameObject.h"
#include "Rectangle.h"
#include "DX2DCamera.h"
#include <float.h>

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

void DX2DGameObject::CalculateDXPosition(DX2DCamera* camera)
{
	auto center = camera->PhysicsToDisplay(_physicsObject->GetVolume()->GetCenter());
	_dxObject->Move(center);

	auto vertice = _physicsObject->GetVolume()->GetVertexes();
	float minX = FLT_MAX;
	float maxX = FLT_MIN;
	float minY = FLT_MAX;
	float maxY = FLT_MIN;
	for (auto vertex : vertice)
	{
		minX = std::fmin(minX, vertex->Get(0));
		maxX = std::fmax(maxX, vertex->Get(0));
		minY = std::fmin(minY, vertex->Get(1));
		maxY = std::fmax(maxY, vertex->Get(1));
	}

	float tmpWidth = maxX - minX;
	float tmpHeight = maxY - minY;

	tmpWidth = tmpWidth / _camera->GetWidth() * _camera->GetClientWidth();
	tmpHeight = tmpHeight / _camera->getHeight() * _camera->GetClientHeight();

	_dxObject->Resize(tmpWidth, tmpHeight);

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
