#pragma once

#include "Scene.h"
#include <vector>

namespace SSB
{
	class DX2DMapObject;
	class DX2DGameObject;
	class DX2DCamera;
	class DX2DGameObjectFactory;

	class TestScene : public Scene
	{
	private:
		DX2DMapObject* _map;
		DX2DCamera* _camera;
		std::vector<DX2DGameObject*> _objects;
		DX2DGameObject* _player;
		DX2DGameObjectFactory* _factory;
		float _dx = 0;
		float _dy = 0;

	public:
		TestScene();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	private:
		void GameLogic();
		void SetDisplayPosition(DX2DGameObject* object);
		void SetDisplayPosition(DX2DMapObject* map);
	};
}
