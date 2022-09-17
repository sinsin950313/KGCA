#pragma once

#include "DX2DObject.h"
#include "ObjectFactory.h"

namespace SSB
{
	class DX2DGameObject;
	class DX2DMapObject;

	class DX2DGameObjectFactory
	{
	private:
		DX2DMapObject* _mapObject;

	public:
		void SetMapObject(DX2DMapObject* mapObject) { _mapObject = mapObject; }

	public:
		DX2DGameObject* CreateStaticGameObject(Position2D center, float width, float height, float mass);
		DX2DGameObject* CreateDynamicGameObject(Position2D center, float width, float height, float mass/*, Game Object Logic?*/);
	};
}
