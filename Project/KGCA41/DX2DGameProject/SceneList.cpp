#define _USE_MATH_DEFINES

#include "SceneList.h"
#include "DX2DMapObject.h"
#include "DX2DGameObject.h"
#include "DX2DCamera.h"
#include "InputManager.h"
#include "DXWindow.h"
#include "DX2DGameObjectFactory.h"
#include "TextureManager.h"
#include "DXStateManager.h"
#include "TextManager.h"
#include "DXCore.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "DX2DAnimation.h"
#include <math.h>

namespace SSB
{
	extern DXWindow* g_dxWindow;
	DX2DCamera* g_Camera;
	extern DXCore* g_DXCore;
	extern bool g_Debug;
    extern BasicWindow* g_Window;

	TitleScene::TitleScene()
	{
		_mainScene = new DX2DObject();
		_flight = new DX2DObject();
		_bgm = SoundManager::GetInstance().Load(L"Title.mp3");
		class StartButtonFunctor : public ButtonFunctor
		{
		private:
			Scene* _currentScene;
			Sound* _bgm;

		public:
			StartButtonFunctor(Scene* currentScene, Sound* bgm) : _currentScene(currentScene), _bgm(bgm) { }

        public:
            void operator()() override
            {
				_bgm->Stop();
				_currentScene->SetFinished(true);
            }
		};
		_startButton = new Button(new StartButtonFunctor(this, _bgm));
		_titleTextTop = new TextUI(L"Font.png");
		_titleTextGun = new TextUI(L"Font.png");
	}

	TitleScene::~TitleScene()
	{
		Release();
	}

