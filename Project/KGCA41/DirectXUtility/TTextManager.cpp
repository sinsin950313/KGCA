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

void TTextManager::AddText(TText* text)
{
	_textList.push_back(text);
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

	hr = _renderTarget->CreateSolidColorBrush({1, 0, 0, 1}, &_brush);
	if (FAILED(hr))
	{
		return false;
	}
	hr = _writeFactory->CreateTextFormat(L"°íµñ", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ko-kr", &_textFormat);
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

	for (auto pText : _textList)
	{
		D2D_RECT_F rt{ pText->GetPosition().left, pText->GetPosition().top, pText->GetPosition().right, pText->GetPosition().bottom };
		_renderTarget->DrawText(pText->GetString().c_str(), pText->GetString().size(), _textFormat, rt, _brush);
	}

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

	return true;
}
