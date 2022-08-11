#pragma once

class CustomFloat
{
private:
	float _val;
	static float S_EPSILON;

public:
	CustomFloat(float val) : _val(val) { }
	CustomFloat operator+(const CustomFloat& f) { return _val + f._val; }
	CustomFloat operator-(const CustomFloat& f) { return _val - f._val; }
	CustomFloat operator*(const CustomFloat& f) { return _val * f._val; }
	CustomFloat operator/(const CustomFloat& f) { return _val / f._val; }
	CustomFloat operator==(const CustomFloat& f);
	operator float() { return _val; }
};

void operator+(const float&, const CustomFloat&) = delete;
void operator-(const float&, const CustomFloat&) = delete;
void operator*(const float&, const CustomFloat&) = delete;
void operator/(const float&, const CustomFloat&) = delete;
void operator==(const float&, const CustomFloat&) = delete;
