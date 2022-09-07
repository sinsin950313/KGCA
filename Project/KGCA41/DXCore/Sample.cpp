#include "DXCore.h"
#include "TText.h"
#include <string>
#include "TTextManager.h"
#include "TInputManager.h"

class DXCoreTest : public DXCore
{
private:
	TText* _timer;
	TText* _wasd;
	TText* _mouse;

public:
	DXCoreTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXCore(name, hInstance, nCmdShow) { }

public:
	bool Init() override
	{
		DXCore::Init();

		_timer = new TText(L"", { 0, 0, 100, 50 });
		_timer->SetTextFormat(TTextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
		_timer->SetBrush(TTextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
		_timer->Init();

		_wasd = new TText(L"", { 200, 300, 300, 500 });
		_wasd->SetTextFormat(TTextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
		_wasd->SetBrush(TTextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
		_wasd->Init();

		_mouse = new TText(L"", { 600, 300, 300, 700 });
		_mouse->SetTextFormat(TTextManager::GetInstance().LoadTextFormat(L"°íµñ", L"ko-kr", 30));
		_mouse->SetBrush(TTextManager::GetInstance().LoadBrush(L"Black", { 0, 0, 0, 1 }));
		_mouse->Init();

		return true;
	}
	bool Frame() override
	{
		DXCore::Frame();

		_timer->SetString(std::to_wstring(GetGlobalTime()));

		_wasd->SetString(L"");
		if (TInputManager::GetInstance().GetKeyState('W') == EKeyState::KEY_HOLD)
		{
			_wasd->SetString(L"W Key Hold");
		}
		if (TInputManager::GetInstance().GetKeyState('A') == EKeyState::KEY_HOLD)
		{
			_wasd->SetString(L"A Key Hold");
		}
		if (TInputManager::GetInstance().GetKeyState('S') == EKeyState::KEY_HOLD)
		{
			_wasd->SetString(L"S Key Hold");
		}
		if (TInputManager::GetInstance().GetKeyState('D') == EKeyState::KEY_HOLD)
		{
			_wasd->SetString(L"D Key Hold");
		}

		_mouse->SetString(L"");
		if (TInputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
		{
			_mouse->SetString(std::to_wstring(TInputManager::GetInstance().GetMousePosition().x) + L", " + std::to_wstring(TInputManager::GetInstance().GetMousePosition().y));
		}

		return true;
	}
	bool PreRender() override
	{
		DXCore::PreRender();
		AddTextable(_timer);
		AddTextable(_wasd);
		AddTextable(_mouse);

		return true;
	}
};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	DXCoreTest win(L"Test", hInstance, nCmdShow);
	win.Init();
	win.Run();
	win.Release();
}
