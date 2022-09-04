#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include "CommonClass.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include <string>
#include <vector>
#include "TText.h"

class TTextManager : public Common
{
private:
	static TTextManager* _instance;
	ID2D1Factory* _factory;
	IDXGISwapChain* _swapChain;
	IDWriteFactory* _writeFactory;
	ID2D1RenderTarget* _renderTarget;

	ID2D1SolidColorBrush* _brush;
	IDWriteTextFormat* _textFormat;
	std::vector<TText*> _textList;

public:
	static TTextManager& GetInstance();
	void Set(IDXGISwapChain* swapChain);
	void AddText(TText* text);

private:
	TTextManager() { }

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
