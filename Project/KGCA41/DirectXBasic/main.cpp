#include "TDXWindow.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	TDXWindow window(L"Test", hInstance, nCmdShow);
	window.Init();

	IDWriteTextFormat* format;
	HRESULT hr = window.GetWriteFactory()->CreateTextFormat(L"°íµñ", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ko-kr", &format);

	ID2D1SolidColorBrush* brush;
	hr = window.GetRenderTarget2D()->CreateSolidColorBrush({ 0, 0, 0, 1 }, &brush);

	TText* text = new TText(L"Text Check", { 300, 300, 500, 400 }, format, brush);

	window.AddText(text);
	window.Run();
}
