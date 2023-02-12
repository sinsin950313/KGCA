#pragma once

#define _USE_MATH_DEFINES 

#include <Unknwnbase.h>
#include <math.h>
#include <cstdlib>
#include <string>
#include <codecvt>

namespace SSB
{
	typedef char Byte;

	class Common
	{
	public:
		bool Release(IUnknown* ptr) { if (ptr) ptr->Release(); return true; }

	public:
		/// <summary>
		/// Request Memory and Fill it
		/// </summary>
		/// <returns></returns>
		virtual bool Init() = 0;
		/// <summary>
		/// Calculate everything before Rendering.
		/// </summary>
		/// <returns></returns>
		virtual bool Frame() = 0;
		/// <summary>
		/// when this function called.
		/// It should be drawn.
		/// </summary>
		/// <returns></returns>
		virtual bool Render() = 0;
		/// <summary>
		/// Release memory but don't destroy it when using Memory pool
		/// </summary>
		/// <returns></returns>
		virtual bool Release() = 0;
	};

	inline float DegreeToRadian(float degree)
	{
		return (degree / 180.0f) * M_PI;
	}

	inline bool IsZero(float val) { return abs(val) < 0.001f; }

	static std::wstring mtw(std::string str)
	{
		std::wstring ret(str.begin(), str.end());
		return ret;
	}

	static std::string wtm(std::wstring str)
	{
		std::string ret(str.begin(), str.end());
		return ret;
	}
};
