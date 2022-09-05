#pragma once

#include "CommonClass.h"
#include <d2d1.h>
#include <string>
#include <d2d1.h>
#include <dwrite.h>

class TText : public Common
{
private:
	ID2D1SolidColorBrush* _brush;
	IDWriteTextFormat* _textFormat;
	RECT _pos;
	std::wstring _str;

public:
	TText(std::wstring str, RECT position, IDWriteTextFormat* format, ID2D1SolidColorBrush* brush) : _str(str), _pos(position), _textFormat(format), _brush(brush) { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;

public:
	void SetString(std::wstring str) { _str = str; }
	void SetPosition(RECT pos) { _pos = pos; }
	std::wstring GetString() { return _str; }
	RECT GetPosition() { return _pos; }

public:
	ID2D1SolidColorBrush* GetBrush() { return _brush; }
	IDWriteTextFormat* GetFormat() { return _textFormat; }
};
