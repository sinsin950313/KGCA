#include "TTextManager.h"
#include "TDXWindow.h"

TTextManager* TTextManager::_instance = nullptr;

TTextManager& TTextManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TTextManager();
	}
	return *_instance;
}

void TTextManager::AddBrush(std::wstring name, D2D1_COLOR_F color)
{
	HRESULT hr;
	ID2D1SolidColorBrush* brush = nullptr;
	hr = _window->GetRenderTarget2D()->CreateSolidColorBrush(color, &brush);
	if (FAILED(hr))
	{
		return;
	}
	_brushes.insert(std::make_pair(name, brush));
}

void TTextManager::AddTextFormat(std::wstring name, std::wstring locale, UINT size)
{
	HRESULT hr;
	IDWriteTextFormat* textFormat = nullptr;
	hr = _window->GetWriteFactory()->CreateTextFormat(name.c_str(), NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, 
														DWRITE_FONT_STRETCH_NORMAL, size, locale.c_str(), &textFormat);
	if (FAILED(hr))
	{
		return;
	}
	_textFormats.insert(std::make_pair(L"Default", textFormat));
}

void TTextManager::AddTextVisible(TText* text)
{
	_textList.insert(std::make_pair(text, true));
}

void TTextManager::SetTextInvisible(TText* text)
{
	_textList.find(text)->second = false;
}

void TTextManager::SetTextVisible(TText* text)
{
	_textList.find(text)->second = true;
}

bool TTextManager::Init()
{
	AddBrush(L"Default", { 1, 0, 0, 0 });
	AddTextFormat(L"°íµñ", L"ko-kr", 30);

	return true;
}

bool TTextManager::Frame()
{
	for (auto text : _textList)
	{
		if (text.second)
		{
			_window->AddText(text.first);
		}
	}

	return true;
}

bool TTextManager::Render()
{

	return true;
}

bool TTextManager::Release()
{
	for (auto text : _textList)
	{
		text.first->Release();
	}
	_textList.clear();

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
