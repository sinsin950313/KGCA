#pragma once

#include "DXCore.h"

class DX2DMapObject;
class DX2DGameObject;
class DX2DCamera;

class DX2DGameProject : public DXCore
{
private:
	DX2DMapObject* _map;
	DX2DCamera* _camera;
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

private:
	void GameLogic();
	void SetDisplayPosition(DX2DGameObject* object);
};
