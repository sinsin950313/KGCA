#pragma once

#include "CommonClass.h"
#include <d2d1helper.h>

#include <string>
#include "TText.h"
#include <map>

class TDXWindow;

class TTextManager : public Common
{
private:
	static TTextManager* _instance;

	TDXWindow* _window;

	std::map<std::wstring, ID2D1SolidColorBrush*> _brushes;
	std::map<std::wstring, IDWriteTextFormat*> _textFormats;
	std::map<TText*, bool> _textList;

public:
	static TTextManager& GetInstance();
	void Set(TDXWindow* window) { _window = window; }
	void AddBrush(std::wstring name, D2D1_COLOR_F color);
	void AddTextFormat(std::wstring name, std::wstring locale, UINT size);
	void AddTextVisible(TText* text);
	void SetTextInvisible(TText* text);
	void SetTextVisible(TText* text);

private:
	TTextManager() { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
