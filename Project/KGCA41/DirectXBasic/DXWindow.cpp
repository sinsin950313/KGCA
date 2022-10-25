#include "DXWindow.h"
#include <math.h>
#include <cassert>
#include "DXStateManager.h"

namespace SSB
{
	DXWindow* g_dxWindow = nullptr;

	DXWindow::DXWindow(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : BasicWindow(name, hInstance, nCmdShow)
	{
		g_dxWindow = this;

		HRESULT hResult;

		hResult = CreateDevice();
		if (FAILED(hResult))
		{
			assert(SUCCEEDED(hResult));
			return;
		}

		hResult = CreateWindowDXGIFactory();
		if (FAILED(hResult))
		{
			assert(SUCCEEDED(hResult));
			return;
		}

		hResult = CreateSwapChain();
		if (FAILED(hResult))
		{
			assert(SUCCEEDED(hResult));
			return;
		}

		hResult = Create2DFactory();
		if (FAILED(hResult))
		{
			assert(SUCCEEDED(hResult));
			return;
		}

		hResult = CreateWriteFactory();
		if (FAILED(hResult))
		{
			assert(SUCCEEDED(hResult));
			return;
		}

		_renderTarget = new RenderTarget();

		_mainCamera = &_defaultCamera;
	}

	HRESULT DXWindow::UpdateResize()
	{
		if (_device == nullptr)
		{
			return S_OK;
		}

		HRESULT hr;

		_deviceContext->OMSetRenderTargets(0, nullptr, NULL);

		if (_renderTargetView)_renderTargetView->Release();
		if (_renderTarget2D)_renderTarget2D->Release();
		if (_depthStencilView)_depthStencilView->Release();

		if (_renderTarget)
		{
			_renderTarget->Release();
		}
		_screen.Release();

		DXGI_SWAP_CHAIN_DESC currDesc, AfterDesc;
		_swapChain->GetDesc(&currDesc);
		hr = _swapChain->ResizeBuffers(currDesc.BufferCount, g_dxWindow->GetClientWidth(), g_dxWindow->GetClientHeight(), currDesc.BufferDesc.Format, 0);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		hr = CreateRenderTargetView();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		hr = CreateRenderTarget2D();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		hr = CreateDepthStencilView();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		_renderTarget->Init();
		_screen.SetRenderTargetTexture(_renderTarget->GetRenderTargetTexture());
		_screen.SetDepthStencilTexture(_renderTarget->GetDepthStencilTexture());
		_screen.Init();

		_deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

		CreateViewPort();

		return S_OK;
	}

	bool DXWindow::Init()
	{
		BasicWindow::Init();

		DXStateManager::GetInstance().Init();

		UpdateResize();

		return true;
	}

	bool DXWindow::Frame()
	{
		_textList.clear();
		_objectList.clear();
		_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		_mainCamera->Frame();

		_renderTarget->Frame();
		_screen.Frame();

		return true;
	}

	bool DXWindow::Render()
	{
		if (!PreRender())
		{
			return false;
		}
		if (!MainRender())
		{
			return false;
		}
		if (!PostRender())
		{
			return false;
		}
		return true;
	}

	bool DXWindow::Release()
	{
		if (_dxgiFactory) _dxgiFactory->Release();

		if (_device) _device->Release();
		if (_deviceContext) _deviceContext->Release();
		if (_swapChain) _swapChain->Release();
		if (_renderTargetView) _renderTargetView->Release();

		if (_factory2D) _factory2D->Release();
		if (_writeFactory) _writeFactory->Release();
		if (_renderTarget2D) _renderTarget2D->Release();
		if (_depthStencilView) _depthStencilView->Release();

		_mainCamera = nullptr;

		DXStateManager::GetInstance().Release();

		if(_renderTarget)_renderTarget->Release();
		_screen.Release();

		return true;
	}

	bool DXWindow::PreRender()
	{
		float color[4] = { 1, 1, 1, 1.0f };
		_deviceContext->ClearRenderTargetView(_renderTargetView, color);

		auto renderTargetView = _renderTarget->GetRenderTargetView();
		GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, _renderTarget->GetDepthStencilView());
		_renderTarget->Clear();

		return true;
	}

	bool DXWindow::MainRender()
	{
		DrawObjects();

		_renderTarget2D->BeginDraw();
		DrawTexts();
		_renderTarget2D->EndDraw();

		return true;
	}

	bool DXWindow::PostRender()
	{
		GetDeviceContext()->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

		_screen.Render();

		_swapChain->Present(0, 0);

		return true;
	}

	void DXWindow::DrawTexts()
	{
		for (auto text : _textList)
		{
			text->Draw(_renderTarget2D);
		}
	}

