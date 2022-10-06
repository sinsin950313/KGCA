#pragma once

#include "DX2DObject.h"
#include <string>
#include "InputManager.h"
#include "CommonPath.h"
#include <map>

namespace SSB
{
	class ButtonFunctor
	{
	public:
		virtual void operator()() = 0;
	};

	class Button : public DX2DObject
	{
	private:
		std::map<std::string, Sprite*> _spriteSet;
		ButtonFunctor* _functor;

	public:
		Button(Position2D center, float width, float height, ButtonFunctor* functor);
		~Button();

	public:
		void RegisterButton(std::string name, Sprite* sprite);

	private:
		bool IsIn();

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class TextUI : public DXDrawableInterface
	{
	private:
		std::wstring _fontFileName;
		Position2D _center;
		float _height = 30;
		std::string _str;
		std::map<char, Sprite*> _fontSprites;
		int _textSize;
		std::vector<DX2DObject*> _outputText;
		Position2D _parentCenter{ 0, 0 };

		float _parentRadian = 0.0f;
		float _radian = 0.0f;

	public:
		TextUI(std::wstring fontFileName, std::wstring fontInfoFileName = std::wstring());
		~TextUI();

	public:
		void SetCenter(Position2D center);
		void SetText(std::string str) { ChangeText(str); }
		void SetHeight(float height) { _height = height; }
		void ChangeText(std::string str);

	private:
		Sprite* GetSprite(char c);
		void Resize(DX2DObject* object, char c);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
		void Draw(ID3D11DeviceContext* dc) override;
		void UpdateParentData(Position2D parentCenter, float parentRadian) override { _parentCenter = parentCenter; _parentRadian = parentRadian; }
	};
}
