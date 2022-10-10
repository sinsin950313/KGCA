#include "TextManager.h"
#include "DXWindow.h"

namespace SSB
{
	TextManager* TextManager::_instance = nullptr;
	extern DXWindow* g_dxWindow;

	TextManager& TextManager::GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new TextManager();
		}
		return *_instance;
	}

	ID2D1SolidColorBrush* TextManager::LoadBrush(std::wstring colorName, D2D1_COLOR_F color)
	{
		if (_brushes.find(colorName) == _brushes.end())
		{
			HRESULT hr;
			ID2D1SolidColorBrush* brush = nullptr;
			hr = g_dxWindow->GetRenderTarget2D()->CreateSolidColorBrush(color, &brush);
			if (FAILED(hr))
			{
				return nullptr;
			}
			_brushes.insert(std::make_pair(colorName, brush));
		}
		return _brushes.find(colorName)->second;
	}

	IDWriteTextFormat* TextManager::LoadTextFormat(std::wstring name, std::wstring locale, UINT size)
	{
		if (_textFormats.find(name) == _textFormats.end())
		{
			HRESULT hr;
			IDWriteTextFormat* textFormat = nullptr;
			hr = g_dxWindow->GetWriteFactory()->CreateTextFormat(name.c_str(), NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL, size, locale.c_str(), &textFormat);
			if (FAILED(hr))
			{
				return nullptr;
			}
			_textFormats.insert(std::make_pair(name, textFormat));
		}
		return _textFormats.find(name)->second;
	}

	TextManager::~TextManager()
	{
		Release();

		delete _instance;
		_instance = nullptr;
	}

	bool TextManager::Init()
	{
		LoadBrush(L"Black", { 0, 0, 0, 1 });
		LoadTextFormat(L"°íµñ", L"ko-kr", 30);

		return true;
	}

	bool TextManager::Frame()
	{
		return true;
	}

	bool TextManager::Render()
	{
		return true;
	}

	bool TextManager::Release()
	{
		for (auto brush : _brushes)
		{
			brush.second->Release();
		}
		_brushes.clear();

		for (auto format : _textFormats)
		{
			format.second->Release();
		}
		_textFormats.clear();

		return true;
	}
}
