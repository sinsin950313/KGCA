#include "DX2DCamera.h"
#include "TDXWindow.h"
#include "PhysicsVector.h"

extern TDXWindow* g_dxWindow;

DX2DCamera::DX2DCamera(Vector2D center, float physicsWidth, float physicsHeight) : _physicsArea(center.Get(0), center.Get(1), physicsWidth, physicsHeight)
{
}

Position2D DX2DCamera::PhysicsToDisplay(Vector2D absolute)
{
	Vector2D relative = absolute - _physicsArea.GetCenter();
	Vector2D halfPhysicsArea{ _physicsArea.GetWidth() / 2, -_physicsArea.GetHeight() / 2 };
	Vector2D physicsInScreen = relative + halfPhysicsArea;
	Vector2D NDCByPIS{ physicsInScreen.Get(0) / _physicsArea.GetWidth(), physicsInScreen.Get(1) / _physicsArea.GetHeight() };
	Position2D screenCoor{ NDCByPIS.Get(0) * _windowWidth, NDCByPIS.Get(1) * _windowHeight };
	return screenCoor;
}

void DX2DCamera::Move(float x, float y)
{
	Vector2D pos(Vector2DData{x, y});
	Move(pos);
}

void DX2DCamera::Move(Vector2D center)
{
	_physicsArea.Reposition(center);
}

bool DX2DCamera::Init()
{
	_windowWidth = g_dxWindow->GetClientWidth();
	_windowHeight = g_dxWindow->GetClientHeight();

	return true;
}

bool DX2DCamera::Frame()
{
	return true;
}

bool DX2DCamera::Render()
{
	return true;
}

bool DX2DCamera::Release()
{
	return true;
}
