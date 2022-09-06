#include "TText.h"
#include "TDXWindow.h"

extern TDXWindow* g_dxWindow;

TText::TText(std::wstring str, RECT position, IDWriteTextFormat* format, ID2D1SolidColorBrush* brush)
	: _str(str), _pos(position), _textFormat(format), _brush(brush)
{

}
bool TText::Init()
{
    return true;
}

bool TText::Frame()
{
    return true;
}

bool TText::Render()
{
	g_dxWindow->GetRenderTarget2D()->BeginDraw();
	Draw(g_dxWindow->GetRenderTarget2D());
	g_dxWindow->GetRenderTarget2D()->EndDraw();

    return true;
}

bool TText::Release()
{
	_brush = nullptr;
	_textFormat = nullptr;

    return true;
}

void TText::Draw(ID2D1RenderTarget* renderTarget)
{
	D2D_RECT_F rt{ GetPosition().left, GetPosition().top, GetPosition().right, GetPosition().bottom };
	renderTarget->DrawText(GetString().c_str(), GetString().size(), _textFormat, rt, _brush);
}
