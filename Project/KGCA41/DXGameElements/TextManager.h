#pragma once

#include "Common.h"
#include <d2d1helper.h>

#include <string>
#include "Text.h"
#include <map>

namespace SSB
{
	class DXWindow;

	class TextManager : public Common
	{
	private:
		static TextManager* _instance;

		std::map<std::wstring, ID2D1SolidColorBrush*> _brushes;
		std::map<std::wstring, IDWriteTextFormat*> _textFormats;

	public:
		static TextManager& GetInstance();
		ID2D1SolidColorBrush* LoadBrush(std::wstring colorName, D2D1_COLOR_F color);
		IDWriteTextFormat* LoadTextFormat(std::wstring name, std::wstring locale, UINT size);

	private:
		TextManager() { }
		~TextManager();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
}
