#pragma once

#include "DXWindow.h"
#include "FBXLoader.h"

namespace SSB
{
	class FBXLoaderTest : public DXWindow
	{
	private:
		FBXLoader* _loader;
		std::vector<DXObject*> _objectList;
		Camera* _camera;

	public:
		FBXLoaderTest(LPCWSTR name, HINSTANCE hInstance, int nCmdShow) : DXWindow(name, hInstance, nCmdShow) { }
		virtual ~FBXLoaderTest();

	public:
		bool Init() override;
		bool Frame() override;
		bool Release() override;

	protected:
		bool PreRender() override;
	};
}
