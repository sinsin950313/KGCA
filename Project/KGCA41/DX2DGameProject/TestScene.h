#pragma once

#include "Scene.h"
#include <vector>
#include "DX2DProjectController.h"
#include "Text.h"

namespace SSB
{
	class DX2DMapObject;
	class DX2DGameObject;
	class DX2DCamera;
	class DX2DGameObjectFactory;

	class TestScene : public Scene
	{
	private:
		class HitEffectMemoryPool : public Common
		{
		private:
			const int _initialEffectCount = 10;
			int _effectCount = 0;
			std::vector<DX2DObject*> _effectList;
			DX2DCamera* _camera;

		public:
			HitEffectMemoryPool();
			~HitEffectMemoryPool();

		private:
			void RequireMemory(int newCount);

		public:
			void SetCamera(DX2DCamera* camera);
			void RunEffect(Vector2D pos);

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};
	private:
		DX2DMapObject* _map;
		DX2DCamera* _camera;
		DX2DGameObjectFactory* _factory;
		//std::vector<DX2DGameObject*> _objects;
		PlayerController* _playerController;
		DX2DInGameObject* _playerObject;
		EnemyController* _enemyController;
		DX2DInGameObject* _enemyObject;
		UINT _hitCount = 0;
		UINT _hittedCount = 0;
		HitEffectMemoryPool _pool;

		Text* _text;

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
