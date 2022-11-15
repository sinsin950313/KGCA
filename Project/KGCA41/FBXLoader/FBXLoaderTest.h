#pragma once

#include "DXWindow.h"
#include "FBXLoader.h"

namespace SSB
{
	class FBXLoaderTest : public DXWindow
	{
	private:
		FBXLoader* _loader;
		FBXLoader* _loader1;

	public:
		FBXLoaderTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }
		~FBXLoaderTest();

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
	};
}
