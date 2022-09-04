#include "TDXWindow.h"
#include <math.h>

bool TDXWindow::Init()
{
	TBasicWindow::Init();

	HRESULT hResult;

	UINT deviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevelList[] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0 };
	hResult = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlag, featureLevelList, 1, D3D11_SDK_VERSION, &_device, &_featureLevel, &_deviceContext);
	if (FAILED(hResult))
	{
		return false;
	}

	hResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);
	if (FAILED(hResult))
	{
		return false;
	}

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

	hResult = _dxgiFactory->CreateSwapChain(_device, &swapChainDesc, &_swapChain);
	if (FAILED(hResult))
	{
		return false;
	}

	ID3D11Texture2D* pBackBuffer = nullptr;
	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	_device->CreateRenderTargetView(pBackBuffer, NULL, &_renderTargetView);
	pBackBuffer->Release();

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = GetClientWidth();
	viewPort.Height = GetClientHeight();
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	_deviceContext->RSSetViewports(1, &viewPort);

	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);

	return true;
}

bool TDXWindow::Frame()
{
	return true;
}

bool TDXWindow::Render()
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

bool TDXWindow::Release()
{
	if(_dxgiFactory) _dxgiFactory->Release();
	if(_device) _device->Release();
	if(_deviceContext) _deviceContext->Release();
	if(_swapChain) _swapChain->Release();
	if(_renderTargetView) _renderTargetView->Release();

	return true;
}

bool TDXWindow::PreRender()
{
	float color[4] = { 1, 1, 1, 1.0f };
	_deviceContext->ClearRenderTargetView(_renderTargetView, color);
	return true;
}

bool TDXWindow::MainRender()
{
	return true;
}

bool TDXWindow::PostRender()
{
	_swapChain->Present(0, 0);
	return true;
}
