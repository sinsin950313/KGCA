#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "BasicWindow.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "BasicWindow.h"
#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <vector>
#include "DXDrawableInterface.h"
#include "DXTextableInterface.h"

namespace SSB
{
	class DXWindow : public BasicWindow
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
		DXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override final;
		bool Release() override;

	protected:
		virtual bool PreRender();
		virtual bool MainRender();
		virtual bool PostRender();

	private:
		std::vector<DXDrawableInterface*> _objectList;
		void DrawObjects();
		std::vector<DXTextableInterface*> _textList;
		void DrawTexts();

	public:
		void AddDrawable(DXDrawableInterface* drawable);
		void AddTextable(DXTextableInterface* textable);

	public:
		ID3D11Device* GetDevice() { return _device; }
		ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }
		IDXGISwapChain* GetSwapChain() { return _swapChain; }
		ID2D1RenderTarget* GetRenderTarget2D() { return _renderTarget2D; }
		IDWriteFactory* GetWriteFactory() { return _writeFactory; }
	};
}