	void DXWindow::AddDrawable(DXDrawableInterface* drawable)
	{
		_objectList.push_back(drawable);
	}

	void DXWindow::AddTextable(DXTextableInterface* textable)
	{
		_textList.push_back(textable);
	}

	void DXWindow::DrawObjects()
	{
		for (auto object : _objectList)
		{
			object->Draw(_deviceContext);
		}
	}

	HRESULT DXWindow::CreateDevice()
	{
		UINT deviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
		deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevelList[] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0 };
		return D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlag, featureLevelList, 1, D3D11_SDK_VERSION, &_device, &_featureLevel, &_deviceContext);
	}

	HRESULT DXWindow::CreateWindowDXGIFactory()
	{
		return CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);
	}

	HRESULT DXWindow::CreateSwapChain()
	{
		DXGI_MODE_DESC dxgi_mode_desc;
		ZeroMemory(&dxgi_mode_desc, sizeof(DXGI_MODE_DESC));
		dxgi_mode_desc.Width = GetClientWidth();
		dxgi_mode_desc.Height = GetClientHeight();
		dxgi_mode_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgi_mode_desc.RefreshRate.Denominator = 1;
		dxgi_mode_desc.RefreshRate.Numerator = 60;

		DXGI_SAMPLE_DESC dxgi_sample_desc;
		dxgi_sample_desc.Count = 1;
		dxgi_sample_desc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc = dxgi_mode_desc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Flags = 0;
		swapChainDesc.OutputWindow = GetWindowHandle();
		swapChainDesc.SampleDesc = dxgi_sample_desc;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = true;

		return _dxgiFactory->CreateSwapChain(_device, &swapChainDesc, &_swapChain);
	}

	HRESULT DXWindow::CreateRenderTargetView()
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		HRESULT hr = _device->CreateRenderTargetView(pBackBuffer, NULL, &_renderTargetView);
		pBackBuffer->Release();

		return hr;
	}

	HRESULT DXWindow::Create2DFactory()
	{
		return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory2D);
	}

	HRESULT DXWindow::CreateRenderTarget2D()
	{
		D2D1_RENDER_TARGET_PROPERTIES props;
		ZeroMemory(&props, sizeof(D2D1_RENDER_TARGET_PROPERTIES));
		props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
		props.dpiX = 96;
		props.dpiY = 96;
		props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

		IDXGISurface1* dxgiSurface;
		_swapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&dxgiSurface);
		HRESULT hr = _factory2D->CreateDxgiSurfaceRenderTarget(dxgiSurface, &props, &_renderTarget2D);
		dxgiSurface->Release();

		return hr;
	}

	HRESULT DXWindow::CreateWriteFactory()
	{
		return DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&_writeFactory);
	}
	HRESULT DXWindow::CreateViewPort()
	{
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = GetClientWidth();
		viewPort.Height = GetClientHeight();
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		_deviceContext->RSSetViewports(1, &viewPort);

		return S_OK;
	}
	HRESULT DXWindow::CreateDepthStencilView()
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		_swapChain->GetDesc(&swapChainDesc);

		ID3D11Texture2D* texture;
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		textureDesc.Width = swapChainDesc.BufferDesc.Width;
		textureDesc.Height = swapChainDesc.BufferDesc.Height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		HRESULT hr = _device->CreateTexture2D(&textureDesc, NULL, &texture);
		if (FAILED(hr))
		{
			return hr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = _device->CreateDepthStencilView(texture, &dsvDesc, &_depthStencilView);
		texture->Release();
		if (FAILED(hr))
		{
			return hr;
		}

		auto state = DXStateManager::GetInstance().GetDepthStencilState(DXStateManager::kDefaultDepthStencil);

		_deviceContext->OMSetDepthStencilState(state, 0xff);

		return S_OK;
	}
	RenderTarget::RenderTarget()
	{
	}
	HRESULT RenderTarget::CreateRenderTarget()
	{
		HRESULT hr = S_OK;

		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		renderTargetTextureDesc.Width = g_dxWindow->GetClientWidth();
		renderTargetTextureDesc.Height = g_dxWindow->GetClientHeight();
		renderTargetTextureDesc.MipLevels = 1;
		renderTargetTextureDesc.ArraySize = 1;
		renderTargetTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderTargetTextureDesc.SampleDesc.Count = 1;
		renderTargetTextureDesc.SampleDesc.Quality = 0;
		renderTargetTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		renderTargetTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTextureDesc.CPUAccessFlags = 0;
		renderTargetTextureDesc.MiscFlags = 0;

		hr = g_dxWindow->GetDevice()->CreateTexture2D(&renderTargetTextureDesc, NULL, &_renderTargetTexture);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		hr = g_dxWindow->GetDevice()->CreateRenderTargetView(_renderTargetTexture, NULL, &_renderTargetView);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		return hr;
	}
	HRESULT RenderTarget::CreateDepthStencil()
	{
		HRESULT hr = S_OK;

		D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
		depthStencilTextureDesc.Width = g_dxWindow->GetClientWidth();
		depthStencilTextureDesc.Height = g_dxWindow->GetClientHeight();
		depthStencilTextureDesc.MipLevels = 1;
		depthStencilTextureDesc.ArraySize = 1;
		depthStencilTextureDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		depthStencilTextureDesc.SampleDesc.Count = 1;
		depthStencilTextureDesc.SampleDesc.Quality = 0;
		depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		depthStencilTextureDesc.CPUAccessFlags = 0;
		depthStencilTextureDesc.MiscFlags = 0;

		hr = g_dxWindow->GetDevice()->CreateTexture2D(&depthStencilTextureDesc, NULL, &_depthStencilTexture);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		hr = g_dxWindow->GetDevice()->CreateDepthStencilView(_depthStencilTexture, &depthStencilViewDesc, &_depthStencilView);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}

		return hr;
	}
	void RenderTarget::Clear()
	{
		float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_dxWindow->GetDeviceContext()->ClearRenderTargetView(_renderTargetView, color);
		g_dxWindow->GetDeviceContext()->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	bool RenderTarget::Init()
	{
		HRESULT hr;

		hr = CreateRenderTarget();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		hr = CreateDepthStencil();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		return true;
	}
	bool RenderTarget::Frame()
	{
		return true;
	}
	bool RenderTarget::Render()
	{
		return true;
	}
	bool RenderTarget::Release()
	{
		if (_renderTargetTexture)
		{
			_renderTargetTexture->Release();
			_renderTargetTexture = nullptr;
		}

		if (_renderTargetTexture)
		{
			_renderTargetTexture->Release();
			_renderTargetView = nullptr;
		}

		if (_depthStencilTexture)
		{
			_depthStencilTexture->Release();
			_depthStencilTexture = nullptr;
		}

		if (_depthStencilView)
		{
			_depthStencilTexture->Release();
			_depthStencilView = nullptr;
		}

		return true;
	}
	DXWindow::Screen::Screen()
	{
	}
	HRESULT DXWindow::Screen::CreateRenderTargetView()
	{
		HRESULT hr = S_OK;
		hr = g_dxWindow->GetDevice()->CreateShaderResourceView(_renderTargetTexture, NULL, &_renderedTargetView);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}
	}
	HRESULT DXWindow::Screen::CreateDepthStencilView()
	{
		HRESULT hr = S_OK;
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = 1;

		hr = g_dxWindow->GetDevice()->CreateShaderResourceView(_renderedDepthStencilTexture, &desc, &_renderedDepthStencilView);
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return hr;
		}
	}
	bool DXWindow::Screen::Init()
	{
		HRESULT hr;

		hr = CreateVertexBuffer();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		hr = CreateIndexBuffer();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		hr = CreateRenderTargetView();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		hr = CreateDepthStencilView();
		if (FAILED(hr))
		{
			assert(SUCCEEDED(hr));
			return false;
		}

		return true;
	}
	bool DXWindow::Screen::Frame()
	{
		return true;
	}
	bool DXWindow::Screen::Render()
	{
		g_dxWindow->GetDeviceContext()->IASetVertexBuffers();
		g_dxWindow->GetDeviceContext()->IASetIndexBuffer();
		g_dxWindow->GetDeviceContext()->IASetInputLayout();
		g_dxWindow->GetDeviceContext()->VSSetShader();
		g_dxWindow->GetDeviceContext()->PSSetShader();
		g_dxWindow->GetDeviceContext()->DrawIndexed();
		return true;
	}
	bool DXWindow::Screen::Release()
	{
		if (_vertexBuffer)
		{
			_vertexBuffer->Release();
			_vertexBuffer = nullptr;
		}
		if (_indexBuffer)
		{
			_indexBuffer->Release();
			_indexBuffer = nullptr;
		}
		if (_renderTargetTexture)
		{
			_renderTargetTexture = nullptr;
		}
		if (_renderedTargetView)
		{
			_renderedTargetView->Release();
		}
		if (_renderedDepthStencilTexture)
		{
			_renderedDepthStencilTexture = nullptr;
		}
		if (_renderedDepthStencilView)
		{
			_renderedDepthStencilView->Release();
			_renderedDepthStencilView = nullptr;
		}
		{
			_vs._code->Release();
			_vs._shader->Release();
		}
		{
			_ps._code->Release();
			_ps._shader->Release();
		}

		return true;
	}
}
