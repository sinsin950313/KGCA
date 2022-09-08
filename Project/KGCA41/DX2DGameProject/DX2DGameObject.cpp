#include "DX2DGameObject.h"

DX2DGameObject::DX2DGameObject()
{
	_dxObject = new TDX2DObject();
	_physicsObject = new Object2D();
}

DX2DGameObject::~DX2DGameObject()
{
	Release();
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
