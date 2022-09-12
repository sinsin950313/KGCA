#include "DX2DMapObject.h"
#include "CollisionTree.h"
#include "DX2DGameObject.h"

DX2DMapObject::DX2DMapObject(Position2D pos, float width, float height)
{
	_dxObject = new TDX2DObject(pos, width, height);

	int maxLayer = 0;
	float wTmp = width;
	float hTmp = height;
	while (wTmp / 2 < 2 || hTmp / 2 < 2)
	{
		++maxLayer;
		wTmp /= 2;
		hTmp /= 2;
	}
	_qt = new QuadTree(width, height, maxLayer);
}

DX2DMapObject::~DX2DMapObject()
{
	_dxObject->Release();

	delete _qt;

	_physicsToDX2DMatch.clear();

	Release();
}

std::vector<DX2DGameObject*> DX2DMapObject::GetCollideObjectList(DX2DGameObject* object)
{
	std::vector<DX2DGameObject*> collidedObjectList;

	auto collidePhysicsObjectList = _qt->GetCollidedObjects(object->GetPhysicsObject());
	for (auto physicsObject : collidePhysicsObjectList)
	{
		collidedObjectList.push_back(_physicsToDX2DMatch.find(physicsObject)->second);
	}

	return collidedObjectList;
}

bool DX2DMapObject::IsCollide(DX2DGameObject* object)
{
	return !_qt->GetCollidedObjects(object->GetPhysicsObject()).empty();
}

bool DX2DMapObject::Init()
{
	return true;
}

bool DX2DMapObject::Frame()
{
	return true;
}

bool DX2DMapObject::Render()
{
	_dxObject->Render();
	return true;
}

bool DX2DMapObject::Release()
{
	delete _qt;

	_dxObject->Release();
	delete _dxObject;

	return true;
}
