#include "Text.h"
#include "DXWindow.h"

namespace SSB
{
	extern DXWindow* g_dxWindow;

	Text::Text(std::wstring str, RECT position, IDWriteTextFormat* format, ID2D1SolidColorBrush* brush)
		: _str(str), _pos(position), _textFormat(format), _brush(brush)
	{

	}
	bool Text::Init()
	{
		return true;
	}

	bool Text::Frame()
	{
		return true;
	}

	bool Text::Render()
	{
		g_dxWindow->AddTextable(this);

		return true;
	}

	bool Text::Release()
	{
		_brush = nullptr;
		_textFormat = nullptr;

		return true;
	}

	void Text::Draw(ID2D1RenderTarget* renderTarget)
	{
		D2D_RECT_F rt{ GetPosition().left, GetPosition().top, GetPosition().right, GetPosition().bottom };
		renderTarget->DrawText(GetString().c_str(), GetString().size(), _textFormat, rt, _brush);
	}
}
