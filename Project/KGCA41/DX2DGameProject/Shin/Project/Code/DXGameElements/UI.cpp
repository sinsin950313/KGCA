#include "UI.h"
#include "DXWindow.h"
#include "TextureManager.h"
#include "DXStateManager.h"
#include "ShaderManager.h"

namespace SSB
{
	Button::Button(Position2D center, float width, float height, ButtonFunctor* functor)
		: DX2DObject(center, width, height), _functor(functor)
	{
	}

	Button::~Button()
	{
		Release();
	}

	void Button::RegisterButton(std::string name, Sprite* sprite)
	{
		_spriteSet.insert(std::make_pair(name, sprite));
	}

	bool Button::IsIn()
	{
		LONG mouseX = InputManager::GetInstance().GetMousePosition().x;
		LONG mouseY = InputManager::GetInstance().GetMousePosition().y;

		Position2D center = GetCenter();
		float hWidth = GetWidth() / 2;
		float hHeight = GetHeight() / 2;

		if (center.x - hWidth <= mouseX && mouseX <= center.x + hWidth)
		{
			if (center.y - hHeight <= mouseY && mouseY <= center.y + hHeight)
			{
				return true;
			}
		}

		return false;
	}

	bool Button::Init()
	{
		SetSprite(_spriteSet.find("Normal")->second);

		DX2DObject::Init();

		return true;
	}

	bool Button::Frame()
	{
		DX2DObject::Frame();

		if (IsIn())
		{
			if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_PRESSED ||
				InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_HOLD)
			{
				SetSprite(_spriteSet.find("Push")->second);
			}
			else if (InputManager::GetInstance().GetKeyState(VK_LBUTTON) == EKeyState::KEY_RELEASE)
			{
				(*_functor)();
			}
			else
			{
				SetSprite(_spriteSet.find("Hover")->second);
			}
		}
		else
		{
			SetSprite(_spriteSet.find("Normal")->second);
		}

		return true;
	}

	bool Button::Render()
	{
		DX2DObject::Render();

		return true;
	}

	bool Button::Release()
	{
		DX2DObject::Release();

		_spriteSet.clear();

		if (_functor)
		{
			delete _functor;
			_functor = nullptr;
		}

		return true;
	}

	extern DXWindow* g_dxWindow;

	TextUI::TextUI(std::wstring fontFileName, std::wstring fontInfoFileName)
	{
		_fontFileName = fontFileName;
		SpriteLoader::GetInstance().RegisterSpriteFromFile(fontFileName, fontInfoFileName);
	}

	TextUI::~TextUI()
	{
		Release();
	}

	void TextUI::SetCenter(Position2D center)
	{
		_center = center;
	}

	void TextUI::ChangeText(std::string str)
	{
		if (_str.size() < str.size())
		{
			_outputText.resize(str.size());
			for (int i = _str.size(); i < str.size(); ++i)
			{
				_outputText[i] = new DX2DObject({ 0, 0 }, 0, 0);
				_outputText[i]->SetSprite(GetSprite(str[i]));
				_outputText[i]->SetVertexShader(ShaderManager::GetInstance().LoadVertexShader(L"Default2DVertexShader.hlsl", "Main", "vs_5_0"));
				_outputText[i]->SetPixelShader(ShaderManager::GetInstance().LoadPixelShader(L"FontPixelShader.hlsl", "Main", "ps_5_0"));
				_outputText[i]->Init();
			}
		}

		_str = str;
		_textSize = _str.size();
	}

	Sprite* TextUI::GetSprite(char c)
	{
		if (_fontSprites.find(c) == _fontSprites.end())
		{
			std::string cStr;
			if (c != ' ')
			{
				cStr = (1, c);
			}
			else
			{
				cStr = "Space";
			}
			_fontSprites.insert(std::make_pair(c, SpriteLoader::GetInstance().Load(_fontFileName, std::wstring(cStr.begin(), cStr.end()), DXStateManager::kDefaultWrapSample)));
		}
		return _fontSprites.find(c)->second;
	}

	void TextUI::Resize(DX2DObject* object, char c)
	{
		Sprite* sprite = GetSprite(c);
		TexturePartCoordinateRatio cr = sprite->GetCurrentTexturePart();
		float rHeight = cr.bottom - cr.top;
		float rWidth = cr.right - cr.left;
		object->Resize(_height * rWidth / rHeight, _height);
	}

	bool TextUI::Init()
	{
		return true;
	}

	bool TextUI::Frame()
	{

		for (int i = 0; i < _textSize; ++i)
		{
			_outputText[i]->SetSprite(GetSprite(_str[i]));
			Resize(_outputText[i], _str[i]);
		}

		float width = 0;
		for (int i = 0; i < _textSize; ++i)
		{
			width += _outputText[i]->GetWidth();
		}
		float hWidth = width / 2;

		Position2D center = _center + _parentCenter;
		float left = center.x - hWidth;
		for (int i = 0; i < _textSize; ++i)
		{
			float hWidth = _outputText[i]->GetWidth() / 2;

			left += hWidth;
			_outputText[i]->SetCenter({ left, center.y });
			left += hWidth;
		}

		for (auto text : _outputText)
		{
			text->Frame();
		}

		return true;
	}

	bool TextUI::Render()
	{
		g_dxWindow->AddDrawable(this);

		return true;
	}

	bool TextUI::Release()
	{
		_str.clear();

		for (auto sprite : _fontSprites)
		{
			sprite.second->Release();
			delete sprite.second;
		}
		_fontSprites.clear();

		for (auto text : _outputText)
		{
			text->SetSprite(nullptr);
			text->Release();
			delete text;
		}
		_outputText.clear();

		return true;
	}

	void TextUI::Draw(ID3D11DeviceContext* dc)
	{
		for (int i = 0; i < _textSize; ++i)
		{
			_outputText[i]->Draw(dc);
		}
	}
}
