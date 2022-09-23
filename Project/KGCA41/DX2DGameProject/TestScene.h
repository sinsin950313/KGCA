#pragma once

#include "Scene.h"
#include <vector>
#include "DX2DProjectController.h"

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
		DX2DGameObjectFactory* _factory;
		//std::vector<DX2DGameObject*> _objects;
		PlayerController* _playerController;
		DX2DGameObject* _playerObject;
		DX2DGameObject* _enemyObject;

	public:
		TestScene();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	private:
		void SetDisplayPosition(DX2DGameObject* object);
		void SetDisplayPosition(DX2DMapObject* map);
	};
}
