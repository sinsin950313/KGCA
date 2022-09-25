#pragma once

#include "DX2DObject.h"
#include "ObjectFactory.h"

namespace SSB
{
	class DX2DInGameObject;
	class DX2DMapObject;

	class DX2DGameObjectFactory
	{
	private:
		DX2DMapObject* _mapObject;

	public:
		void SetMapObject(DX2DMapObject* mapObject) { _mapObject = mapObject; }

	public:
		DX2DInGameObject* CreateStaticGameObject(Position2D center, float width, float height, float mass);
		DX2DInGameObject* CreateDynamicGameObject(Position2D center, float width, float height, float mass/*, Game Object Logic?*/);
	};
}
