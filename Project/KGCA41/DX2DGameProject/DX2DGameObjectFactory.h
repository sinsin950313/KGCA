#pragma once

class DX2DGameObject;
class DX2DMapObject;

class DX2DGameObjectFactory
{
private:
	DX2DMapObject* _mapObject;

public:
	void SetMapObject(DX2DMapObject* mapObject) { _mapObject = mapObject; }

public:
	DX2DGameObject* CreateStaticGameObject();
	DX2DGameObject* CreateDynamicGameObject(/*Game Object Logic?*/);
};
