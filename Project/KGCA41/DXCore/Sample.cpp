#include "DXCore.h"
#include "Text.h"
#include <string>
#include "TextManager.h"
#include "InputManager.h"
#include "Scene.h"

namespace SSB
{
	extern DXCore* g_DXCore;

	class TestScene : public Scene
	{
	private:
		Text* _timer;
		Text* _wasd;
		Text* _mouse;

	public:
		bool Init() override
		{
			Scene::Init();

			_timer = new Text(L"", { 0, 0, 100, 50 });
			_timer->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
			_timer->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
			_timer->Init();

			_wasd = new Text(L"", { 200, 300, 300, 500 });
			_wasd->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
			_wasd->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
			_wasd->Init();

			_mouse = new Text(L"", { 600, 300, 300, 700 });
			_mouse->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
			_mouse->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
			_mouse->Init();

			return true;
		}
		bool Frame() override
		{
			Scene::Frame();

			_timer->SetString(std::to_wstring(g_DXCore->GetGlobalTime()));

			_wasd->SetString(L"");
			if (InputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
			{
				_wasd->SetString(L"W Key Hold");
			}
			if (InputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
			{
				_wasd->SetString(L"A Key Hold");
			}
			if (InputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
			{
				_wasd->SetString(L"S Key Hold");
			}
			if (InputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
			{
				_wasd->SetString(L"D Key Hold");
			}

			_mouse->SetString(L"");
			if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
			{
				_mouse->SetString(std::to_wstring(InputManager::GetInstance().GetMousePosition().x) + L", " + std::to_wstring(InputManager::GetInstance().GetMousePosition().y));
			}

			if (InputManager::GetInstance().GetKeyState('Q') == EKeyState::KEY_HOLD)
			{
				SetFinished(true);
			}

			return true;
		}
		bool Render() override
		{
			Scene::Render();

			g_DXCore->AddTextable(_timer);
			g_DXCore->AddTextable(_wasd);
			g_DXCore->AddTextable(_mouse);

			return true;
		}
		bool Release() override
		{
			return Scene::Release();
		}
	};

	class TestEndScene : public Scene
	{
	private:
		Text* _endMessage;

	public:
		bool Init() override
		{
			Scene::Init();

			_endMessage = new Text(L"", { 200, 300, 300, 500 });
			_endMessage->SetTextFormat(TextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
			_endMessage->SetBrush(TextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
			_endMessage->SetString(L"Scene is finished");
			_endMessage->Init();

			return true;
		}
		bool Render() override
		{
			Scene::Render();

			g_DXCore->AddTextable(_endMessage);

			return true;
		}
		bool Release() override
		{
			if (_endMessage)_endMessage->Release();
			return Scene::Release();
		}
	};

	class DXCoreTest : public DXCore
	{
	public:
		DXCoreTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow)
		{
			NewScene("Default", new TestScene());
			SetCurrentScene("Default");
			NewScene("End", new TestEndScene());
			GetScene("Default")->LinkNewScene("End", GetScene("End"));
			GetScene("Default")->SetNextScene("End");
		}

	public:
		bool PreRender() override
		{
			DXCore::PreRender();

			return true;
		}
	};
}

using namespace SSB;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DXCoreTest win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
