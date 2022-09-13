#include "DX2DCamera.h"
#include "TDXWindow.h"
#include "PhysicsVector.h"
#include "DX2DGameObject.h"
#include <float.h>

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

void DX2DCamera::MontageForLens(DX2DGameObject* object)
{
	auto center = PhysicsToDisplay(object->GetPhysicsObject()->GetVolume()->GetCenter());
	object->GetDXObject()->Move(center);

	auto vertice = object->GetPhysicsObject()->GetVolume()->GetVertexes();
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

	float physicsWidth = maxX - minX;
	float physicsHeight = maxY - minY;

	float screenWidth = physicsWidth / _physicsArea.GetWidth() * _windowWidth;
	float screenHeight = physicsHeight / _physicsArea.GetHeight() * _windowHeight;

	object->GetDXObject()->Resize(screenWidth, screenHeight);
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
