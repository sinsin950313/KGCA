#include "DX2DCamera.h"
#include "DXWindow.h"
#include "PhysicsVector.h"
#include "DX2DGameObject.h"
#include <float.h>
#include "Rectangle.h"
#include "DX2DMapObject.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

	DX2DCamera::DX2DCamera(Vector2D center, float physicsWidth, float physicsHeight)
	{
		_captureArea = new Object2D(new Rectangle(center.Get(0), center.Get(1), physicsWidth, physicsHeight), Rigidbody2D(0));
	}

	DX2DCamera::~DX2DCamera()
	{
		Release();
	}

	Position2D DX2DCamera::PhysicsToDisplay(Vector2D absolute)
	{
		Vector2D relative = absolute - _captureArea->GetVolume()->GetCenter();
		Rectangle* captureArea = static_cast<Rectangle*>(_captureArea->GetVolume());
		Vector2D halfForPhysicsToScreen(Vector2DData{ -captureArea->GetWidth() / 2, captureArea->GetHeight() / 2 });
		Vector2D physicsInScreen = relative - halfForPhysicsToScreen;
		Vector2D NDCByPIS(Vector2DData{ physicsInScreen.Get(0) / captureArea->GetWidth(), physicsInScreen.Get(1) / captureArea->GetHeight() });
		Position2D screenCoor{ NDCByPIS.Get(0) * _windowWidth, -NDCByPIS.Get(1) * _windowHeight };
		return screenCoor;
	}

	void DX2DCamera::MontageForFilm(DX2DGameObject* object)
	{
		auto center = PhysicsToDisplay(object->GetCenter());
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

		Rectangle* captureArea = static_cast<Rectangle*>(_captureArea->GetVolume());
		float screenWidth = physicsWidth / captureArea->GetWidth() * _windowWidth;
		float screenHeight = physicsHeight / captureArea->GetHeight() * _windowHeight;

		object->GetDXObject()->Resize(screenWidth, screenHeight);
	}

	void DX2DCamera::MontageForFilm(DX2DInGameObject* object)
	{
		int currentLayer = object->GetCurrentMapLayer() - 2;
		float ratio = (10.0f + currentLayer * 2) / 10.0f;
		MontageForFilm((DX2DGameObject*)object);
		object->GetDXObject()->Resize(object->GetDXObject()->GetWidth() * ratio, object->GetDXObject()->GetHeight() * ratio);
	}

	//void DX2DCamera::MontageForFilm(DX2DMapObject* map)
	//{
	//	auto center = PhysicsToDisplay(map->GetCenter());
	//	//map->SetDXCenter(center);

	//	auto vertice = map->GetPhysicsObject()->GetVolume()->GetVertexes();
	//	float minX = FLT_MAX;
	//	float maxX = FLT_MIN;
	//	float minY = FLT_MAX;
	//	float maxY = FLT_MIN;
	//	for (auto vertex : vertice)
	//	{
	//		minX = std::fmin(minX, vertex->Get(0));
	//		maxX = std::fmax(maxX, vertex->Get(0));
	//		minY = std::fmin(minY, vertex->Get(1));
	//		maxY = std::fmax(maxY, vertex->Get(1));
	//	}

	//	float physicsWidth = maxX - minX;
	//	float physicsHeight = maxY - minY;

	//	Rectangle* captureArea = static_cast<Rectangle*>(_captureArea->GetVolume());
	//	float screenWidth = physicsWidth / captureArea->GetWidth() * _windowWidth;
	//	float screenHeight = physicsHeight / captureArea->GetHeight() * _windowHeight;

	//	//map->GetDXObject()->Resize(screenWidth, screenHeight);
	//}

	void DX2DCamera::Move(float x, float y)
	{
		Vector2D pos(Vector2DData{ x, y });
		Move(pos);
	}

	void DX2DCamera::Move(Vector2D center)
	{
		_captureArea->GetVolume()->Reposition(center);
	}

	void DX2DCamera::ConnectTo(DX2DGameObject* object)
	{
		Move(object->GetCenter());
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
		if (_captureArea)
		{
			delete _captureArea;
			_captureArea = nullptr;
		}
		return true;
	}
}
