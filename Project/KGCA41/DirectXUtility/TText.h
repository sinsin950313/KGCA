#pragma once

#include "CommonClass.h"
#include <d2d1.h>
#include <string>

class TText : public Common
{
private:
	RECT _pos;
	std::wstring _str;

public:
	TText(std::wstring str, RECT position) : _str(str), _pos(position) { }

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
};
