#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "BasicWindow.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "TBasicWindow.h"
#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include "TText.h"
#include <vector>

class TDXWindow : public TBasicWindow
{
private:
	IDXGIFactory* _dxgiFactory = nullptr;

	ID3D11Device* _device = nullptr;
	D3D_FEATURE_LEVEL _featureLevel;
	ID3D11DeviceContext* _deviceContext = nullptr;
	IDXGISwapChain* _swapChain = nullptr;
	ID3D11RenderTargetView* _renderTargetView = nullptr;

	ID2D1Factory* _factory2D;
	IDWriteFactory* _writeFactory;
	ID2D1RenderTarget* _renderTarget2D;

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

private:
	std::vector<TText*> _textList;
public:
	void AddText(TText* text);

public:
	ID3D11Device* GetDevice() { return _device; }
	ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }
	IDXGISwapChain* GetSwapChain() { return _swapChain; }
	ID2D1RenderTarget* GetRenderTarget2D() { return _renderTarget2D; }
	IDWriteFactory* GetWriteFactory() { return _writeFactory; }
};
