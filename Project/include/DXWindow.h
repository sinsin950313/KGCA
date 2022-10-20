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
#include "Camera.h"

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
		ID3D11DepthStencilView* _depthStencilView = nullptr;

		ID2D1Factory* _factory2D = nullptr;
		IDWriteFactory* _writeFactory = nullptr;
		ID2D1RenderTarget* _renderTarget2D = nullptr;

		Camera _defaultCamera;
		Camera* _mainCamera = nullptr;

	private:
		HRESULT CreateDevice();
		HRESULT CreateWindowDXGIFactory();
		HRESULT CreateSwapChain();
		HRESULT CreateRenderTargetView();
		HRESULT Create2DFactory();
		HRESULT CreateRenderTarget2D();
		HRESULT CreateWriteFactory();
		HRESULT CreateViewPort();
		HRESULT CreateDepthStencilView();

	public:
		DXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

	private:
		HRESULT UpdateResize() override;

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
		ID3D11Device* GetDevice() { return _device; }
		ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }
		IDXGISwapChain* GetSwapChain() { return _swapChain; }
		ID2D1RenderTarget* GetRenderTarget2D() { return _renderTarget2D; }
		IDWriteFactory* GetWriteFactory() { return _writeFactory; }
		void ChangeMainCamera(Camera* camera) { _mainCamera = camera; }
		Camera* GetMainCamera() { return _mainCamera; }
	};
}
