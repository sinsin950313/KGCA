#pragma once

#include "Common.h"
#include "DX2DObject.h"
#include "Object.h"

namespace SSB
{
	class DX2DGameObject;
	class DX2DInGameObject;
	class DX2DMapObject;

	class DX2DCamera : public Common
	{
	private:
		Object2D* _captureArea;
		float _windowWidth;
		float _windowHeight;

	public:
		DX2DCamera(Vector2D center, float physicsWidth, float physicsHeight);
		~DX2DCamera();

	public:
		Vector2D GetCenter() { return _captureArea->GetVolume()->GetCenter(); }
		void MontageForFilm(DX2DGameObject* object);
		void MontageForFilm(DX2DInGameObject* object);
		void MontageForFilm(DX2DMapObject* map);
		void Move(float x, float y);
		void Move(Vector2D center);
		Object2D* GetCaptureArea() { return _captureArea; }
		void ConnectTo(DX2DGameObject* object);

	private:
		// Physics Coordinate to Screen Coordinate
		Position2D PhysicsToDisplay(Vector2D absolute);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
