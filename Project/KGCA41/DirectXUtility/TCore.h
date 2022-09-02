#pragma once

#include "CommonClass.h"
#include "TInputManager.h"
#include "TTimer.h"
#include "TTextManager.h"

class TCore : public Common
{
private:
	static TCore* _instance;

private:
	HWND _hWnd;
	IDXGISwapChain* _swapChain;
	TTimer _timer;

private:
	TCore() { }

public:
	static TCore& GetInstance();

public:
	void Set(HWND hWnd, IDXGISwapChain* swapChain);
	TTimer& GetTimer() { return _timer; }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