	bool TitleScene::Init()
	{
		Scene::Init();

		_bgm->Init();
		_bgm->Play(true);

		_mainScene->SetCenter({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) });
		_mainScene->Resize(g_Window->GetClientWidth(), g_Window->GetClientHeight());
		SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"TitleBackground.jpg", L"TitleBackground", { 0, 0, 5101, 3401 });
		_mainScene->SetSprite(SpriteLoader::GetInstance().Load(L"TitleBackground.jpg", L"TitleBackground", DXStateManager::kDefaultWrapSample));
		_mainScene->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		_mainScene->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithoutMask", "ps_5_0"));
		_mainScene->Init();

		_flight->SetCenter({ (float)(g_Window->GetClientWidth() / 6 * 5), (float)(g_Window->GetClientHeight() / 8 * 7) });
		_flight->Resize(g_Window->GetClientWidth(), g_Window->GetClientHeight());
		SpriteLoader::GetInstance().RegisterSpriteFromFile(L"FA-18 Super Hornet.bmp", L"FA-18 Super Hornet");
		_flight->SetSprite(SpriteLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"Title3", DXStateManager::kDefaultWrapLinearSample));
		_flight->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		_flight->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FA-18 Super Hornet PixelShader.hlsl", "Main", "ps_5_0"));
		_flight->Init();

		_startButton->SetCenter({(float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) + 200});
		_startButton->Resize(400, 150);
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonNormal.png", L"Normal", { 0, 0, 300, 196 });
        _startButton->RegisterButton("Normal", SpriteLoader::GetInstance().Load(L"DefaultButtonNormal.png", L"Normal", DXStateManager::kDefaultWrapSample));
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonHover.png", L"Hover", { 0, 0, 300, 196 });
        _startButton->RegisterButton("Hover", SpriteLoader::GetInstance().Load(L"DefaultButtonHover.png", L"Hover", DXStateManager::kDefaultWrapSample));
        SpriteLoader::GetInstance().RegisterSpriteWithCoordinateValue(L"DefaultButtonPush.png", L"Push", { 0, 0, 300, 196 });
        _startButton->RegisterButton("Push", SpriteLoader::GetInstance().Load(L"DefaultButtonPush.png", L"Push", DXStateManager::kDefaultWrapSample));
        _startButton->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _startButton->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"ButtonPixelShader.hlsl", "Main", "ps_5_0"));
		TextUI* _startUI = new TextUI(L"Font.png");
        _startUI->SetCenter({ 0, -10 });
        _startUI->SetText("START");
		_startUI->SetHeight(80);
		_startButton->AddChild(_startUI);
		_startButton->Init();

        _titleTextTop->SetCenter({(float)(g_Window->GetClientWidth() / 2) - 100, (float)(g_Window->GetClientHeight() / 2) - 200});
        _titleTextTop->SetText("TOP");
		_titleTextTop->SetHeight(200);
		_titleTextTop->Init();

        _titleTextGun->SetCenter({(float)(g_Window->GetClientWidth() / 2) + 100, (float)(g_Window->GetClientHeight() / 2) + 20});
        _titleTextGun->SetText("GUN!");
		_titleTextGun->SetHeight(200);
		_titleTextGun->Init();

		SetNextScene("DefenseScene");

		return true;
	}

	bool TitleScene::Frame()
	{
		Scene::Frame();

		_mainScene->Frame();
		_flight->Frame();
		_startButton->Frame();
		_titleTextTop->Frame();
		_titleTextGun->Frame();
		_bgm->Frame();

		return true;
	}

	bool TitleScene::Render()
	{
		Scene::Render();

		_mainScene->Render();
		_flight->Render();
		_startButton->Render();
		_titleTextTop->Render();
		_titleTextGun->Render();
		_bgm->Render();

		return true;
	}

	bool TitleScene::Release()
	{
		if (_mainScene)
		{
			_mainScene->Release();
			delete _mainScene;
			_mainScene = nullptr;
		}
		if (_flight)
		{
			_flight->Release();
			delete _flight;
			_flight = nullptr;
		}
		if (_startButton)
		{
			_startButton->Release();
			delete _startButton;
			_startButton = nullptr;
		}
		if (_titleTextTop)
		{
			_titleTextTop->Release();
			delete _titleTextTop;
			_titleTextTop = nullptr;
		}
		if (_titleTextGun)
		{
			_titleTextGun->Release();
			delete _titleTextGun;
			_titleTextGun = nullptr;
		}
		if (_bgm)
		{
			_bgm->Release();
			delete _bgm;
			_bgm = nullptr;
		}

		Scene::Release();

		return true;
	}

	BattleScene::BattleScene()
	{
		_map = new DX2DMapObject(Vector2D(Vector2DData{ 0, 0 }), 300, 300);

		_factory = new DX2DGameObjectFactory;
		_factory->SetMapObject(_map);

		_playerObject = _factory->CreateDynamicGameObject(Position2D{ 0, 0, }, 10, 10, 1);
		_playerController = new PlayerController(_playerObject);

		_enemyObject = _factory->CreateDynamicGameObject(Position2D{ 0, 50, }, 10, 10, 2);
		_enemyController = new EnemyController(_enemyObject);
		_enemyController->SetEnemy(_playerObject);

		_camera = new DX2DCamera(Vector2D(Vector2DData{ 0, 0 }), 100, 100);
		g_Camera = _camera;

		_cloudManager = new CloudManager;

		_text = new Text(L"", { 0, 100, 300, 50 });
		_timerText = new TextUI(L"Font.png");
		_bgm = SoundManager::GetInstance().Load(L"BattleBGM.mp3");

		_pool.SetCamera(_camera);
		_map->SetPlayer(_playerObject);
	}

	BattleScene::~BattleScene()
	{
		Release();
	}

	bool BattleScene::Init()
	{
		Scene::Init();

		if (_defenseStage)
		{
			_camera->Init();

			_map->Init();

			_playerObject->Init();
			_enemyObject->Init();

			_pool.Init();

			_text->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
			_text->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
			_text->Init();

			_cloudManager->Init();

			_timerText->SetCenter({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) - 250 });
			_timerText->SetText("");
			_timerText->SetHeight(50);
			_timerText->Init();

			SetNextScene("ChangeScene");
			_playerObject->Move(g_Camera->GetCenter().Get(0), g_Camera->GetCenter().Get(1) + 50);
			_enemyObject->Move(g_Camera->GetCenter().Get(0), g_Camera->GetCenter().Get(1) - 50);

			SoundManager::GetInstance().PlayInstanceSound(L"BattleStart.mp3");

			_bgm->Init();
		}
		else
		{
			_playerObject->Move(g_Camera->GetCenter().Get(0), g_Camera->GetCenter().Get(1) - 50);
			_enemyObject->Move(g_Camera->GetCenter().Get(0), g_Camera->GetCenter().Get(1) + 50);
			SetNextScene("EndScene");
		}

		_startTime = g_DXCore->GetGlobalTime();
		_bgm->Play(true);

		return true;
	}

	bool BattleScene::Frame()
	{
		Scene::Frame();

		if (_maxTime < g_DXCore->GetGlobalTime() - _startTime)
		{
			SetFinished(true);
			if (_defenseStage)
			{
				((ChangeScene*)GetNextScene())->SetInitialPosition(_playerObject->GetDXObject()->GetCenter(), _enemyObject->GetDXObject()->GetCenter());
				((ChangeScene*)GetNextScene())->SetTerrian(_map->GetTerrain());
				_bgm->Stop();
			}
			else
			{
				((EndScene*)GetNextScene())->SetScore(_hitCount, _damagedCount);
				_bgm->Stop();
			}
		}

		_bgm->Frame();

		float remainTime = (_maxTime - (g_DXCore->GetGlobalTime() - _startTime)) / 1000.0f;
		_timerText->SetText(std::to_string(remainTime));
		_timerText->Frame();

		_map->Frame();

		const float kDefaultSpeed = 0.5f;
		_playerObject->Move(_playerObject->GetCenter().Get(0), _playerObject->GetCenter().Get(1) + kDefaultSpeed);
		_enemyObject->Move(_enemyObject->GetCenter().Get(0), _enemyObject->GetCenter().Get(1) + kDefaultSpeed);

		_playerController->Frame();
		_enemyController->Frame();

		_camera->ConnectTo(_playerObject);
		_camera->Frame();

		_pool.Frame();

		//collide check
		if (_map->IsHit(_playerObject, _enemyObject))
		{
			_enemyObject->Targeted();
			if (_enemyObject->IsHit())
			{
				++_hitCount;
				_pool.RunEffect(_enemyObject->GetCenter());
			}
		}
		else
		{
			_enemyObject->UnTargeted();
		}
		
		if (_map->IsHit(_enemyObject, _playerObject))
		{
			_playerObject->Targeted();
			if (_playerObject->IsHit())
			{
				++_damagedCount;
				_pool.RunEffect(_playerObject->GetCenter());
			}
		}
		else
		{
			_playerObject->UnTargeted();
		}

		_text->SetString(L"DeltaLayer : " + std::to_wstring(_enemyObject->GetCurrentMapLayer()));
		_text->Frame();

		_cloudManager->Frame();

		return true;
	}

	bool BattleScene::Release()
	{
		if (_factory)
		{
			delete _factory;
			_factory = nullptr;
		}

		if (_playerController)
		{
			_playerController->Release();
			delete _playerController;
			_playerController = nullptr;
		}

		if (_enemyController)
		{
			_enemyController->Release();
			delete _enemyController;
			_enemyController = nullptr;
		}

		if (_map)
		{
			_map->Release();
			delete _map;
			_map = nullptr;
		}

		if (_playerObject)
		{
			_playerObject->Release();
			delete _playerObject;
			_playerObject = nullptr;
		}

		if (_enemyObject)
		{
			_enemyObject->Release();
			delete _enemyObject;
			_enemyObject = nullptr;
		}

		if (_camera)
		{
			_camera->Release();
			delete _camera;
			_camera = nullptr;
		}

		_pool.Release();

		if (_text != nullptr)
		{
			_text->Release();
			delete _text;
			_text = nullptr;
		}

		if (_cloudManager)
		{
			_cloudManager->Release();
			delete _cloudManager;
			_cloudManager = nullptr;
		}

		if (_timerText != nullptr)
		{
			_timerText->Release();
			delete _timerText;
			_timerText = nullptr;
		}

		if (_bgm)
		{
			_bgm->Release();
			delete _bgm;
			_bgm = nullptr;
		}

		Scene::Release();

		return true;
	}

	bool BattleScene::Render()
	{
		Scene::Render();

		_map->Render();

		_cloudManager->Render();

		auto objectList = _map->GetCollideObjectList(_camera);
		for (auto object : objectList)
		{
			SetDisplayPosition(object);
			object->Render();
		}

		_pool.Render();

		if (g_Debug)
		{
			_text->Render();
		}

		_timerText->Render();

		_bgm->Render();

		return true;
	}

	void BattleScene::SetDisplayPosition(DX2DInGameObject* object)
	{
		_camera->MontageForFilm(object);
	}

	void BattleScene::SetDisplayPosition(DX2DGameObject* object)
	{
		_camera->MontageForFilm(object);
	}

	BattleScene::HitEffectMemoryPool::HitEffectMemoryPool()
	{
	}

	BattleScene::HitEffectMemoryPool::~HitEffectMemoryPool()
	{
		Release();
	}

	void BattleScene::HitEffectMemoryPool::RequireMemory(int newCount)
	{
		_effectList.resize(newCount);

		for (int i = _effectCount; i < newCount; ++i)
		{
			DX2DGameObject* effect = new DX2DGameObject({ 0, 0 }, 5, 5, 0);
			effect->GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
			effect->GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"Default2DPixelShader.hlsl", "WithMask", "ps_5_0"));

			SpriteLoader::GetInstance().RegisterSpriteFromFile(L"Effect.bmp", L"Effect");
			SpriteAction* action = SpriteActionLoader::GetInstance().Load(L"Effect.bmp", L"Bomb", DXStateManager::kDefaultWrapSample);
			action->SetInterval(300);
			action->SetLoop(false);
			action->Off();
			effect->GetDXObject()->SetSprite(action);
			effect->Init();

			_effectList[i] = effect;
		}
		_effectCount = newCount;
	}

	void BattleScene::HitEffectMemoryPool::SetCamera(DX2DCamera* camera)
	{
		_camera = camera;
	}

	void BattleScene::HitEffectMemoryPool::RunEffect(Vector2D pos)
	{
		for (auto effect : _effectList)
		{
			SpriteAction* action = (SpriteAction*)effect->GetDXObject()->GetSprite();
			if (action->IsFinished())
			{
				effect->GetPhysicsObject()->GetVolume()->Reposition(pos);
				action->ResetAction();
				SoundManager::GetInstance().PlayInstanceSound(L"20mm effect.mp3");
				return;
			}
		}
		RequireMemory(_effectCount + 10);
		RunEffect(pos);
	}

	bool BattleScene::HitEffectMemoryPool::Init()
	{
		RequireMemory(_initialEffectCount);

		return true;
	}

	bool BattleScene::HitEffectMemoryPool::Frame()
	{
		for (auto effect : _effectList)
		{
			_camera->MontageForFilm(effect);
			effect->Frame();
		}
		return true;
	}

	bool BattleScene::HitEffectMemoryPool::Render()
	{
		for (auto effect : _effectList)
		{
			SpriteAction* action = (SpriteAction*)effect->GetDXObject()->GetSprite();
			if (!action->IsFinished())
			{
				effect->Render();
			}
		}
		return true;
	}

	bool BattleScene::HitEffectMemoryPool::Release()
	{
		for (auto effect : _effectList)
		{
			effect->Release();
			delete effect;
		}
		_effectList.clear();

		_camera = nullptr;

		return true;
	}

	BattleScene::CloudManager::~CloudManager()
	{
		Release();
	}

	DX2DGameObject* BattleScene::CloudManager::GetCloud()
	{
		for (auto cloud : _clouds)
		{
			if (cloud->GetCenter().Get(1) < g_Camera->GetCenter().Get(1) - 100)
			{
				return cloud;
			}
		}
		return nullptr;
	}

	bool BattleScene::CloudManager::Init()
	{
		_lastTime = g_DXCore->GetGlobalTime();

		_clouds.resize(5);
		for (int i = 0; i < 5; ++i)
		{
			DX2DGameObject* cloud = new DX2DGameObject({ 0, -500 }, rand() % 20 + 10, rand() % 20 + 10, 0);
			cloud->GetDXObject()->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
			cloud->GetDXObject()->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"CloudPixelShader.hlsl", "Main", "ps_5_0"));

			SpriteLoader::GetInstance().RegisterSpriteFromFile(L"cloud.bmp", L"cloud");
			Sprite* sprite = SpriteLoader::GetInstance().Load(L"cloud.bmp", L"cloud1", DXStateManager::kDefaultWrapSample);
			cloud->GetDXObject()->SetSprite(sprite);
			cloud->Init();

			_clouds[i] = cloud;
		}

		return true;
	}

	bool BattleScene::CloudManager::Frame()
	{
		if (_lastTime + _interval < g_DXCore->GetGlobalTime())
		{
			if (rand() % 3 == 0)
			{
				auto cloud = GetCloud();
				if (cloud != nullptr)
				{
					std::wstring cloudName = L"cloud" + std::to_wstring(rand() % 3 + 1);
					cloud->GetDXObject()->SetSprite(SpriteLoader::GetInstance().Load(L"cloud.bmp", cloudName, DXStateManager::kDefaultWrapSample));
					cloud->Move(g_Camera->GetCenter().Get(0) + (rand() % 100 - 50), g_Camera->GetCenter().Get(1) + 100);
				}
			}
			_lastTime = g_DXCore->GetGlobalTime();
		}

		for (auto cloud : _clouds)
		{
			g_Camera->MontageForFilm(cloud);
			cloud->Frame();
		}
		return true;
	}

	bool BattleScene::CloudManager::Render()
	{
		for (auto cloud : _clouds)
		{
			cloud->Render();
		}

		return true;
	}

	bool BattleScene::CloudManager::Release()
	{
		for (auto cloud : _clouds)
		{
			cloud->Release();
			delete cloud;
		}
		_clouds.clear();

		return true;
	}

	ChangeScene::ChangeScene()
	{
        _player = new DX2DObject();
		_enemy = new DX2DObject();
	}

	ChangeScene::~ChangeScene()
	{
		Release();
	}

	void ChangeScene::SetInitialPosition(Position2D player, Position2D enemy)
	{
		_playerPosition = player;
		_enemyPosition = enemy;
	}

	bool ChangeScene::Init()
	{
		Scene::Init();

		_player->SetCenter(_playerPosition);
		_player->Resize(_initSize, _initSize);
        DX2DAnimation* animation = new DX2DAnimation(TextureResourceManager::GetInstance().Load(L"FA-18 Super Hornet.bmp"));
        SpriteAction* sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"PostStall", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(false);
        ((SpriteAction*)sprite)->SetInterval(100);
        animation->RegisterState("PostStall", sprite);
        animation->SetCurrentState("PostStall");
        _player->SetSprite(animation);
        _player->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _player->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FA-18 Super Hornet PixelShader.hlsl", "Main", "ps_5_0"));
        _player->Init();

		_enemy->SetCenter(_enemyPosition);
		_enemy->Resize(_initSize, _initSize);
        animation = new DX2DAnimation(TextureResourceManager::GetInstance().Load(L"FA-18 Super Hornet.bmp"));
        sprite = SpriteActionLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"Straight", DXStateManager::kDefaultWrapSample);
        ((SpriteAction*)sprite)->SetLoop(true);
        animation->RegisterState("Straight", sprite);
        animation->SetCurrentState("Straight");
        _enemy->SetSprite(animation);
        _enemy->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
        _enemy->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FA-18 Super Hornet PixelShader.hlsl", "Main", "ps_5_0"));
        _enemy->Init();

		_startTime = g_DXCore->GetGlobalTime();

		SetNextScene("OffenseScene");

		SoundManager::GetInstance().PlayInstanceSound(L"PostStall.mp3");

		return true;
	}

	bool ChangeScene::Frame()
	{
		Scene::Frame();

		DWORD elapseTime = g_DXCore->GetGlobalTime() - _startTime;
		if (_scenePlayTime < elapseTime)
		{
			SetFinished(true);
			auto scene = (BattleScene*)GetNextScene();
			scene->ModeChange();
			scene->SetFinished(false);
		}

		double theta = (double)elapseTime / _scenePlayTime * M_PI;
		float size = (g_dxWindow->GetClientHeight() - _initSize) * (sin(theta)) + _initSize;
		_player->Resize(size, size);

		static Position2D enemyInitPosition = _enemy->GetCenter();
		static Position2D enemyFinalPosition = { g_dxWindow->GetClientWidth() / 2, g_dxWindow->GetClientHeight() / 2 - 400.0f };

		float delta = (float)elapseTime / _scenePlayTime;
		_player->Frame();

		_enemy->SetCenter({ enemyInitPosition.x, enemyInitPosition.y + (enemyFinalPosition.y - enemyInitPosition.y) * delta });
		_enemy->Frame();

		return true;
	}

	bool ChangeScene::Render()
	{
		Scene::Render();

		_terrain->Render();
		_enemy->Render();
		_player->Render();

		return true;
	}

	bool ChangeScene::Release()
	{
		if (_player != nullptr)
		{
			_player->Release();
			delete _player;
			_player = nullptr;
		}

		if (_enemy != nullptr)
		{
			_enemy->Release();
			delete _enemy;
			_enemy = nullptr;
		}

		if (_terrain)
		{
			_terrain = nullptr;
		}

		Scene::Release();

		return true;
	}

	EndScene::EndScene()
	{
		_bgm = SoundManager::GetInstance().Load(L"Ending.mp3");
		_mainScene = new DX2DObject();
		_hitUI = new TextUI(L"Font.png");
		_damageUI = new TextUI(L"Font.png");
	}

	EndScene::~EndScene()
	{
		Release();
	}

	bool EndScene::Init()
	{
		Scene::Init();

		_bgm->Init();
		_bgm->Play(true);

		_mainScene->SetCenter({ (float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) });
		_mainScene->Resize(g_Window->GetClientWidth(), g_Window->GetClientHeight());
		SpriteLoader::GetInstance().RegisterSpriteFromFile(L"FA-18 Super Hornet.bmp", L"FA-18 Super Hornet");
		_mainScene->SetSprite(SpriteLoader::GetInstance().Load(L"FA-18 Super Hornet.bmp", L"End", DXStateManager::kDefaultWrapLinearSample));
		_mainScene->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
		_mainScene->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FA-18 Super Hornet PixelShader.hlsl", "Main", "ps_5_0"));
		_mainScene->Init();

        _hitUI->SetCenter({(float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2) - 100});
        _hitUI->SetText("HIT : " + std::to_string(_hitCount));
		_hitUI->SetHeight(100);
		_hitUI->Init();

        _damageUI->SetCenter({(float)(g_Window->GetClientWidth() / 2), (float)(g_Window->GetClientHeight() / 2)});
        _damageUI->SetText("DAMAGED : " + std::to_string(_damagedCount));
		_damageUI->SetHeight(100);
		_damageUI->Init();

		return true;
	}

	bool EndScene::Frame()
	{
		Scene::Frame();

		_mainScene->Frame();
		_hitUI->Frame();
		_damageUI->Frame();
		_bgm->Frame();

		return true;
	}

	bool EndScene::Render()
	{
		Scene::Render();

		_mainScene->Render();
		_hitUI->Render();
		_damageUI->Render();
		_bgm->Render();

		return true;
	}

	bool EndScene::Release()
	{
		if (_mainScene != nullptr)
		{
			_mainScene->Release();
			delete _mainScene;
			_mainScene = nullptr;
		}

		if (_hitUI != nullptr)
		{
			_hitUI->Release();
			delete _hitUI;
			_hitUI = nullptr;
		}

		if (_damageUI != nullptr)
		{
			_damageUI->Release();
			delete _damageUI;
			_damageUI = nullptr;
		}

		if (_bgm)
		{
			_bgm->Release();
			delete _bgm;
			_bgm = nullptr;
		}

		Scene::Release();

		return true;
	}
}
