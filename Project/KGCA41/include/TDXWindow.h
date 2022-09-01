#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "BasicWindow.lib")

#include "TBasicWindow.h"
#include <d3d11.h>

class TDXWindow : public TBasicWindow
{
private:
	IDXGIFactory* _dxgiFactory = nullptr;

	ID3D11Device* _device = nullptr;
	D3D_FEATURE_LEVEL _featureLevel;
	ID3D11DeviceContext* _deviceContext = nullptr;
	IDXGISwapChain* _swapChain = nullptr;
	ID3D11RenderTargetView* _renderTargetView = nullptr;

public:
	TDXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : TBasicWindow(name, hInstance, nCmdShow) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

protected:
	virtual bool PreRender();
	virtual bool MainRender();
	virtual bool PostRender();

public:
	ID3D11Device* GetDevice() { return _device; }
	ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }
};
