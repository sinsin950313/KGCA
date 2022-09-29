#pragma once

#include "Common.h"
#include "DXTextableInterface.h"
#include <d2d1.h>
#include <string>
#include <d2d1.h>
#include <dwrite.h>

namespace SSB
{
	class Text : public Common, public DXTextableInterface
	{
	private:
		ID2D1SolidColorBrush* _brush;
		IDWriteTextFormat* _textFormat;
		RECT _pos;
		std::wstring _str;

	public:
		Text(std::wstring str, RECT position, IDWriteTextFormat* format = nullptr, ID2D1SolidColorBrush* brush = nullptr);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;

	public:
		void SetTextFormat(IDWriteTextFormat* format) { _textFormat = format; }
		void SetBrush(ID2D1SolidColorBrush* brush) { _brush = brush; }
		void SetString(std::wstring str) { _str = str; }
		void SetPosition(RECT pos) { _pos = pos; }
		std::wstring GetString() { return _str; }
		RECT GetPosition() { return _pos; }

	public:
		ID2D1SolidColorBrush* GetBrush() { return _brush; }
		IDWriteTextFormat* GetFormat() { return _textFormat; }

	protected:
		void Draw(ID2D1RenderTarget* renderTarget);
	};
}
