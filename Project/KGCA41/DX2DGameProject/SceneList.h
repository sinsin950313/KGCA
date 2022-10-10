#pragma once

#include "Scene.h"
#include <vector>
#include "DX2DProjectController.h"
#include "Text.h"
#include "UI.h"
#include "Terrain.h"
#include "Sound.h"

namespace SSB
{
	class DX2DMapObject;
	class DX2DGameObject;
	class DX2DCamera;
	class DX2DGameObjectFactory;

	class TitleScene : public Scene
	{
	private:
		DX2DObject* _mainScene;
		DX2DObject* _flight;
		Button* _startButton;
		TextUI* _titleTextTop;
		TextUI* _titleTextGun;
		Sound* _bgm;

	public:
		TitleScene();
		~TitleScene();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class BattleScene : public Scene
	{
	private:
		class HitEffectMemoryPool : public Common
		{
		private:
			const int _initialEffectCount = 10;
			int _effectCount = 0;
			std::vector<DX2DGameObject*> _effectList;
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
		class CloudManager : public Common
		{
		private:
			std::vector<DX2DGameObject*> _clouds;
			const DWORD _interval = 400;
			DWORD _lastTime;

		public:
			~CloudManager();

		private:
			DX2DGameObject* GetCloud();

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
		UINT _damagedCount = 0;
		HitEffectMemoryPool _pool;
		CloudManager* _cloudManager;

		Text* _text;

		const DWORD _maxTime = 30000;
		DWORD _startTime = 0;
		TextUI* _timerText;

		bool _defenseStage = true;

		Sound* _bgm;

	public:
		BattleScene();
		~BattleScene();

	public:
		void ModeChange() { _defenseStage = false; _enemyController->SetDeffensive(); }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	private:
		void SetDisplayPosition(DX2DGameObject* object);
		void SetDisplayPosition(DX2DInGameObject* object);
		//void SetDisplayPosition(DX2DMapObject* map);
	};

	class ChangeScene : public Scene
	{
	private:
		Position2D _enemyPosition;
		Position2D _playerPosition;
		Terrain* _terrain;

		int _initSize = 50;

		// Change scene only has DXObject.
		// This Scene just direct animation which is change position from deffense to offense.
		DX2DObject* _enemy;
		DX2DObject* _player;

		DWORD _startTime;
		DWORD _scenePlayTime = 5000;

	public:
		ChangeScene();
		~ChangeScene();

	public:
		void SetInitialPosition(Position2D player, Position2D enemy);
		void SetTerrian(Terrain* terrain) { _terrain = terrain; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class EndScene : public Scene
	{
	private:
		DX2DObject* _mainScene;
		TextUI* _hitUI;
		TextUI* _damageUI;
		UINT _hitCount;
		UINT _damagedCount;
		Sound* _bgm;

	public:
		EndScene();
		~EndScene();

	public:
		void SetScore(UINT hitCount, UINT damagedCount) { _hitCount = hitCount; _damagedCount = damagedCount; }

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
