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
	class RenderTarget : public Common
	{
	private:
		ID3D11Texture2D* _renderTargetTexture;
		ID3D11RenderTargetView* _renderTargetView;
		ID3D11Texture2D* _depthStencilTexture;
		ID3D11DepthStencilView* _depthStencilView;

	public:
		RenderTarget();

	private:
		HRESULT CreateRenderTarget();
		HRESULT CreateDepthStencil();

	public:
		ID3D11Texture2D* GetRenderTargetTexture() { return _renderTargetTexture; }
		ID3D11RenderTargetView* GetRenderTargetView() { return _renderTargetView; }
		ID3D11Texture2D* GetDepthStencilTexture() { return _depthStencilTexture; }
		ID3D11DepthStencilView* GetDepthStencilView() { return _depthStencilView; }
		void Clear();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class DXWindow : public BasicWindow
	{
		class Screen : public Common
		{
			struct Vertex
			{
				Float2 Position;
				Float4 Color;
				Float2 Texture;
			};
			ID3D11InputLayout* _inputLayout;
			ID3D11Buffer* _vertexBuffer;
			ID3D11Buffer* _indexBuffer;
			ID3D11Texture2D* _renderTargetTexture;
			ID3D11ShaderResourceView* _renderedTargetView;
			ID3D11Texture2D* _renderedDepthStencilTexture;
			ID3D11ShaderResourceView* _renderedDepthStencilView;
			ID3D11VertexShader* _vertexShader;
			ID3DBlob* _vsCode;
			ID3D11PixelShader* _pixelShader;
			ID3DBlob* _psCode;
			ID3D11SamplerState* _sampler;

		public:
			Screen();

		public:
			void SetRenderTargetTexture(ID3D11Texture2D* texture) { _renderTargetTexture = texture; }
			void SetDepthStencilTexture(ID3D11Texture2D* texture) { _renderedDepthStencilTexture = texture; }

		private:
			HRESULT CreateVertexBuffer();
			HRESULT CreateInputLayout();
			HRESULT CreateIndexBuffer();
			HRESULT CreateVertexShader();
			HRESULT CreatePixelShader();
			HRESULT CreateRenderTargetView();
			HRESULT CreateDepthStencilView();
			HRESULT CreateSampler();

		public:
			bool Init() override;
			bool Frame() override;
			bool Render() override;
			bool Release() override;
		};
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

		RenderTarget* _renderTarget;
		Screen _screen;
		bool _showWire = false;

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
		void ClearD3D11DeviceContext();

	public:
		DXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);
		~DXWindow();

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
