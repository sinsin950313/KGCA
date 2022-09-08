#pragma once

#include "DXCore.h"
#include "DX2DMapObject.h"
#include "DX2DCamera.h"
#include "DX2DGameObject.h"

class DX2DGameProject : public DXCore
{
private:
	DX2DMapObject _map;
	DX2DCamera _camera;
	std::vector<DX2DGameObject*> _objects;
	DX2DGameObject* _player;

public:
	DX2DGameProject(LPCWSTR name, HINSTANCE hInstance, int nCmdShow);

public:
	bool Init() override;
	bool Frame() override;
	bool Release() override;

protected:
	bool PreRender() override;
	bool MainRender() override;
	bool PostRender() override;
};
