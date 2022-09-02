#include "TTextManager.h"

TTextManager* TTextManager::_instance = nullptr;

TTextManager& TTextManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TTextManager();
	}
	return *_instance;
}

void TTextManager::Set(IDXGISwapChain* swapChain)
{
	_swapChain = swapChain;
}

bool TTextManager::Init()
{
	HRESULT hr;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
	if (FAILED(hr))
	{
		return false;
	}

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
	hr = _factory->CreateDxgiSurfaceRenderTarget(dxgiSurface, &props, &_renderTarget);
	if (FAILED(hr))
	{
		return false;
	}
	dxgiSurface->Release();

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&_writeFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = _renderTarget->CreateSolidColorBrush({0, 0, 0, 1}, &_brush);
	if (FAILED(hr))
	{
		return false;
	}
	hr = _writeFactory->CreateTextFormat(L"°íµñ", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ko-kr", &_textFormat);
	if (FAILED(hr))
	{
		return false;
	}

	hr = _writeFactory->CreateTextLayout(L"Test", sizeof(L"Test"), _textFormat, 100, 50, &_textLayout);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool TTextManager::Frame()
{
	return true;
}

bool TTextManager::Render()
{
	_renderTarget->BeginDraw();

	D2D1_RECT_F rt = { 0, 0, 100, 50 };
	_brush->SetColor({ 0, 0, 0, 1 });
	_renderTarget->DrawText(L"Test", 5, _textFormat, rt, _brush);

	_renderTarget->EndDraw();

	return true;
}

bool TTextManager::Release()
{
	if (_factory) _factory->Release();
	if (_writeFactory) _writeFactory->Release();
	if (_renderTarget) _renderTarget->Release();
	if (_brush) _brush->Release();
	if (_textFormat) _textFormat->Release();
	if (_textLayout) _textLayout->Release();

	return true;
}
