#include "DXWindow.h"
#include <math.h>
#include <cassert>

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

		hResult = CreateRenderTargetView();
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

		hResult = CreateRenderTarget2D();
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

		_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);
	}

	HRESULT DXWindow::UpdateResize()
	{
		if (_device == nullptr)
		{
			return S_OK;
		}

		HRESULT hr;

		_deviceContext->OMSetRenderTargets(0, nullptr, NULL);

		_renderTargetView->Release();
		_renderTarget2D->Release();

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

		_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);

		return S_OK;
	}

	bool DXWindow::Init()
	{
		BasicWindow::Init();

		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = GetClientWidth();
		viewPort.Height = GetClientHeight();
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		_deviceContext->RSSetViewports(1, &viewPort);

		return true;
	}

	bool DXWindow::Frame()
	{
		_textList.clear();
		_objectList.clear();

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

		return true;
	}

	bool DXWindow::PreRender()
	{
		float color[4] = { 1, 1, 1, 1.0f };
		_deviceContext->ClearRenderTargetView(_renderTargetView, color);

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
}
