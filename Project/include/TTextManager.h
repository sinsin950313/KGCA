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

	std::map<std::wstring, ID2D1SolidColorBrush*> _brushes;
	std::map<std::wstring, IDWriteTextFormat*> _textFormats;

public:
	static TTextManager& GetInstance();
	ID2D1SolidColorBrush* LoadBrush(std::wstring colorName, D2D1_COLOR_F color);
	IDWriteTextFormat* LoadTextFormat(std::wstring name, std::wstring locale, UINT size);

private:
	TTextManager() { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
